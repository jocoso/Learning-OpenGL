/*
	We create an OpenGL context and an application window
	to draw in. 

	GLFW is a library written in C that gives us the bare 
	necessities for rendering to the screen.
*/

// 3.2 Building GLFW
/*
	Step1: To get GLFW go to the website: www.glfw.org/download.html.

	Step2: Download Source Package

	Step3: Extract and open the content. We will only focus in the library
	and the include folder.

	Step4: Open CMake to compile the library and in "Where is te source Code:" click on Browse Source
	And select the root folder of the glfw file you just downloaded. 
	
	Step5: In "Where to build the binaries:" right under preset do the same as in step 4
	but once you are inside of the root folder, create a "build" directory and select it.
	Compiling the library assures that the resulting library is good for the CPU/OS.

	Step6: Click the Configure button so CMake can read the required settings and the source code.

	Step7: A message will pop up. The first input will ask you to specify the generator for this project.
	Pick your version of visual studio and press "finish". CMake should configured the solution so it 
	compiles to a 64-bit library; now press configure again.

	Step8: Click Generate. You can close CMake after.

	Step9: In the build folder look for a file named GLFW.sln and open it with Visual Studio.

	Step10: In VS click on Build and Build Solution.

	Step11: Inside of your program create two folders named Include and Libs.

	Step12: Add the content of glfwxx/include in the folder Include. The folder
	you will be moving should be named GLFW.

	Step13: Add the content of glfwxx/build/src/Debug in the Lib folder. The files we are moving are
	glfw3.lib, you can ignore glfw3.pdb.

	Step14: Change the dropdown at the top next to Debug to x64.

	Step15: We link the library with our project. We want to use glfw3.lib in the linker setting. To tell it
	where it is. Right click the project name and click Properties.

	Step16: From the properties menu move to VC++ Directories.

	Step17: Select the arrow in Library Directories and press <edit>

	Step18: Click new line which is a yellow folder with a red weird circle.

	Step19: Click the 3 dots next to the empty line we just created and select the Lib folder.

	Step 20: Do the same thing in Step 17-19 but this time with Include Directories in the menu and add the Include folder.

	Step 21: Still in the menu, move to Linker -> Input and click Additional Dependencies. Write glfw3.lib to the field.

*/

// 3.5 GLAD

/*
	Glad simplifies our coding process. As a normal OpenGL may look like...
	
	// define the function’s prototype
	typedef void (*GL_GENBUFFERS) (GLsizei, GLuint*);
	// find the function and assign it to a function pointer
	GL_GENBUFFERS glGenBuffers =
		(GL_GENBUFFERS)wglGetProcAddress("glGenBuffers");
	// function can now be called as normal
	unsigned int buffer;
	glGenBuffers(1, &buffer);

	So Glad makes it less cumbersome.

	To use glad...

	Step1: Go to https://glad.dav1d.de

	Step2: Set language to C/C++

	Step3: Specification: OpenGL

	Step4: API -> gl Version 3.3

	Step5: Profile Core

	Step6: Generate a loader should be selected.

	Step7: Click Generate

	Step8: Donwload and open the zip file.

	Step9: glad and KHR folder will go into the Include directory and glad.c should be
	in the root file.

	Step10: Right-click the project name -> add -> existing item and then add glad.c
*/