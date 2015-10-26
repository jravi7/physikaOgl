//Physika X
//Author: Jay Ravi
//Date: Oct 2nd 2015

#pragma once

//C++
#include <iostream>
//3rd Party
#include <GL\glew.h>
#include <SOIL.h>


class ImageIO
{

public:
	static unsigned char* Load(const char* file, int &w, int &h);
	static void Save(const char* file, unsigned char* bytes, int &w, int &h);
	static void captureScreen(int w, int h);
};
