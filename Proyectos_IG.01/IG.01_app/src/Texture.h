//#pragma once
#ifndef _H_Texture_H_
#define _H_Texture_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include "Pixmap32RGBA.h"
#include <string>

//-------------------------------------------------------------------------

class Texture // utiliza la clase PixMap32RGBA para el método load
{
public:
  Texture(){};
  ~Texture() { if (mId != 0) glDeleteTextures(1, &mId); };

  Texture(const Texture & tex) = delete;  // no copy constructor
  Texture & operator=(const Texture & tex) = delete;  // no copy assignment

  void load(const std::string & BMP_Name, GLubyte alpha = 255); // load from file and upload to GPU
  void loadColorBuffer(const GLubyte width, const GLubyte height, const GLenum buffer);
  void save(const std::string& BMP_Name);
  
  void bind(GLuint mixMode); // mixMode: GL_REPLACE / MODULATE / ADD
  void unbind() { glBindTexture(GL_TEXTURE_2D, 0); };

  GLuint width() const { return mWidth; };
  GLuint height() const { return mHeight; };
  
  void setWrap(GLuint wp);  // GL_REPEAT, GL_CLAMP 

protected:

  void init();
  
  GLuint mWidth = 0;	// dimensiones de la imagen
  GLuint mHeight = 0;	
  GLuint mId = 0;		// identificador interno (GPU) de la textura
						// 0 significa NULL, no es un identificador válido
  
};

//-------------------------------------------------------------------------

#endif //_H_Texture_H_

