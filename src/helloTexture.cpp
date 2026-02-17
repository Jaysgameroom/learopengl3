#include "shader.h"
#include <cstddef>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <stb_image.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

float vertices[] = {
	-0.5f, -0.5f, 0.0f,	//bottom left
	0.5f, -0.5f, 0.0f, //bottom right
	0.0f,  0.5f, 0.0f //top
};

float texCoords[] = {
	0.0f, 0.0f,
	1.0f, 0.0f, 
	0.5f, 1.0f
};

unsigned int indices[] = {
	0, 1, 2
};

int main() {

	// Initialize and create window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGl", NULL, NULL);
	if (window == NULL){
		std::cout << "Failed to create Glfw window" << std::endl;
		glfwTerminate();
		return -1;
	}


	//Grab context and viewport for drawing
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}    

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//******************************Initialization******************************

	unsigned int VAO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO, TBO;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &TBO);
	glBindBuffer(GL_ARRAY_BUFFER, TBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(1);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	//******************************load image******************************
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char *data = stbi_load("assets/container.jpg", &width, &height, &nrChannels, 0); 
	if(!data){
		std::cout << "Failed to load texture" << std::endl;
		return -1;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);



	Shader shader = Shader("shader/vertex/texture.vert", "shaders/fragment/texture.frag");


	//main render loop	
	while(!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();    
	}

	glfwTerminate();
	return 0;
}



void framebuffer_size_callback(GLFWwindow* window, int width, int height){
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window){
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window, true);
	}
}
