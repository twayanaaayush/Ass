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
#include "Light.h"
#include "Material.h"
//#include "MousePicking.h"

const unsigned int WINDOW_WIDTH = 1024;
const unsigned int WINDOW_HEIGHT = 780;

bool WIREFRAME_SETTING = false;

Camera camera(glm::vec3(0.0f, 1.5f, 6.0f));
Material g_material;

double g_lastX, g_lastY;

int buttonDown = -1;

float nearPlane = 0.1f, farPlane = 100.0f;

float g_rotX_angle = 0.0f;
float g_rotY_angle = 0.0f;

double deltaTime = 0.0f;
double lastTime = 0.0f;

//glm::mat4 projection = glm::perspective(camera.GetZoom(), (float)(WINDOW_WIDTH / WINDOW_HEIGHT), nearPlane, farPlane);
//glm::mat4 view = camera.GetViewMatrix();
//glm::vec3 pos = glm::vec3(0.0f, 1.0f, 0.0f);

Light g_light = {
	glm::vec3(2.0f, 2.0f, 2.0f),
	glm::vec3(0.2f, 0.2f, 0.2f),
	glm::vec3(0.5f, 0.5f, 0.5f),
	glm::vec3(1.0f, 1.0f, 1.0f)
};


// function declaration
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

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	// shaders
	Shader BasicShader("res/shaders/BasicVertex.shader", "res/shaders/BasicFragment.shader");
	Shader phongShader("res/shaders/PhongVertex.shader", "res/shaders/PhongFragment.shader");
	//Shader gridShader("res/shaders/GridVertex.shader", "res/shaders/GridFragment.shader");

	// Meshes
	Mesh cube(cube::vertices, cube::triangles);
	Mesh icosphere;

	/*std::vector<Vertex> grid = {
		{glm::vec3(1.0f,  1.0f, 0.0f)},
		{glm::vec3(1.0f, -1.0f, 0.0f)},
		{glm::vec3(-1.0f, -1.0f, 0.0f)},
		{glm::vec3(-1.0f,  1.0f, 0.0f)}
	};

	std::vector<Triangle> gridIndices = {
		{0,  1,  3},
		{1,  2,  3}
	};

	VertexArray* VAO_2 = new VertexArray();
	VertexBuffer* VBO_2 = new VertexBuffer(&grid[0], 4 * 3 * sizeof(Vertex));
	IndexBuffer* EBO_2 = new IndexBuffer(reinterpret_cast<unsigned int*>(&gridIndices[0]), gridIndices.size()*3);
	BufferLayout* layout_2 = new BufferLayout();

	layout_2->Add<float>(3);

	VAO_2->AddBuffer(*VBO_2, *layout_2);
	VAO_2->Unbind();*/

	while (!glfwWindowShouldClose(window))
	{
		double  currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		processInput(window, deltaTime);

		glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (WIREFRAME_SETTING)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			BasicShader.Use();

			BasicShader.SetUniformVec4f("color", glm::vec4(1.0f, 0.5f, 0.31f, 1.0f));
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			phongShader.Use();
			phongShader.SetUniformVec3f("light.position", g_light.position);
			phongShader.SetUniformVec3f("light.ambient", g_light.ambient);
			phongShader.SetUniformVec3f("light.diffuse", g_light.diffuse);
			phongShader.SetUniformVec3f("light.specular", g_light.specular);
			phongShader.SetUniformVec3f("viewPos", camera.GetPosition());
			g_material.SetUniforms(phongShader);
		}

		glm::mat4 projection = glm::perspective(camera.GetZoom(), (float)(WINDOW_WIDTH / WINDOW_HEIGHT), nearPlane, farPlane);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);

		glm::vec3 pos = glm::vec3(0.0f, 1.0f, 0.0f);

		model = glm::scale(model, glm::vec3(1.0f));
		model = glm::translate(model, pos);
		model = glm::rotate(model, glm::radians(g_rotX_angle), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(g_rotY_angle), glm::vec3(0.0f, 1.0f, 0.0f));

		phongShader.SetUniformMat4f("projection", projection);
		phongShader.SetUniformMat4f("view", view);
		phongShader.SetUniformMat4f("model", model);

		// draw cube
		//cube.Draw();

		// draw icosahedron
		icosphere.Draw();


		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//gridShader.Use();
		//gridShader.SetUniform1f("nearPlane", nearPlane);
		//gridShader.SetUniform1f("farPlane", farPlane);
		//gridShader.SetUniformMat4f("PROJECTION", PROJECTION);
		//gridShader.SetUniformMat4f("VIEW", VIEW);

		//VAO_2->Bind();
		//EBO_2->Bind();
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//delete VAO_2;
	//delete VBO_2;
	//delete EBO_2;
	//delete layout_2;

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
}

void cursor_callback(GLFWwindow* window, double xpos, double ypos)
{
	double xoffset = xpos - g_lastX;
	double yoffset = g_lastY - ypos; // reversed since y-coordinates go from bottom to top

	if (buttonDown == 1) camera.ProcessMouseMovement(xoffset, yoffset, deltaTime);

	if (buttonDown == 0)
	{
		g_rotX_angle += (float)((ypos - g_lastY) * camera.GetMouseSensitivity());
		g_rotY_angle += (float)((xoffset) * camera.GetMouseSensitivity());

		//glm::vec3 ray_wor = get_ray_from_mouse(WINDOW_WIDTH, WINDOW_HEIGHT, projection, view, xpos, ypos);

		//int closest_sphere_clicked = -1;
		//float closest_intersection = 0.0f;
		//float t_dist = 0.0f;

		//if (ray_sphere(camera.GetPosition(), ray_wor, pos, 1.0f, &t_dist)) {
		//	// if more than one sphere is in path of ray, only use the closest one
		//	if (closest_sphere_clicked == -1 || t_dist < closest_intersection) {
		//		closest_sphere_clicked = 1;
		//		closest_intersection = t_dist;

		//		std::cout << closest_sphere_clicked << ", " << closest_intersection << std::endl;
		//	}

		//}
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
}