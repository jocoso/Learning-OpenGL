#include "Chapter7.h"

void Chapter7::run() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow *window = glfwCreateWindow(this->WIDTH, this->HEIGHT, "Chapter7", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	// Compile our shader
	// GLSL has a built-in data-type for texture objects called a sampler that takes as postfix the texture type
	// we want. 1D, 2D, 3D. check shader.fs
	// To sample color we use GLSL's buil-in texture function.
	// It takes as parameters:
	//		The corresponding color value 
	//		The tex coordinates
	Shader theShader("./extras/chapter6/shader.vs", "./extras/chapter6/shader.fs");

	// For GL_CLAMP_TO_BORDER we use glTexParameterfv and add the border
	// ---------------------------------------------------------------------
	// float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	// ---------------------------------------------------------------------

	// Texture coordinates can be any floating point value.
	// Texture Pixel is also known as texel.
	// OpenGL has the options for texture filtering.
	// The most importan options are GL_NEAREST and GL_LINEAR.
	// GL_NEAREST is also know as nearest neighbor or point.
	// 
	// GL_LINEAR is also known as (bi)linear filtering. (bi representation)
	// Linear takes the interpolated value of the texture coordinate's neighboring texels.
	// It approximates a color between the texels.
	// The smaller the distance from the texture coordinate to a texel's center the more that color contributes to the sample color.
	// 
	// GL_NEAREST as a result returns a blocked pattern and GL_LINEAR returns a blurry one
	// GL_LINEAR is more realistic. GL_NEAREST is better for pixel.
	// 
	// Texture filtering can be set for magnifying and minifyinf operations.
	// ---------------------------------------------------------------------
	// glTextParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// glTextParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// ---------------------------------------------------------------------
	
	// Mipmaps
	// Mipmaps is a collection of texture images where each subsequent texture is twice as small compared to the previous one.
	// Meaning, after certain distance threshold from the viewer OpenGL will use a different mipmap to suits the distance.
	// For that we sue glGenerateMipmaps after creating a texture.
	// It is possible to filter between mipmaps layer using NEAREST and LINEAR.
	// To do this we can replace the original filtering with one of the following:
	//		GL_NEAREST_MIPMAP_NEAREST: Takes the nearest mipmap to match the pixel size and uses
	//			the nearest neighbor interpolation for texture sampling.
	//		GL_LINEAR_MIPMAP_NEAREST: Takes the nearest mipmap level and samples that level using
	//			interpolation.
	//		GL_NEAREST_MIPMAP_LINEAR: Linearly interpolates between the two mipmaps that most closely
	//			match the size of a pixel and samples the interpolated level via nearest neigbor
	//			interpolation.
	//		GL_LINEAR_MIPMAP_LINEAR: Linearly interpolates between the two closest mipmaps and samples
	//			the interpolated level via linear interpolation
	// 
	// We use the filtering method the same way as the texture filtering
	// ---------------------------------------------------------------------
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	// Vertices
	// -------------------------
	float vertices[] = {
		// positions // colors // texture coords
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
		-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // top left
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// Texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Textures
	// -----------------------------
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// A texture is a 2D image that add details to flat vertice surfaces.
	// To map a texture we need to tell each vertex of the triangle which part of the 
	// texture it correspons to.
	// Each texture should have avertex coodrinate.
	// Texture coordinates range from 0 to 1 in the x and y axis.
	// Retrieving the texture color using texture coordinates is called sampling
	// Texture coordinates start at (0, 0) for the lower left corner to (1, 1) for the upper right.

	/*
		--------------------------------
		|(0,1)|     |(.5,1)|     |(1,1)|
		|     |     |      |     |     |
		|     |     |      |     |     |
		|     |     |      |     |     |
		|(0,0)|     |      |     |(1,0)|
		--------------------------------
	*/

	// GL_REPEAT: Default behaviour for textures. Repeats the image.
	// GL_MIRRORED_REPEAT: Same as the prior but mirrors the image with each repeat.
	// GL_CLAMP_TO_EDGE: Clamps the coordinates between 0 and 1. Higher coordinates become.
	// clamped to the edge, resulting in a stretched edge pattern.
	// GL_CLAMP_TO_BORDER: Coordinates outside the range are now given a user-specified border color.

	//              texture_target   texture_axis    texture_wrapping_mode
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);  // Mirror repeat in X
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);  // Mirror repeat in Y
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("./extras/chapter6/brunoFanart.png", &width, &height, &nrChannels, 0);
	if (data) {
		// -----------------------------------------------------------------------------------
		// texture_target: Generates a texture on the currentlly bound texture 1D 2D or 3D
		// mipmap_level: 0 base level. We can generate manually.
		// format: Tell OpenGL what kind of format we want to store the texture.
		// width + height: of the image.
		// ??: Legacy item. Set always to 0.
		// datatype_source_image: determine the datatype of the source.
		// image: the image data.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		// -----------------------------------------------------------------------------------
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "FAILED TO LOAD TEXTURE" << std::endl;
	}
	stbi_image_free(data);

	theShader.use();
	theShader.setInt("ourTexture", 1);

	glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture);
		theShader.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

Chapter7::~Chapter7() {
	glfwTerminate();
}
