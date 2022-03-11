#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

/*
	Everything in OpenGL is in 3D thus a large part of OpenGL's work
	is about transforming all 3D coordinates to 2D pixels that fit on
	your screen. 

	The graphic pipeline is what manage the transformation from 3D coordinates
	to 2D pixels that fit in the screen.

	The graphic pipeline takes as input a set of 3D coordinates and transforms
	these colored 2D pixels on the screen. The pipeline can be divided into
	several steps where each step's output is the input of the next. Each
	step has only one function and can be easily executed in parallel.
	
	Shaders are small programs ran on the GPU for each step of the pipeline.
	Some of them shaders are configurable to replace default shaders.
	Which gives the programmer more control over specific parts of the pipeline
	which is ALWAYS a good thing. Shaders are written in OpenGL Shading
	Language (GLSL).

	This is a representation of how the graphics pipeline works. All the 
	sections followed by a '*' are sections where we can inject our own shaders.

	vertex Data[] -> Vertex Shader* -> Shape Assembly -> Geometry Shader* ->
	Tests and Blending -> Fragment Shader* -> Rasterization

	Vertex Shader:  takes as input a single vertex and its main purpose
	is to transform 3D coordinates into different 3D coordinates (Helpful).
	More info later.

	Primitive Assembly: Takes all the vertex(ices) from the vertex shader
	and assembles all the point(s) in the primitive shape given.

	Geometry Shader: Takes the output of the primitive assembly.
	Generates other shapes from the input collection of vertices that 
	form a primitive by emitting new vertices to form new primitives.

	Rasterization Stage: Takes as input the output of the geometry shader
	and maps the resulting primitive(s) to the corresponding pixel on the
	screen, resulting in fragments for the fragment shader to use. A 
	fragment, btw in OpenGL is all the data required for OpenGL to 
	render a single pixel.

	Clipping: Discards all fragments that are outside the user view,
	increasing performance. 

	Fragment Shader: Calculates the final color of a pixel. This shader
	contains data about the 3D scene that it can use to calculate final 
	pixel color. Very advance.

	Alpha Test + Blending: Check the corresponding depth (and stencil)
	values of the fragment and uses those to check if the resulting
	fragment is in front or behind other objects and should be discarded.
	The stage also checks for alpha values (opacity) and blends the objects
	accordingly.

	Looks hard but for almost all the cases we only have to work with the vertex
	and gragment shader. The geometry shader is optional.

	In OpenGL we are required to define AT LEAST a vertex and fragment shader of
	our own (no default). It is, like, really hard to use.
	
*/


// We can fuck with vertex shaders. Very programmable.
// They use GLSL (OpenGL Shading Language) Where is the O? I don't know.
// This is a VERY basic source code.
const char* vertexShaderSource = "#version 330 core\n"  // Version declaration, specify we are using core-profile
"layout (location = 0) in vec3 aPos;\n"                 // Declaring all the input vertex attr in a 3D vector named aPos (customizable)
													    // We also specify the location of the variable (location = 0)
"void main() {\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0)\n"  // gl_Position is a type vec4 system variable. 
														// Because we have a vec3 we just assign each to where they belong the last one is 1.0 because...
"}\0";

// This is the fragment shader code source which like the
// Vertex uses GLSL as well. The fragment shader requires
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"                                    // only one output and that is a vec4
"void main() {\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"          // A color => Red: 1.0f, Green: 0.5, Blue: 0.2f, Alpha: 1.0f a very orange
"}\0";


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main() {
	// Initializing stuff 
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initializing GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Vertex Data -> normalized 3D coordinates ranging from -1.0 to 1.0
	// Any improper coordinate will be clipped. -2 will be clipped, pi will be clipped
	// It is called normalized device coordinates NDC
	// NDC gets transformed into screen-space coordinates via viewport transform
	float vertices[] = {
		//    x      y     z
			-0.5f, -0.5f, 0.0f,
			 0.5,  -0.5f, 0.0f,           // 3 Vertices aka triangle
			 0.0f,  0.5f, 0.0f 
	};

	// We create a vertex shader by creating  memory on the GPU
	// In it we store the vertex data, configure how OpenGL should interpret
	// the memory and specify how to send the data to the graphics card.
	// The vertex shader then processes as many vertices as we feel to give it.

	// Vertex Buffer Objects(VBO) can store a large number of vertices in the
	// GPU's memory. Which keep things efficient. Sending data to the graphic 
	// card is relatively slow.

	unsigned int VBO;			// Will not store the VBO but an ID to the memory
	// glGenBuffers( GLsizei n, GLuint *buffers)
	// n Specifies the number of buffer object names to be generated
	glGenBuffers(1, &VBO);      // Generate an ID and puts it in VBO variable

	// Binds an array with the ID store in the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Copies user-defined data into the currently bound buffer.
	// first argument is the type of buffer we want to copy data into. Look line 133.
	// The second specifies the size of the data in bytes.
	// The third parameter is the data.
	// The fourth is more poetic. GL_STATIC_DRAW basically tell the buffer we are going 
	// to set data into it only once and use it many times.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// In order to use a shader we need to compile its source dynamically
	unsigned int vertexShader;						 // Create a shader object
	vertexShader = glCreateShader(GL_VERTEX_SHADER); // Create an ID for a shader

	// Attach the shader source code to the shader object and compile the shader
	// First parameter is the shader to compile.
	// Second how many strings we're passing as source code.
	// Third the actual source code (as a reference of course)
	// Fourth specifies an array of string lengths NULL means null terminated \0
	// glShaderSource( GLuint shader, GLsizei count, const GLchar **string, cons GLint *length)
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // Attach
	glCompileShader(vertexShader);                              // Compile

	// Check if compilation was successful and if not shows error.
	int success;
	char infoLog[512];
	// Takes a peek and tells you if the compilation was a success
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "HOW DARE YOU!? BYE\n" << infoLog << std::endl;
	}

	// The fragmentshader compilation process is the same as the
	// vertex shader.

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // Instead of GL_VERTEX_SHADER
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "My GOODNESS! THE AUDACITY!! BYE\n" << infoLog << std::endl;
	}

	// A shader program object is the final linked version of multiple shaders
	// combined. To use the shaders we have to link them to a shader program object.
	// and then activate the program when rendering objects.
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();		// Creating the program and getting the program ID reference

	glAttachShader(shaderProgram, vertexShader);   // Attach
	glAttachShader(shaderProgram, fragmentShader); // Attach

	glLinkProgram(shaderProgram);                  // Link

	// Checking if we fucked it up
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "*GASP* GOODBYE SIR... I SAID GOODBYE\n" << infoLog << std::endl;
	}

	// Now we can use the program 
	glUseProgram(shaderProgram);

	// Deleting the Shaders because now that we linked them with 
	// the program we don't need them anymore.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	while (!glfwWindowShouldClose(window)) {

		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}


	glfwTerminate();

	return 0;
}