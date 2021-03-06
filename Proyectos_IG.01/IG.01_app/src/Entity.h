//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Mesh.h"

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
protected:

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
	explicit Poligono(GLuint numL, GLdouble rd, glm::dvec4 const& color);
	~Poligono();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class Circle : public Abs_Entity
{
public:
	explicit Circle(GLuint numL, GLdouble rd);
	~Circle();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class Triangle : public Abs_Entity
{
public:
	explicit Triangle(GLuint numL, GLdouble rd);
	~Triangle();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------
class Sierpinski : public Abs_Entity
{
public:
	explicit Sierpinski(GLuint numL, GLdouble rd, glm::dvec4 const& color);
	~Sierpinski();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};
#endif //_H_Entities_H_