#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include "shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// ���������
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;




float vert[] = {
	 0.5f, -0.5f, 0.0f,      1.0f, 0.0f, 0.0f,   // ������ ������ �������
	-0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,   // ������ ����� �������
	 0.0f,  0.5f, 0.0f,		 0.0f, 0.0f, 1.0f    // ������� �������
};

int main()
{
	


	// glfw: ������������� � ����������������
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // ���������������� ��� ������, ���� ����������� macOS
#endif

	// glfw: �������� ����
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "testing", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: �������� ���� ���������� �� OpenGL-�������
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// �������������� ����� ��������� ���������
	Shader myShader("./shaders/vertex.vs", "./shaders/fragment.fs");

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// ������� ��������� ������ ���������� �������, ����� ��������� � ������������� ��������� �����(�), � ����� ������������� ��������� �������(�)
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	// �� ������ �������� �������� V�� ����� �����, ����� ������ ������ V�� �������� �� �������� ���� VAO (�� �������� �������� ����� ���������).
	// ����������� ������ VAO ������� ����� glBindVertexArray(), ������� �� ������ �� ������� �������� VAO (��� VBO), ����� ��� �� ��������� ��������
	// glBindVertexArray(0);


	// ���������� VAO (�� ��� ������, �� �� ������� ��� ��� ��� ��� �����������).
	// ��������� � ��� ���� ������ ���� V��, �� �� ����� ������� ��� �������, ������ ��� ��������������� ��������������� �����������
	glBindVertexArray(VAO);
	float offset = 0.3f;
	
	// ���� ����������
	while (!glfwWindowShouldClose(window))
	{
		// ��������� �����
		processInput(window);

		// ���������
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// ����������, ��� ������������ ��������� ��������� (������, ��� �������� glUniform())
		

		// ���������� ��������� uniform-����������
	

		// ��������� ������������
		myShader.use();
		myShader.setFloat("xOffset", offset);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// glfw: ����� ���������� front- � back- �������. ������������ ������� �����\������ (���� �� ������/�������� ������, ��������� ������ ���� � �.�.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// �����������: ����������� ��� �������, ��� ������ ��� ��������� ���� ��������������
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// glfw: ����������, ������������ ���� ����� ��������������� GLFW-��������
	glfwTerminate();
	return 0;
}

// ��������� ���� ������� �����: ������ GLFW � �������/���������� ������ ���� � ������ ����� � ��������������� ��������� ������ �������
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: ������ ���, ����� ���������� ������� ���� (������������� ��� ������������ ��������), ���������� ������ callback-�������
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// ����������, ��� ���� ��������� ������������� ����� �������� ����.
	// �������� ��������, ������ ����� ����������� ������, ��� �������, �� Retina-��������
	glViewport(0, 0, width, height);
}