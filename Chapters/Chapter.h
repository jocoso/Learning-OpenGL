#ifndef CHAPTER_H
#define CHAPTER_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Chapter {
public:
	virtual void run() = 0;
};

#endif CHAPTER_H