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

int main(void) {
	return 0;
}