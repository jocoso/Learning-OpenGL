/*
	Shaders are little programs that rest on the GPU.
	They are run for each specific session of the graphic pipeline
	Shaders are nothing more than programs transforming inputs to outputs.
	Shaders do not communicate with each other.
	Shaders are like brushes in that regard.
*/

//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//
//#include "extras/chapter6/chapter6shaderclass.h";
//// Prototypes
//void framerbuffer_size_callback(GLFWwindow *window, int width, int height);
//void processInput(GLFWwindow *window);
//
//// Settings
//const unsigned int WIDTH = 800;
//const unsigned int HEIGHT = 600;
//const unsigned int COMPLAIN_SIZE = 512;
//int success;
//char infoLog[COMPLAIN_SIZE];
//
//// Shaders
//const char *vertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"out vec4 vertexColor;\n" // Specifiy a color output to the fragment shader
//"void main() {\n"
//"	gl_Position = vec4(aPos, 1.0);\n"
//"	vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
//"}\0";
//
//const char *fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"in vec4 vertexColor;\n"
//"void main() {\n"
//"	FragColor = vertexColor;\n"
//"}\0";
//
//// Uniforms are global or unique per shader program object.
//// Values in uniform will remain until reset or updated.
//// XXX: If you declare a uniform and don't use it the compiler will silently remove it.
//const char *uniformFragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"uniform vec4 ourColor;\n" // We set this variable in OpenGL code.
//"void main() {\n"
//"	FragColor = ourColor;\n"
//"}\0";
//
//const char *complexVertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"layout (location = 1) in vec3 aColor;\n"
//"out vec3 ourColor;\n"
//"void main() {\n"
//"	gl_Position = vec4(aPos, 1.0);\n"
//"	ourColor = aColor;\n"
//"}\0";
//
//const char *complexFragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"in vec3 ourColor;\n"
//"void main() {\n"
//"	FragColor = vec4(ourColor, 1.0);\n"
//"}\0";
//
//// Vertices
//float vertices[] = {
//		-0.45f, 0.5f, 0.0f,
//		-0.7f, 0.2f, 0.0f,
//		-0.2f, 0.2f, 0.0f,
//};
//
//float vertices2[] = {
//	//     positions     //   colors
//	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
//	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
//	 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
//};
//
//int malin() {
//	// Initializing stuff 
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//
//	// Window Creation
//	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
//	if (window == NULL) {
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	// Initializing GLAD
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	 Shaders always begin with a version declaration followed by
//	 a list of inputs and outputs available and its main function.
//	 Shaders follow a structre:
//
//		#version version_name
//	  in type in_variable_name;
//		in type in_variable_name;
//	  out type out_variable_name;
//	  uniform type uniform_name;
//	  void main() {
//	      // process input(s) and do some weird graphics stuff
//	      ...
//	      // output processed stuff to output variable
//	      out_variable_name = weird_stuff_we_processed;
//	  }
//
//	 Specifically talking about vertex shader, each input variable is also
//	 know as a vertex attribute.
//	 The maximum bumber of vertex attributes is limited by the hardware.
//	 OpenGL guarantees at leas 16 4-component vertex attribues
//	 but some hardware may allow for more by querying
//	 GL_MAX_VERTEX_ATTRIBS 
//	int nrAttributes;
//	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
//
//	std::cout << "Maximum number of vertex attributes supported: " << nrAttributes
//		<< std::endl;
//
//	 6.2 Types
//	 GLSL had data types
//	 It has most of the default basic types from C
//	 (int, float, double, uint and bool)
//	 GLSL also has two container types: vectors and matrices.
//	
//	 6.2.1 Vectors
//	 Vectors in GLSL is a 1, 2, 3, 4 component container
//	 They can take the following form (n should be replaced with the ints above)
//	 vecn: the default vector of n floats
//	 bvecn: a vector of n booleans
//	 ivecn: a vector of n integers
//	 uvecn: a vector of n unsigned integers
//	 dvecn: a vector of n double components
//	
//	 Vectors can be accessed via .x, .y, .z and .w in the case of 4 dimensional vectors
//	 GLSL also allows for the use of rgba for colors or stpq for texture.
//	 It also allows for swizzling which allows us to use the following syntax:
//			vec2 someVec;
//			vec4 differentVec = someVec.xyxx;
//			vec3 anotherVec   = differentVec.zyw;
//			vec4 otherVec     = someVec.xxx + anotherVec.yxzy;
//	 
//	 Combining 4 letters we create a new vector of the same type.
//	 It won't work if the components miss one or more of the components.
//	 
//			vec2 vect = vec2(0.5, 0.7);
//			vec4 result = vec4(vect, 0.0, 0.0);
//			vec4 otherResult = vec4(result.xyz, 1.0);
//	 
//	 Vectors are flexible.
//	
//
//	 6.3 Ins and Outs
//	 GLSL define in and out keywords for inputs and outputs.
//	 Each shader can specify inputs and outputs using those keywords.
//	 Whatever an ouput variable matches with an input variables of the next shader they are passed along.
//	 The vertex and fragment shader differ.
//	 The vertex Shader should receive an input.
//	 The vertex Shader receives an input straight from the vertex data.
//	 To define how is organized we specify the input variable with the location metadata.
//	 layout (location = 0).
//	 
//	 We could omit layout ( location = 0 ) and replace it with the query glGetAttribLocation.
//	 The fragment shader requires a vec4 for color output.
//	 Fragment shaders needs to generate a final output color.
//	 If the color is undefined the fragment will render white or black
//	 To send data between shaders we need to declare an output with a similar input than the receiving shader.
//	 When the types and names are equal on both sides they are linked example
//			[VERTEX SHADER]
//	 
//			#version 330 core
//			layout (location = 0) in vec3 aPos;  // Position has attribute position 0
//	 
//			out vec4 vertexColor; // Specify a color to the fragment shader
//	 
//			void main() {
//				gl_Position = vec4(aPos, 1.0); // We give a vec3 to vec4's constructor
//				vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // Output variable to dark-red
//			}
//	 
//			[FRAGMENT SHADER]
//			
//			#version 330 core
//			out vec4 FragColor;
//	 
//			in vec4 vertexColor; // input variable from vs (same name and type)
//	 
//			void main() {
//				FragColor = vertexColor;
//			}
//
//	
//	// Build and Compile Shaders
//	// Vertex
//	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertexShader, 1, &complexVertexShaderSource, NULL);
//	glCompileShader(vertexShader);
//	// Checking
//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//	if (!success) {
//		glGetShaderInfoLog(vertexShader, COMPLAIN_SIZE, NULL, infoLog);
//		std::cout << infoLog << std::endl;
//	}
//
//	// Fragment
//	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, &complexFragmentShaderSource, NULL);
//	glCompileShader(fragmentShader);
//	// Checking
//	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//	if (!success) {
//		glGetShaderInfoLog(fragmentShader, COMPLAIN_SIZE, NULL, infoLog);
//		std::cout << infoLog << std::endl;
//	}
//
//	// Program
//	unsigned int programShader = glCreateProgram();
//	glAttachShader(programShader, vertexShader);
//	glAttachShader(programShader, fragmentShader);
//	glLinkProgram(programShader);
//	// Checking
//	glGetProgramiv(programShader, GL_COMPILE_STATUS, &success);
//	if (!success) {
//		glGetProgramInfoLog(programShader, COMPLAIN_SIZE, NULL, infoLog);
//		std::cout << infoLog << std::endl;
//	}
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//
//	// VBO, VAO
//	unsigned int VBO, VAO;
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//
//	Shader shader("./extras/chapter6/shader.vs", "./extras/chapter6/shader.fs");
//	float counter = 0;
//	float add = 0.02;
//
//	// Render Loop
//	while (!glfwWindowShouldClose(window)) {
//		// Input
//		processInput(window);
//		
//		// Render
//		glClearColor(0.2f, 0.4f, 0.1f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		// Draw
//		if (counter >= 1 || counter <= -1) add *= -1;
//		counter += add;
//
//		shader.use();
//		shader.setFloat("hPos", counter);
//		glBindVertexArray(VAO);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//		 glUseProgram(programShader);
//		 float timeValue = glfwGetTime();
//		 returns a value between 0.0, -1 and 0
//		 float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
//		 Returns -1 if it cannot find the location
//		 int vertexColorLocation = glGetUniformLocation(programShader, "ourColor");
//		 Changing uniform of current used program
//		 Changing the last letter on glUniform4f to...
//		 f: float
//		 i: int
//		 ui: unigned integer
//		 3f: three floats
//		 fv: float vector/array
//		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
//		glBindVertexArray(VAO);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//
//		 SWAP & POLL
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	// Deallocation
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VAO);
//	glDeleteProgram(programShader);
//
//	return 0;
//	
//}
//
//// Process Input
//void processInput(GLFWwindow* window) {
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//}
//
//// Resize Window
//void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//	glViewport(0, 0, width, height);
//}