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
#include "GameObject.h"
#include "Renderer.h"
#include "Scene.h"

const unsigned int WINDOW_WIDTH = 1024;
const unsigned int WINDOW_HEIGHT = 780;
const float NEAR_PLANE = 0.1f;
const float FAR_PLANE = 100.0f;

bool WIREFRAME_SETTING = false;

std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3(0.0f, 1.5f, 6.0f));
std::shared_ptr<Material> g_material = std::make_shared<Material>();
std::shared_ptr<Light> g_light = std::make_shared<Light>();

double g_lastX, g_lastY;

int buttonDown = -1;

float g_rotX_angle = 0.0f;
float g_rotY_angle = 0.0f;

double deltaTime = 0.0f;
double lastTime = 0.0f;

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
	
	// shaders
	std::shared_ptr<Shader> phongShader(new Shader("res/shaders/PhongVertex.shader", "res/shaders/PhongFragment.shader"));
	Shader BasicShader("res/shaders/BasicVertex.shader", "res/shaders/BasicFragment.shader");
	Shader gridShader("res/shaders/GridVertex.shader", "res/shaders/GridFragment.shader");

	// Meshes
	std::shared_ptr<Mesh>cube_mesh = std::make_shared<Mesh>(cube::vertices, cube::triangles);
	std::shared_ptr<Mesh>icosphere_mesh = std::make_shared<Mesh>();

	std::unique_ptr<GameObject>cube = std::make_unique<GameObject>(cube_mesh, g_material);
	std::unique_ptr<GameObject>icosphere = std::make_unique<GameObject>(icosphere_mesh, g_material);

	std::shared_ptr<std::vector<std::unique_ptr<GameObject>>> renderObjects =
		std::make_shared<std::vector<std::unique_ptr<GameObject>>>();

	(*renderObjects).push_back(std::move(cube));
	(*renderObjects).push_back(std::move(icosphere));

	Renderer renderer(renderObjects, g_light);
	renderer.AddShader(phongShader);

	Scene scene(camera);

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

		}

		//glm::mat4 model = glm::mat4(1.0f);

		//glm::vec3 pos = glm::vec3(0.0f, 1.0f, 0.0f);

		//model = glm::scale(model, glm::vec3(1.0f));
		//model = glm::translate(model, pos);
		//model = glm::rotate(model, glm::radians(g_rotX_angle), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(g_rotY_angle), glm::vec3(0.0f, 1.0f, 0.0f));

		//(*phongShader).SetUniformMat4f("model", model);

		renderer.UpdateAll(g_rotX_angle, g_rotY_angle);
		renderer.RenderAll(*camera);

		scene.SetGridUniforms(gridShader);
		scene.DrawGrid();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

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
		(*camera).ProcessKeyboard(Cam::Camera_Movement::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		(*camera).ProcessKeyboard(Cam::Camera_Movement::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		(*camera).ProcessKeyboard(Cam::Camera_Movement::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		(*camera).ProcessKeyboard(Cam::Camera_Movement::RIGHT, deltaTime);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
	if (key == GLFW_KEY_E && action == GLFW_PRESS) setWireframe();
	if (key == GLFW_KEY_R && action == GLFW_PRESS) (*camera).ResetPosition();
}

void setWireframe()
{
	WIREFRAME_SETTING = !WIREFRAME_SETTING;
}

void cursor_callback(GLFWwindow* window, double xpos, double ypos)
{
	double xoffset = xpos - g_lastX;
	double yoffset = g_lastY - ypos; // reversed since y-coordinates go from bottom to top

	if (buttonDown == 1) (*camera).ProcessMouseMovement(xoffset, yoffset, deltaTime);

	if (buttonDown == 0)
	{
		g_rotX_angle += (float)((ypos - g_lastY) * (*camera).GetMouseSensitivity());
		g_rotY_angle += (float)((xoffset) * (*camera).GetMouseSensitivity());

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
	(*camera).ProcessMouseScroll(yoffset);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	glfwGetCursorPos(window, &g_lastX, &g_lastY);

	if (action == GLFW_PRESS)
		buttonDown = button;
	else
		buttonDown = -1;	
}