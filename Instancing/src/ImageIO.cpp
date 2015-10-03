#include "ImageIO.h"

//source: http://programmingexamples.net/wiki/OpenGL/Screenshot
//TODO: implement above method. SOIL causes heap corruption at higher resolutions. 
void ImageIO::captureScreen(int w, int h)
{
	//unsigned char* buffer = (unsigned char*)malloc(w*h*3*sizeof(unsigned char));

	//glReadBuffer(GL_FRONT);
	//glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)buffer);

	SOIL_save_screenshot("test.bmp",SOIL_SAVE_TYPE_BMP, 0, 0, w,h);
}