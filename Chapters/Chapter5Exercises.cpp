#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// Settings
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;
const unsigned int COMPLAIN_SIZE = 512;
int success;
char infoLog[COMPLAIN_SIZE];


const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main() {\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
"}\0";

const char* orangeFragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main(){ \n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

const char* yellowFragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
"	FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\0";

int main() {
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw Window Creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Chapter 5 Execises", NULL, NULL);
	if (window == NULL) {
		std::cout << "FAILED TO CREATE GLFW WINDOW" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: Load all OpenGL function pointers
	// ----------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	// Build and compile shader program
	// --------------------------------
	// Vertex
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// Check for shader errors
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, COMPLAIN_SIZE, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Fragment Orange
	unsigned int fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderOrange, 1, &orangeFragmentShaderSource, NULL);
	glCompileShader(fragmentShaderOrange);
	// Check for errors
	glGetShaderiv(fragmentShaderOrange, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShaderOrange, COMPLAIN_SIZE, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Link Orange
	unsigned int shaderProgramOrange = glCreateProgram();
	glAttachShader(shaderProgramOrange, vertexShader);
	glAttachShader(shaderProgramOrange, fragmentShaderOrange);
	glLinkProgram(shaderProgramOrange);
	// Check for linking errors
	glGetProgramiv(shaderProgramOrange, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgramOrange, COMPLAIN_SIZE, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	
	glDeleteShader(fragmentShaderOrange);

	// Fragment Yellow
	unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderYellow, 1, &yellowFragmentShaderSource, NULL);
	glCompileShader(fragmentShaderYellow);
	// Check for errors
	glGetShaderiv(fragmentShaderYellow, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShaderYellow, COMPLAIN_SIZE, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Link Yellow
	unsigned int shaderProgramYellow = glCreateProgram();
	glAttachShader(shaderProgramYellow, vertexShader);
	glAttachShader(shaderProgramYellow, fragmentShaderYellow);
	glLinkProgram(shaderProgramYellow);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShaderYellow);


	// Set up vertex data and buffer(s) and configure vertex attributes
	// ----------------------------------------------------------------
	//float vertices[] = {
	//	 -0.45f,  0.5f, 0.0f, // top left
	//	 -0.7f,  0.2f, 0.0f, // bottom left
	//	 -0.2f,  0.2f, 0.0f, // bottom right
	//	  0.1f,  0.5f, 0.0f, // top right
	//	  0.3f,  0.2f, 0.0f
	//};
	//unsigned int indices[] = { // we start from 0
	//	0, 1, 2, // first triangle
	//	2, 3, 4  // second triangle
	//};

	//float vertices[] = {
	//	// first triangle
	//	-0.45f, 0.5f, 0.0f,
	//	-0.7f, 0.2f, 0.0f,
	//	-0.2f, 0.2f, 0.0f,
	//	// second triangle
	//	 0.1f, 0.5f, 0.0f,
	//	-0.2f, 0.2f, 0.0f,
	//	 0.3f, 0.2f, 0.0f
	//};

	float triangle_one[] = {
		-0.45f, 0.5f, 0.0f,
		-0.7f, 0.2f, 0.0f,
		-0.2f, 0.2f, 0.0f,
	};

	float triangle_two[] = {
		0.1f, 0.5f, 0.0f,
		-0.2f, 0.2f, 0.0f,
		0.3f, 0.2f, 0.0f
	};

	unsigned int VBOs[2], VAOs[2];// , EBO;
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);

	// glGenBuffers(1, &EBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and then configure vertex attribute(s)
	glBindVertexArray(VAOs[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_one), triangle_one, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_two), triangle_two, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);


	// Note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's
	// bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// remember: do not unbind the EBO while a VAO is active as the bound element buffer
	// is store in the VAO; keep the EBO bound.

	// You can unbind the VAO afterwards so other VAO call won't accidentally modify this VAO, but this rarely happens.
	// Modifing other VAOs requires a call to glBindVertexArray anyways we generally don't unbind VAOs nor VBOs when it's not necessary
	glBindVertexArray(0);

	// render loop
	//------------
	while (!glfwWindowShouldClose(window)) {
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.4f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw our first triangle
		glUseProgram(shaderProgramOrange);
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgramYellow);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//glDrawArrays(GL_TRIANGLES, 0, 6);
		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// swap buffers and poll IO events
		// -------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	
	}	

	// Deallocate all resources once they've outlived their purpose
	// ------------------------------------------------------------
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	//glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgramOrange);
	glDeleteProgram(shaderProgramYellow);

	glfwTerminate();


	return 0;

}

// Process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: Whenever the window size changed (by OS or user) this callback function executes
//---------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina display
	glViewport(0, 0, width, height);
}