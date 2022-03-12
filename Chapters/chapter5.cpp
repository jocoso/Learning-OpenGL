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
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"  // gl_Position is a type vec4 system variable. 
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

	// [ Example for triangle ]
	// Vertex Data -> normalized 3D coordinates ranging from -1.0 to 1.0
	// Any improper coordinate will be clipped. -2 will be clipped, pi will be clipped
	// It is called normalized device coordinates NDC
	// NDC gets transformed into screen-space coordinates via viewport transform
	//float vertices[] = {
	//	//    x      y     z
	//		-0.5f, -0.5f, 0.0f,
	//		 0.5,  -0.5f, 0.0f,           // 3 Vertices aka triangle
	//		 0.0f,  0.5f, 0.0f 
	//};

	// [ Example for rectangle ]
	// We are drawing a rectangle by using two triangles
	// This is not efficient to do a better solutions is
	// to store only the unique vertices and then specify 
	// the order at which we want to draw these vertices in
	// The Element Buffer Object allows us to do just that
	//
	//float sqrtVertices[] = {
	//	// first triangle
	//	 0.5f,  0.5f, 0.0f, // top right
	//	 0.5f, -0.5f, 0.0f, // bottom right
	//	-0.5f,  0.5f, 0.0f, // top left
	//	// second triangle
	//	 0.5f, -0.5f, 0.0f, // bottom right
	//	-0.5f, -0.5f, 0.0f, // bottom left
	//	-0.5f,  0.5f, 0.0f  // top left
	//};
	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f,  // top left
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	

	// We create a vertex shader by creating  memory on the GPU
	// In it we store the vertex data, configure how OpenGL should interpret
	// the memory and specify how to send the data to the graphics card.
	// The vertex shader then processes as many vertices as we feel to give it.

	// Vertex Buffer Objects(VBO) can store a large number of vertices in the
	// GPU's memory. Which keep things efficient. Sending data to the graphic 
	// card is relatively slow.

	unsigned int VBO, VAO;			// Will not store the VBO/VAO but an ID to the memory
	
	glGenVertexArrays(1, &VAO);
	// glGenBuffers( GLsizei n, GLuint *buffers)
	// n Specifies the number of buffer object names to be generated
	glGenBuffers(1, &VBO);      // Generate an ID and puts it in VBO variable


	// -- 0. Copy our vertices array in the buffer for OpenGL to use --
	// Binds an array with the ID store in the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);


	// A vertex array object can be bound just like a vertex buffer object
	// Anny subsequent vertex attribute call from that point on will be
	// stored inside the VAO. This makes switching between different vertex data
	// and attribute configuration as easy as binding a different VAO.
	// All the state we just set is stored inside the VAO.

	// To use VAO all you have to do is bind the VAO using glBindVertexArray.
	// From that moment on you can bind/configure the corresponding VBO's
	// attribute pointer and then unbind the VAO for later use. When we want
	// to draw something we bind the VAO with the preferred settings before
	// drawing the object.
	// 

	// 1. bind Vertex Array Object
	glBindVertexArray(VAO);

	// Copies user-defined data into the currently bound buffer.
	// first argument is the type of buffer we want to copy data into. Look line 133.
	// The second specifies the size of the data in bytes.
	// The third parameter is the data.
	// The fourth is more poetic. GL_STATIC_DRAW basically tell the buffer we are going 
	// to set data into it only once and use it many times.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// --------------------------------------------------------------

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



	// The vertex shader let us specify any input in the form of
	// Vertex attributes. However, we need to manually specify what part of 
	// the input data goes to which vertex attribute in the vertex shader.
	// Which means we should tell OpenGL how to interpret the vertex data
	// before we can render.

	// |     vertex1     |     vertex2     |     vertex3     |
	// |  x  |  y  |  z  |  x  |  y  |  z  |  x  |  y  |  z  |
	// 0     4     8     12    16    20    24    28    32    36  Byte

	// Position data is store as 32-bit (4 byte) floating point values.
	// Each position is composed of 3 values.
	// No space or other values between each set of 3 values. They are
	// tightly packed in the array.
	// The first value in the data is at the beginning of the buffer

	// This is how we tell openGL how to interpret the vertex data.
	
	// The first parameter specify the vertex attribute we want to configure
	// The position of the vertex attribute was specified in the shader source
	// as (location = 0) thus we pass a 0.

	// The second parameter specify the size of the vertex attribute. Because it is 
	// a vec3 it is composed of 3 values, thus we wrote 3.

	// The third parameter specifies the type of data we are dealing with.
	// In this case we are dealing with floats because in GLSL vec* consists set of floats
	// so we pass GL_FLOAT

	// Fourth parameter specifies if we want the data normalized. 
	// If we were inputting intsor bytes and we set them to GL_TRUE
	// the integer data is normalized to 0 or -1 depending if the data
	// is signed or not. 1 if it is a float.

	// Fifth parameter is the stride which is the space between consecutive 
	// vertex attributes. Since the vertex array are so well packed together
	// and each contains 3 attributes we can safely multiply the data type
	// of each attribute (float) by 3.

	// The Sixth parameter specify a offset of the first component of the first
	// generic vertex attribute in the array in the data store of the buffer
	// currently bound to the GL_ARRAY_BUFFER target. The initial value is 0.
	// If it is not NULL, a non-zero named buffer object must be bound to the 
	// GL_ARRAY_BUFFER target with glBindBuffer.
	
	// 1. then set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);


	// 2. use our shader program when we want to render and object
	glEnableVertexAttribArray(0);

	// We will have to repeat process 1 to 3 everytime we want to draw an object.


	// [ Example for rectangle ] 

	unsigned int EBO;
	// Very similar to VBO and VAO we create the Element buffer
	glGenBuffers(1, &EBO);

	// Then we bind it with BindBuffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// Same thing as the VBO we call glBufferData but this time
	// we pass GL_ELEMENT_ARRAY_BUFFER as the first parameter
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);




	while (!glfwWindowShouldClose(window)) {

		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//// Draw the object
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		//// Draws primitives using the currently active shader.
		//// glDrawArrays function takes 3 parameter
		//// 1. Primitive we would like to draw... a triangle 
		//// 2. The starting location of the vertex array or 0 for this example
		//// 3. How many vertices we want to draw, which is 3 of course.
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}


	glfwTerminate();

	return 0;
}