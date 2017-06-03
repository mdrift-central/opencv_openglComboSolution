#include <iostream>
#define GLEW_STATIC
#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include"Shader.h"
#include <SOIL2\SOIL2.h>
using namespace std;

const GLint WIDTH = 800, HEIGHT = 600;


int main(){

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	if (nullptr == window){
	
		cout << "Failed to initiate GLFW Window" << endl;
		glfwTerminate();

		return EXIT_FAILURE;

	
	}
	
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit()){

		cout << "Failed to Initiate GLEW" << endl;
		return EXIT_FAILURE;
	}

	glViewport(0, 0, screenWidth, screenHeight);

	Shader ourShader("core.vs", "core.frag");


	GLfloat vertices[] = {

		// position          // color
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f,0.0f,// bottom left
		-0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  
		0.0f, 0.5f, 0.0f,    0.0f, 0.0f, 1.0f

	};

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	while (!glfwWindowShouldClose(window)){
	
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f );
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.Use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		// Draw OpenGL Stuff
	
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();

	return EXIT_SUCCESS;
}
