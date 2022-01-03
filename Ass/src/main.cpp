#include <iostream>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "BufferLayout.h"
#include "Camera.h"
#include "Mesh.h"

const unsigned int WINDOW_WIDTH = 1024;
const unsigned int WINDOW_HEIGHT = 780;

bool WIREFRAME_SETTING = false;

// camera
Camera camera(glm::vec3(0.0f, 1.0f, 5.0f));
double g_lastX, g_lastY;

int buttonDown = -1;

float nearPlane = 0.1f, farPlane = 100.0f;

float g_rotX_angle = 0.0f;
float g_rotY_angle = 0.0f;

double deltaTime = 0.0f;
double lastTime = 0.0f;

// light
glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);

void frameBuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, double deltaTime);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void setWireframe();
void cursor_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

int main()
{
	//initialize and create window
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "ASS", nullptr, nullptr);

	if (window == nullptr)
	{
		std::cout << "Failed to create a GLFW window." << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, frameBuffer_size_callback);

	glfwSetKeyCallback(window, key_callback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	Shader gridShader("res/shaders/GridVertex.shader", "res/shaders/GridFragment.shader");

	float vertices[] = {
		// Front face		// Normals
		-1.0, -1.0,  1.0,	0.0, 0.0, 1.0,
		 1.0, -1.0,  1.0,	0.0, 0.0, 1.0,
		 1.0,  1.0,  1.0,	0.0, 0.0, 1.0,
		-1.0,  1.0,  1.0,	0.0, 0.0, 1.0,

		// Back face
		-1.0, -1.0, -1.0,	0.0, 0.0, -1.0,
		-1.0,  1.0, -1.0,	0.0, 0.0, -1.0,
		 1.0,  1.0, -1.0,	0.0, 0.0, -1.0,
		 1.0, -1.0, -1.0,	0.0, 0.0, -1.0,

		 // Top face
		-1.0,  1.0, -1.0,	0.0, 1.0, 0.0,
		-1.0,  1.0,  1.0,	0.0, 1.0, 0.0,
		 1.0,  1.0,  1.0,	0.0, 1.0, 0.0,
		 1.0,  1.0, -1.0,	0.0, 1.0, 0.0,

		 // Bottom face
		 -1.0, -1.0, -1.0,	0.0, -1.0, 0.0,
		  1.0, -1.0, -1.0,	0.0, -1.0, 0.0,
		  1.0, -1.0,  1.0,	0.0, -1.0, 0.0,
		 -1.0, -1.0,  1.0,	0.0, -1.0, 0.0,

		 // Right face
		 1.0, -1.0, -1.0,	1.0, 0.0, 0.0,
		 1.0,  1.0, -1.0,	1.0, 0.0, 0.0,
		 1.0,  1.0,  1.0,	1.0, 0.0, 0.0,
		 1.0, -1.0,  1.0,	1.0, 0.0, 0.0,

		 // Left face
		 -1.0, -1.0, -1.0,	-1.0, 0.0, 0.0,
		 -1.0, -1.0,  1.0,	-1.0, 0.0, 0.0,
		 -1.0,  1.0,  1.0,	-1.0, 0.0, 0.0,
		 -1.0,  1.0, -1.0,	- 1.0, 0.0, 0.0
	};

	unsigned int indices[] = {
		// front
		0,  1,  2,
		0,  2,  3,

		// back
		4,  5,  6,
		4,  6,  7,

		// top
		8,  9,  10,
		8,  10, 11,

		// bottom
		12, 13, 14,
		12, 14, 15,

		// right
		16, 17, 18,
		16, 18, 19,

		// left
		20, 21, 22,
		20, 22, 23
	};

	float grid[] = {
		 1.0f,  1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f
	};

	unsigned int gridIndices[] = {
		0,  1,  3,
		1,  2,  3
	};

	std::vector<Vertex> verts;
	std::vector<unsigned int> inds(indices, indices + (sizeof(indices) / sizeof(indices[0])));

	for (int i = 0; i < sizeof(vertices) / sizeof(vertices[0]); i += 6)
	{
		Vertex v;
		v.Position = glm::vec3(vertices[i], vertices[i+1], vertices[i+2]);
		v.Normal = glm::vec3(vertices[i+3], vertices[i+4], vertices[i+5]);

		verts.push_back(v);
	}

	memset(vertices, 0, sizeof(vertices));
	memset(indices, 0, sizeof(indices));

	Mesh cube(verts, inds);
	cube.SetShader("res/shaders/PhongVertex.shader", "res/shaders/PhongFragment.shader");
	
	Mesh light(verts, inds);
	light.SetShader("res/shaders/LightVertex.shader", "res/shaders/LightFragment.shader");

	VertexArray* VAO_2 = new VertexArray();
	VertexBuffer* VBO_2 = new VertexBuffer(grid, 4 * 3 * sizeof(float));
	IndexBuffer* EBO_2 = new IndexBuffer(gridIndices, 6);
	BufferLayout* layout_2 = new BufferLayout();

	layout_2->Add<float>(3);

	VAO_2->AddBuffer(*VBO_2, *layout_2);
	VAO_2->Unbind();

	while (!glfwWindowShouldClose(window))
	{
		// calculate delta-time

		double  currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// process inputs & clear scr

		processInput(window, deltaTime);

		glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// orbit light
		lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
		lightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;

		// 3D cube model

		if (WIREFRAME_SETTING)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		// setting default uniforms
		cube.GetShader().Use();
		cube.GetShader().SetUniformVec3f("lightColor", glm::vec3(1.0f));
		cube.GetShader().SetUniformVec3f("lightPos", lightPos);
		cube.GetShader().SetUniformVec3f("viewPos", camera.GetPosition());

		cube.GetShader().SetUniformVec3f("material.color", cube.GetMaterial().color);
		cube.GetShader().SetUniformVec3f("material.ambient", cube.GetMaterial().ambient);
		cube.GetShader().SetUniformVec3f("material.diffuse", cube.GetMaterial().diffuse);
		cube.GetShader().SetUniformVec3f("material.specular", cube.GetMaterial().specular);
		cube.GetShader().SetUniform1f("material.shininess", cube.GetMaterial().shininess);

		// view/projection transformations
		glm::mat4 projection = glm::perspective(camera.GetZoom(), (float)(WINDOW_WIDTH / WINDOW_HEIGHT), nearPlane, farPlane);
		glm::mat4 view = camera.GetViewMatrix();

		cube.GetShader().SetUniformMat4f("projection", projection);
		cube.GetShader().SetUniformMat4f("view", view);

		// world transforamtions
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(g_rotX_angle), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(g_rotY_angle), glm::vec3(0.0f, 1.0f, 0.0f));

		cube.GetShader().SetUniformMat4f("model", model);

		// draw cube
		cube.Draw();



		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		// light
		light.GetShader().Use();
		light.GetShader().SetUniformMat4f("projection", projection);
		light.GetShader().SetUniformMat4f("view", view);

		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
		light.GetShader().SetUniformMat4f("model", model);

		// draw light
		light.Draw();

		// 3D 
		gridShader.Use();

		gridShader.SetUniform1f("nearPlane", nearPlane);
		gridShader.SetUniform1f("farPlane", farPlane);
		gridShader.SetUniformMat4f("projection", projection);
		gridShader.SetUniformMat4f("view", view);

		VAO_2->Bind();
		EBO_2->Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	delete VAO_2;
	delete VBO_2;
	delete EBO_2;
	delete layout_2;

	glfwTerminate();
	return 0;
}

void frameBuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, double deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(Cam::Camera_Movement::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(Cam::Camera_Movement::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(Cam::Camera_Movement::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(Cam::Camera_Movement::RIGHT, deltaTime);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
	if (key == GLFW_KEY_E && action == GLFW_PRESS) setWireframe();
	if (key == GLFW_KEY_R && action == GLFW_PRESS) camera.ResetPosition();
}

void setWireframe()
{
	WIREFRAME_SETTING = !WIREFRAME_SETTING;
	//if (WIREFRAME_SETTING)
	//{
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//}
	//else 
	//{
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//}
}

void cursor_callback(GLFWwindow* window, double xpos, double ypos)
{
	double xoffset = xpos - g_lastX;
	double yoffset = g_lastY - ypos; // reversed since y-coordinates go from bottom to top

	if (buttonDown == 1) camera.ProcessMouseMovement(xoffset, yoffset, deltaTime);

	if (buttonDown == 0)
	{
		g_rotX_angle += (ypos - g_lastY) * camera.GetMouseSensitivity();
		g_rotY_angle += (xoffset) * camera.GetMouseSensitivity();
	}

	g_lastX = xpos;
	g_lastY = ypos;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	glfwGetCursorPos(window, &g_lastX, &g_lastY);

	if (action == GLFW_PRESS)
		buttonDown = button;
	else
		buttonDown = -1;

	//if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) buttonDown = true;
	//if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) buttonDown = false;	
}