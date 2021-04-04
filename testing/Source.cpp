#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <iostream>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

float firstTriangle[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f,  0.5f, 0.0f,
	 0.0f,  1.0f, 0.0f
};
float secondTriangle[] = {
	 -0.2f,  -0.2f, 0.0f,
	-0.5f, -0.7f, 0.0f,
	 0.5f, -0.7f, 0.0f
};

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* win = glfwCreateWindow(1920, 1080, "testing", NULL, NULL);

	if (win == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(win);
	glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	int vertexShader = glCreateShader(GL_VERTEX_SHADER),
		orangeFragShader = glCreateShader(GL_FRAGMENT_SHADER),
		yellowFragShader = glCreateShader(GL_FRAGMENT_SHADER),
		orangeShaderProg = glCreateProgram(),
		yellowShaderProg = glCreateProgram();

	unsigned int VBO[2], VAO[2];

	glGenBuffers(2, VBO);
	glGenVertexArrays(2, VAO);


	//������ ����������� ���������
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	/*    �������� �1: ���������, ����� ������� ������� �� ����� ���������. �������, ��� �� ������� ������������ ������� ���������� �������� � ��������� ������� ��� ������ layout (location = 0). ��������� �����, �������������� ���������� �������� ��������������� � 0, �, ��������� �� ����� �������� ������ � ���� ������� �������, �� �������� � �������� ��������� �������� 0.

   �������� �2: ���������� ������ ���������� ��������. �� ����� ��� vec3, ������� ������� �� 3-� ��������.

   �������� �3: ��������� ��� ������ GL_FLOAT (�.�. vec* � GLSL ������� �� �������� ���� � ��������� ������).

   �������� �4: ���������, ����� �� ��, ����� ���� ������ ���� �������������. ���� �� ������ ������������� ���� ������ (int, byte) � ���������� ��� ��� �������� GL_TRUE, �� ������������� unsigned ������ ���������� � 0 (��� � -1 ��� ����� ������ signed) � � 1 ��� �������������� � ��� float. ��� �� ����� ��������� � ������ �������, ������� �� ������� �������� ������� ��������� ��� GL_FALSE.

   �������� �5: �������� ��� ��� (����. �stride�) � ������� ��� � ������������ ����� ����������������� ���������� ������. ��������� ��������� ����� ������ �������������� ������� ��������� �� ���������� 3*sizeof(float), �� ��������� ��� �������� ��� ���. �������� ��������, ��������� �� �����, ��� ������ ������ �������� (��� �������� ������������ ����� ��������� ��������� �������� �������), �� ����� �� ����� ������� �������� ���� ��� 0, ����� ��������� OpenGL ������ ���������� ��� (��� �������� ������ �����, ����� �������� ������ ���������). ������ ���, ����� �� ����� ���� � ������� ����������� ��������� ���������, ����� ��������� ���������� ���������� ����� ������ ��������� (������� �������� ������� �� ���������� ��������� �����).
	*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);



	//������ ����������� ���������
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);


	const char
		* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0",

		* orangeFragShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0",

		* yellowFragShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 1.0f, 0.0f, 0.0f); \n"
		"}\n\0";

	//��������� ������
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	//����������� ������(orange)
	glShaderSource(orangeFragShader, 1, &orangeFragShaderSource, nullptr);
	glCompileShader(orangeFragShader);

	//����������� ������(yellow)
	glShaderSource(yellowFragShader, 1, &yellowFragShaderSource, nullptr);
	glCompileShader(yellowFragShader);

	//���������� �������� � ���� ���������(orange)
	glAttachShader(orangeShaderProg, vertexShader);
	glAttachShader(orangeShaderProg, orangeFragShader);
	glLinkProgram(orangeShaderProg);


	//���������� �������� � ���� ���������(yellow)
	glAttachShader(yellowShaderProg, vertexShader);
	glAttachShader(yellowShaderProg, yellowFragShader);
	glLinkProgram(yellowShaderProg);

	glDeleteShader(vertexShader);
	glDeleteShader(orangeFragShader);

	/*������� ���� ���������*/
	while (!glfwWindowShouldClose(win)) {

		processInput(win);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/*�������� ���*/
		glUseProgram(orangeShaderProg);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		glUseProgram(yellowShaderProg);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(win);
		glfwPollEvents();
	}
	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);

	glfwTerminate();
	return 0;
}




void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}