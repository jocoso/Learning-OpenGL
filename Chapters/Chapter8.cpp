#include "Chapter8.h"

void Chapter8::run() {
	//
	// A better way to transform an object is by using a matrix object
	// 
	// Vectors are directions and nothing more. 
	// A vector has a direction and a magnitude.
	// It is like directions in treasure maps: Go South 3 steps ... yadda yadd
	// South is the direction and 3 steps is the magnitude.
	// If a vector has 2 dimensions it represents a direction o a plane (2D graphs)
	// When it has 3 it can represent any direction in the real world.
	// 
	// Using vectors we could describe directions and positions in 2D and 3D space.
	// 
	// SCALAR
	// Scalar is a single digit. When adding/subtracting/multiplying or dividing a vector
	//		with a scalar we simply add/subtract/multiply or divide each element of the vector
	//		by said scalar.
	// Something like (1, 2, 3) + x -> (1, 2, 3) + (x, x, x) = (1+x, 2+x, 3+x)
	// Works the same way for the others.
	// 
	// VECTOR NEGATION
	// Negating a vector result in the vector going to the opposite direction.
	// To negate a vector we add a minus-sign to each component. 
	// It can also be represented by a multiplication.
	// (1, 2, 3) * -1 -> (1, 2, 3) * (-1, -1, -1) -> (1 * -1, 2 * -1, 3 * -1) = (-1, -2, -3)
	// 
	// ADITION AND SUBTRACTION
	// Addition of two vectos is defined as component-wise addition.
	// v = (1, 2, 3), k = (4, 5, 6) => v + k = (1 + 4, 2 + 5, 3 + 6) = <5, 7, 9>
	// Visually, it will form a line as long as the two vectors combined (Not changing the alignment of each vector)
	// 
	// Same is true with subtraction.
	// v = <1, 2, 3>, k = <4, 5, 6> => v - k = <1 - 4, 2 - 5, 3 - 6> = <-3, -3, -3>
	// Visually, it will form a line between the end points of each vector.
	// 
	// LENGHT
	// To retrieve the length/magnitude of a vector we use the Pythgoras Theorem.
	// ||v|| = sqrt(pow(x, 2) + pow(y, 2))
	// ||v|| is the length of the vector
	// for 3d we just add pow(z, 2)
	// ||v|| = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	// There is also a special vector called the unit vector.
	// An unit vector length is exactly 1. 
	// We calculate it by dividing each of the vector's components by its length:
	// n = v/||v||
	//
	std::cout << "CHAPTER 8 WORKS" << std::endl;
}