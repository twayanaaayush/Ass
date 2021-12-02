#include <iostream>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

void frameBuffer_size_callback(GLFWwindow* window, int width, int height);
void processInputs(GLFWwindow* window);

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "ASS", nullptr, nullptr);
	
	if ( window == nullptr )
	{
		std::cout << "Failed to create a window." << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frameBuffer_size_callback);

	if ( !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) )
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	while ( !glfwWindowShouldClose(window) )
	{
		processInputs(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

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

void processInputs(GLFWwindow* window)
{
	if ( glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ) {
		glfwSetWindowShouldClose(window, true);
	}
}