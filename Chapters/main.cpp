#include "Chapter.h"
#include "Chapter7.h"
#include "Chapter8.h"

int main() {
	unsigned int current_chapter = 1;
	Chapter7 r_ch7 = Chapter7();
	Chapter8 r_ch8 = Chapter8();
	Chapter* chapters[] = { &r_ch7, &r_ch8 };

	chapters[current_chapter]->run();
	return 0;
}