//#pragma once
#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include <vector>

//-------------------------------------------------------------------------

class Mesh 
{
public:
	static Mesh* generaPoligono(GLdouble rd, GLuint numL);
	static Mesh* generaSierpinski(GLdouble rd, GLuint numP);
	static Mesh* generaTriangleRGB(GLdouble rd);
	static Mesh* generaRectangulo(GLdouble w, GLdouble h);
	static Mesh* generaRectanguloRGB(GLdouble w, GLdouble h);
	static Mesh* generaEstrella3D(GLdouble re, GLuint np, GLdouble h);
	static Mesh* generaContCubo(GLdouble ld);
	static Mesh* generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
	static Mesh* generaEstrellaTexCor(GLdouble re, GLuint np, GLdouble h);
	static Mesh* generaContCuboTexCor(GLdouble nl);
	static Mesh* createRGBAxes(GLdouble l); // creates a new 3D-RGB axes mesh
	
	Mesh() {};
	virtual ~Mesh() {};

	Mesh(const Mesh & m) = delete;  // no copy constructor
	Mesh & operator=(const Mesh & m) = delete;  // no copy assignment
			
	virtual void render() const;
	
	GLuint size() const { return mNumVertices; };   // number of elements
	std::vector<glm::dvec3> const& vertices() const { return vVertices; };
	std::vector<glm::dvec4> const& colors() const { return vColors; };
	std::vector<glm::dvec2> const& texCoords() const { return vTexCoords; };
	std::vector<glm::dvec3> const& normals() const { return vNormals; };

	void setTexCoords(std::vector<glm::dvec2> texCoords) { vTexCoords = texCoords; };

protected:
	
	GLuint mPrimitive = GL_TRIANGLES;   // graphic primitive: GL_POINTS, GL_LINES, GL_TRIANGLES, ...
	GLuint mNumVertices = 0;  // number of elements ( = vVertices.size())
	std::vector<glm::dvec3> vVertices;  // vertex array
	std::vector<glm::dvec4> vColors;    // color array
	std::vector<glm::dvec2> vTexCoords;		// texture coords array
	std::vector<glm::dvec3> vNormals;
	virtual void draw() const;
};
//-------------------------------------------------------------------------
class IndexMesh : public Mesh
{
public:
	IndexMesh() { mPrimitive = GL_TRIANGLES; };
	virtual ~IndexMesh() { delete[] vIndices; };
	virtual void render() const;
	virtual void draw() const;

	GLuint size() const { return nNumIndices; };   // number of indexs

	static IndexMesh* generaAnilloCuadradoIndexado();
	static IndexMesh* generaCuboConTapasIndexado(GLdouble l);
	void buildNormalVectors();

	GLuint* indices() { return vIndices; };
protected:
	GLuint* vIndices = nullptr;
	GLuint nNumIndices = 0;


};

#endif //_H_Scene_H_