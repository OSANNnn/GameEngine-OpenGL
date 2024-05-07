#include "utils.h"
#include <glm/glm.hpp>

extern Fly_Camera camera;
extern float deltaTime;
extern float mixValue;
extern float mouseLastX;
extern float mouseLastY;
extern bool firstMouse;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		mouseLastX = xpos;
		mouseLastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - mouseLastX;
	float yoffset = mouseLastY - ypos;

	mouseLastX = xpos;
	mouseLastY = ypos;

	camera.processMouseMovement(xoffset, yoffset, false);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.processMouseScroll((float)yoffset);
}

void processInput(GLFWwindow* window, Fly_Camera& camera)
{
	const float cameraSpeed = 2.5f * deltaTime;

	//window close
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	//camera controls
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.processKeyboard(FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.processKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.processKeyboard(STRAFE_LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.processKeyboard(STRAFE_RIGHT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		camera.processKeyboard(STRAFE_UP, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		camera.processKeyboard(STRAFE_DOWN, deltaTime);
	}

	//texture mix
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		if (mixValue < 1.0f) mixValue += 0.01f;
		else return;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		if (mixValue > 0.0f) mixValue -= 0.01f;
		else return;
	}
}

