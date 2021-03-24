//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Mesh.h"
#include "Texture.h"

//-------------------------------------------------------------------------

class Abs_Entity  // abstract class
{
public:
	Abs_Entity(): mModelMat(1.0), mColor(1) {};  // 4x4 identity matrix
	virtual ~Abs_Entity() {};

	Abs_Entity(const Abs_Entity& e) = delete;  // no copy constructor
	Abs_Entity& operator=(const Abs_Entity& e) = delete;  // no copy assignment

	virtual void render(glm::dmat4 const& modelViewMat) const = 0;  // abstract method
	
	// modeling matrix
	glm::dmat4 const& modelMat() const { return mModelMat; };
	void setModelMat(glm::dmat4 const& aMat) { mModelMat = aMat; };
	void setColor(glm::dvec4 const& color) { mColor = color; };
	void setTexture(Texture* tex) { mTexture = tex; };
	void setTexture2(Texture* tex) { mTexture2 = tex; };
	virtual void update() {};
protected:
	Texture* mTexture = nullptr;
	Texture* mTexture2 = nullptr;
	Mesh* mMesh = nullptr;		// the mesh
	glm::dmat4 mModelMat;		// modeling matrix
	glm::dvec4 mColor;			// mesh color
	// transfers modelViewMat to the GPU
	virtual void upload(glm::dmat4 const& mModelViewMat) const; 
};

//-------------------------------------------------------------------------

class EjesRGB : public Abs_Entity 
{
public:
	explicit EjesRGB(GLdouble l);
	~EjesRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class Poligono : public Abs_Entity
{
public:
	explicit Poligono(GLdouble rd, GLuint numL, glm::dvec4 const& color);
	~Poligono();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------
class Sierpinski : public Abs_Entity
{
public:
	explicit Sierpinski(GLdouble rd, GLuint numP, glm::dvec4 const& color);
	~Sierpinski();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class TrianguloRGB : public Abs_Entity
{
public:
	explicit TrianguloRGB(GLdouble rd);
	~TrianguloRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
private:
	double rotAngle=0, transAngle=0;

};

//-------------------------------------------------------------------------

class RectanguloRGB : public Abs_Entity
{
public:
	explicit RectanguloRGB(GLdouble w, GLdouble h);
	~RectanguloRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	
};

//-------------------------------------------------------------------------


class Estrella3D : public Abs_Entity
{
public:
	explicit Estrella3D(GLdouble re, GLuint np, GLdouble h);
	~Estrella3D();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
private:
	double rotAngleY=0, rotAngleZ=0;
};

//-------------------------------------------------------------------------

class Caja : public Abs_Entity
{
public:
	explicit Caja(GLdouble ld);
	~Caja();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class Suelo : public Abs_Entity
{
public:
	explicit Suelo(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
	~Suelo();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class Image : public Abs_Entity
{
public:
	explicit Image(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
	~Image();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};
#endif //_H_Entities_H_