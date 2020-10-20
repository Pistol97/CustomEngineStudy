#include "Renderer.h"

#include <stdio.h>

#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h"

#include "glm/gtc/matrix_transform.hpp"

#include "Shader.h"
#include "RenderableObject.h"
#include "NonRenderableObject.h"
#include "Camera.h"
#include "FileManager.h"

Renderer* Renderer::instance = nullptr;

void Renderer::Init(int width, int height, const char* title_name)
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(width, height, title_name, NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	// Hide the mouse and enable unlimited mouvement
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set the mouse at the center of the screen
	glfwPollEvents();
	glfwSetCursorPos(window, width / 2, height / 2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	//쉐이더 불러오기
	Shader* shader = new Shader("vertex.shader", "fragment.shader");
	programID = shader->LoadShaders();

	delete shader;

	MatrixID = glGetUniformLocation(Renderer::Instance()->GetProgramID(), "MVP");
	ViewMatrixID = glGetUniformLocation(Renderer::Instance()->GetProgramID(), "V");
	ModelMatrixID = glGetUniformLocation(Renderer::Instance()->GetProgramID(), "M");

	// Compute the MVP matrix from keyboard and mouse input
	ProjectionMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

	// Get a handle for our "myTextureSampler" uniform
	TextureID = glGetUniformLocation(Renderer::Instance()->GetProgramID(), "myTextureSampler");

	// Get a handle for our "LightPosition" uniform
	glUseProgram(Renderer::Instance()->GetProgramID());
	LightID = glGetUniformLocation(Renderer::Instance()->GetProgramID(), "LightPosition_worldspace");



}

void Renderer::LoadVBO()
{
	for (
		std::vector<RenderableObject*>::iterator it = render_objects.begin();
		it != render_objects.end();
		++it
		)
	{
		// Load it into a VBO
		glGenBuffers(1, &(*it)->GetVertexBuffer());
		glBindBuffer(GL_ARRAY_BUFFER, (*it)->GetVertexBuffer());
		glBufferData(GL_ARRAY_BUFFER, (*it)->GetIndexedVertices().size() * sizeof(glm::vec3), &(*it)->GetIndexedVertices()[0], GL_STATIC_DRAW);

		glGenBuffers(1, &(*it)->GetUVBuffer());
		glBindBuffer(GL_ARRAY_BUFFER, (*it)->GetUVBuffer());
		glBufferData(GL_ARRAY_BUFFER, (*it)->GetIndexedUVs().size() * sizeof(glm::vec2), &(*it)->GetIndexedUVs()[0], GL_STATIC_DRAW);

		glGenBuffers(1, &(*it)->GetNormalBuffer());
		glBindBuffer(GL_ARRAY_BUFFER, (*it)->GetNormalBuffer());
		glBufferData(GL_ARRAY_BUFFER, (*it)->GetIndexedNormals().size() * sizeof(glm::vec3), &(*it)->GetIndexedNormals()[0], GL_STATIC_DRAW);

		glGenBuffers(1, &(*it)->GetElementBuffer());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*it)->GetElementBuffer());
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (*it)->GetIndices().size() * sizeof(int), &(*it)->GetIndices()[0], GL_STATIC_DRAW);
	}
}

void Renderer::Draw()
{
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use our shader
	glUseProgram(programID);

	lightPos = glm::vec3(4, 4, 4);
	glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
	for (
		std::vector<RenderableObject*>::iterator it = render_objects.begin();
		it != render_objects.end();
		++it
		)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, (*it)->GetTexture());
		// Set our "myTextureSampler" sampler to use Texture Unit 0
		glUniform1i(TextureID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, (*it)->GetVertexBuffer());
		glVertexAttribPointer(
			0,                  // attribute
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, (*it)->GetUVBuffer());
		glVertexAttribPointer(
			1,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// 3rd attribute buffer : normals
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, (*it)->GetNormalBuffer());
		glVertexAttribPointer(
			2,                                // attribute
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*it)->GetElementBuffer());

		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &camera->GetViewMatrix()[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &(*it)->GetModelMatrix()[0][0]);
		glm::mat4 MVP = ProjectionMatrix * camera->GetViewMatrix() * (*it)->GetModelMatrix();

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		// Draw the triangles !
		glDrawElements(
			GL_TRIANGLES,
			(*it)->GetIndices().size(), 
			GL_UNSIGNED_INT, 
			(void*)0
		);
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	// Swap buffers
	glfwSwapBuffers(Renderer::Instance()->GetWindow());
	glfwPollEvents();
}

void Renderer::Update()
{
	for(
		std::vector<NonRenderableObject*>::iterator it = non_render_objects.begin();
		it != non_render_objects.end();
		++it	
		)
	{
		(*it)->Update();
	}
}

void Renderer::Clean()
{
	for (
		std::vector<RenderableObject*>::iterator it = render_objects.begin();
		it != render_objects.end();
		++it
		)
	{
		(*it)->Clean();
	}

	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	delete instance;
}