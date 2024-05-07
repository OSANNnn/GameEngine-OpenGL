#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera.h"
#include "utils.h"
#include "Shader.h"
#include "buffers.h"

using namespace std;
using namespace Buffers;
using namespace glm;

//canvas size
const unsigned int width = 800;
const unsigned int height = 600;
//texture mix
float mixValue = 0.3f;

Fly_Camera camera(vec3(0.0f, 0.0f, 4.0f));

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float mouseLastX = 400;
float mouseLastY = 300;
bool firstMouse = true;


int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Learn opengGL", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}
	glViewport(0, 0, width, height);


	//float vertices[] = {
	//	//	  POSITION     ||		COLOR	  || TEXTURE COORD || "../../assets/textures/wall.jpg"
	//	 0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // top right (blue)
	//	 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // bottom right (green)
	//	-0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f, // bottom left (white)
	//	-0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f  // top left (red)
	//};

	//GLuint indices[] = {
	//	0, 1, 3,
	//	1, 2, 3
	//};

	float vertices[] = {
		//BACK
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // G
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // H
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // F
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // F
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // E
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // G
		//FRONT
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // C
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // D
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // B
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // B
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // A
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // C
		//EAST
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // A
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // E
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // G
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // G
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // C
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // A
		//WEST
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // B
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // F
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // H
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // H
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // D
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // B
		 //BOTTOM
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // G
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // H
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // D
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // D
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // C
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // G
		//TOP
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // E
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // F
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // B
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // B
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // A
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f  // E
	};

	VAO cubeVAO, lightsourceVAO;
	VBO cubeVBO;

	cubeVAO.Bind();
	cubeVBO.Bind();

	cubeVBO.Data(vertices, sizeof(vertices));
	//ebo.Data(indices, sizeof(indices));

	cubeVBO.SetAttrib(0, 3, sizeof(float) * 5, 0);
	cubeVBO.SetAttrib(1, 2, sizeof(float) * 5, 3 * sizeof(float));
	
	cubeVAO.UnBind();


	stbi_set_flip_vertically_on_load(true);
	Texture woodenBox;
	woodenBox.Bind();
	woodenBox.TexData("container.jpg");
	

	Shader program("default.vert", "default.frag");
	Shader lightShader("light.vert", "light.frag");
	program.Use();
	program.SetInt("texture1", 0);
	woodenBox.Activate(0);

	//uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	mat4 view = camera.getViewMatrix();
	mat4 projection(1.0f);
	mat4 model(1.0f);
	float aspect = (float)width / height;


	glEnable(GL_DEPTH_TEST);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//main render loop -----------------------------------------------------------------------------
	while (!glfwWindowShouldClose(window))
	{	
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//check for inputs
		processInput(window, camera);
		//rendering
		glClearColor(0.3f, 0.0f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//draw vertex
		program.Use();

		cubeVAO.Bind();
		
		view = camera.getViewMatrix();
		projection = perspective(radians(camera.m_Zoom), aspect, 0.1f, 100.0f);
		program.setMat4f("view", view);
		program.setMat4f("projection", projection);
		

		mat4 model = (1.0);
		model = translate(model, vec3(0.0f, 0.0f, 0.0f));
		program.setMat4f("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		//swap front and back buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//main render loop --------------------------------------------------------------------------END

	//delete everything
	cubeVAO.Delete();
	cubeVBO.Delete();
	lightsourceVAO.Delete();
	program.Delete();

	//clean memory and close the program
	glfwTerminate();
	return 0;
}