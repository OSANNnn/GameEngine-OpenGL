#pragma once

#include<glfw3.h>
#include "camera.h"

//callback to resize the window to the original size
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//callback for mouse position
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

//input handler
void processInput(GLFWwindow* window, Fly_Camera& camera);