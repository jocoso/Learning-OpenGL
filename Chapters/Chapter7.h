#ifndef CHAPTER_7_H
#define CHAPTER_7_H

#include "Chapter.h"
#include "stb_image.h"
#include "extras/chapter6/chapter6shaderclass.h";


class Chapter7 : public Chapter {
public:
	void run();
	~Chapter7();
private:
	const int HEIGHT = 600;
	const int WIDTH = 800;
};


#endif // Chapter7.h