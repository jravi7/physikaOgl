#include "Texture.h"


Texture::Texture(GLenum target)
{
	m_texture_target = target; 
}
Texture::~Texture(void){}

void Texture::setWrap(GLint wrap)
{
	m_wrap = wrap;
}

void Texture::setMinFilter(GLfloat min)
{
	m_min_filter = min;
}

void Texture::setMagFilter(GLfloat mag)
{
	m_mag_filter = mag;
}

void Texture::setImagePath(std::string file)
{
	m_file = file;
}

void Texture::init()
{
	if(m_texture_target == GL_TEXTURE_2D)
		init2d();
	if(m_texture_target == GL_TEXTURE_3D)
		init3d();
}

void Texture::init2d()
{
	int w, h; 
	unsigned char *image_data = NULL; 

	image_data = ImageIO::Load(m_file.c_str(), w, h);

	if(image_data == NULL)
	{
		std::cerr<<"Error loading texture file " <<m_file<<std::endl;
	}

	glGenTextures  (1, &m_texture_id);	
	glBindTexture  (m_texture_target, m_texture_id);
	glTexImage2D   (m_texture_target, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	glTexParameterf(m_texture_target, GL_TEXTURE_MIN_FILTER, m_min_filter);
	glTexParameterf(m_texture_target, GL_TEXTURE_MAG_FILTER, m_mag_filter);
	glTexParameteri(m_texture_target, GL_TEXTURE_WRAP_S, m_wrap);
	glTexParameteri(m_texture_target, GL_TEXTURE_WRAP_T, m_wrap);
	glBindTexture  (m_texture_target, 0);	//unbind

	SOIL_free_image_data(image_data);
}

void Texture::init3d()
{

}

void Texture::activate(GLenum texture_unit)
{
	glActiveTexture(texture_unit);
	glBindTexture(m_texture_target, m_texture_id);
}

void Texture::deactivate()
{
	glBindTexture(m_texture_target, 0);
}