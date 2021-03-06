#include "Entity.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Abs_Entity::upload(dmat4 const& modelViewMat) const 
{ 
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat));  // transfers modelView matrix to the GPU
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l): Abs_Entity()
{
  mMesh = Mesh::createRGBAxes(l);
}
//-------------------------------------------------------------------------

EjesRGB::~EjesRGB() 
{ 
	delete mMesh; mMesh = nullptr; 
};
//-------------------------------------------------------------------------

void EjesRGB::render(dmat4 const& modelViewMat) const 
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
	}
}

//-------------------------------------------------------------------------

//Circle::Circle(GLuint numL, GLdouble rd)
//{
//	mMesh = Mesh::generaCircle(numL, rd);
//}
//
//Circle::~Circle()
//{
//	delete mMesh; mMesh = nullptr;
//}
//
//void Circle::render(glm::dmat4 const& modelViewMat) const
//{
//	if (mMesh != nullptr) {
//		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
//		upload(aMat);
//		glLineWidth(2);
//		mMesh->render();
//		glLineWidth(1);
//	}
//}

//-------------------------------------------------------------------------

//Triangle::Triangle(GLuint numL, GLdouble rd)
//{
//	mMesh = Mesh::generaTriangle(numL, rd);
//}
//
//Triangle::~Triangle()
//{
//	delete mMesh; mMesh = nullptr;
//}
//
//void Triangle::render(glm::dmat4 const& modelViewMat) const
//{
//	if (mMesh != nullptr) {
//		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
//		upload(aMat);
//		glLineWidth(2);
//		mMesh->render();
//		glLineWidth(1);
//	}
//}

Sierpinski::Sierpinski(GLuint numL, GLdouble rd, glm::dvec4 const& color)
{
	mMesh = Mesh::generaSierpinski(numL, rd, color);
}

Sierpinski::~Sierpinski()
{
	delete mMesh; mMesh = nullptr;
}

void Sierpinski::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor4dv(value_ptr(mColor));
		glPointSize(2);
		mMesh->render();
		glColor4d( 1.0, 1.0, 1.0, 1.0 );
		glPointSize(1);
	}
}

Poligono::Poligono(GLuint numL, GLdouble rd, glm::dvec4 const& color)
{
	mMesh = Mesh::generaPoligono(numL, rd, color);
}

Poligono::~Poligono()
{
	delete mMesh; mMesh = nullptr;
}

void Poligono::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor3dv(value_ptr(mColor));
		glLineWidth(2);
		mMesh->render();
		glColor3d(1.0, 1.0, 1.0);
		glLineWidth(1);
	}
}

TrianguloRGB::TrianguloRGB(GLdouble rd)
{
	mMesh = Mesh::generaTriangleRGB(rd);
}

TrianguloRGB::~TrianguloRGB()
{
	delete mMesh; mMesh = nullptr;
}

void TrianguloRGB::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		
		glColor3d(0.0, 1.0, 1.0); // value_ptr(mColor));
		glLineWidth(2);
		mMesh->render();
		glColor3d(1.0, 1.0, 1.0);
		glLineWidth(1);
	}
}
