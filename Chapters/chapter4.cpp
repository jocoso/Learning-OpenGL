#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


// Step 1 to make a resizable window
// This function makes that whenever the window changes size, GLFW calls
// this function and fills in the proper arguments for you.
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// Tell OpenGL the size of the rendering window so it knows how we want
	// to display the data and coordinates with respect to the window.

	// the first two parameters are the location of the lower left corner 
	// of the window.

	// The third is the width and the fourth is the height

	// OpenGL uses the data given by this function to transform normalized 2D coordinates
	// to coordinates your screen can show.
	glViewport(0, 0, width, height);
}


// Step 1 to input control
// All input processes will be here to keep everything neat.
void processInput(GLFWwindow* window) {
	// glfwGetKey returns whether this key is currently being pressed
	// In this case the key is Escape
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		// Stops the render loop
		glfwSetWindowShouldClose(window, true);
}

int main() {
	// Initialize GLFW
	glfwInit();

	// Configure GLFW
	// glfwWindowHint(bit Option we want to configure, int to_what)
	// We are saying that we are using the OpenGL version 3.3
	// If the user has any other openGL installed it will fail to run.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// We are using the core-profile option of OpenGL
	// We are using core becaur we want to get access to a smaller
	// Subset of OpenGL features without backwards-compatible features we no longer need.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// Creates a window object which will hold all the windowing data.
	// glfwCreateWindow(int width, int height, string window_name, tbd, tbd);
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	// Because the program is useless without a window, we make sure that the window
	// was created before continuing. If not, we terminate the program.
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

	// Step 2 to make a resizable window
	// We are telling GLFW we want to call this function on every window
	// resize. 
	// It also calls it when the window is first displayed.
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Draw to the window until it closes
	// Render loop
	// glfwWindowShouldClose check at the start of each loop if GLFW
	// has been instructed to close. If so, it returns true.
	while (!glfwWindowShouldClose(window)) {

		// Step 2 to input control
		// Check if the keys were pressed every iteraction (frame) of the loop
		processInput(window);

		// Rendering commands here

		// Clear the screen with a RGB color

		// Specify te color to clear the screen with.
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// Clean the screen color buffer
		glClear(GL_COLOR_BUFFER_BIT);

		// Swap the color buffer which is a large 2D buffer that contains
		// color values for each pixel in GLFW's window. 

		// DOUBLE BUFFER: When an application draw in a single buffer
		// The resulting image may flicker. This is because images are not
		// drawn in a instant but pixel by pixel left-to-right, top-to-bottom.
		// To stop this issue window (not windows) applications apply double buffering
		// The front buffer containst the final image that the user is currently looking at
		// while all the rendering occurs on the back buffer. When the rendering is 
		// over, the buffers switch changing the front image and removing the artifact
		// in the previous front buffer.
		glfwSwapBuffers(window);

		// Check if any events are triggered (Like keyboard input or mouse)
		// update the window state, and calls the corresponding functions.
		glfwPollEvents();
	}

	// Clean/Delete all of GLFW's resources that were allocate.
	glfwTerminate();

	return 0;
}