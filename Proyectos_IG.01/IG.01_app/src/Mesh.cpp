#include "Mesh.h"
#include "CheckML.h"
#include <fstream>
using namespace std;
using namespace glm;

//-------------------------------------------------------------------------

void Mesh::draw() const 
{
  glDrawArrays(mPrimitive, 0, size());   // primitive graphic, first index and number of elements to be rendered
}
//-------------------------------------------------------------------------

void Mesh::render() const 
{
  if (vVertices.size() > 0) {  // transfer data
    // transfer the coordinates of the vertices
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vVertices.data());  // number of coordinates per vertex, type of each coordinate, stride, pointer 
    if (vColors.size() > 0) { // transfer colors
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(4, GL_DOUBLE, 0, vColors.data());  // components number (rgba=4), type of each component, stride, pointer  
    }

	draw();

    glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
  }
}
//-------------------------------------------------------------------------

Mesh* Mesh::generaCircle(GLuint numL, GLdouble rd)
{
    // variables iniciales:
    Mesh* mesh = new Mesh();
    mesh->mPrimitive = GL_LINE_LOOP;
    mesh->mNumVertices = numL;
    mesh->vVertices.reserve(mesh->mNumVertices);
    // construccion del circulo:
    double ang = 0.0;
    for (uint i = 0; i < mesh->mNumVertices; ++i) 
    {
        double y = 0 + rd * cos(radians(ang));
        double x = 0 + rd * sin(radians(ang));
        ang = ang + (360 / mesh->mNumVertices);
        mesh->vVertices.emplace_back(x, y, 0.0);
        mesh->vColors.emplace_back(1.0, 0.0, 1.0, 0.0);
    }
    return mesh;
}
//-------------------------------------------------------------------------

Mesh* Mesh::generaTriangle(GLuint numL, GLdouble rd)
{
    // variables iniciales:
    Mesh* mesh = new Mesh();
    mesh->mPrimitive = GL_LINE_LOOP;
    mesh->mNumVertices = numL;
    mesh->vVertices.reserve(mesh->mNumVertices);
    // construccion del triangulo:
    double ang = 0.0;
    for (uint i = 0; i < mesh->mNumVertices; ++i)
    {
        double y = 0 + rd * cos(radians(ang));
        double x = 0 + rd * sin(radians(ang));
        ang = ang + (360 / mesh->mNumVertices);
        mesh->vVertices.emplace_back(x, y, 0.0);
        mesh->vColors.emplace_back(1.0, 1.0, 0.0, 0.0);
    }
    return mesh;
}

Mesh* Mesh::generaTriangleRGB(GLdouble rd)
{
	// variables iniciales:
	Mesh* mesh = generaTriangle(3, rd);
	mesh->mPrimitive = GL_TRIANGLES;


	return mesh;
}

Mesh* Mesh::generaSierpinski(GLdouble rd, GLuint numP) {
	Mesh* triangulo = generaTriangle(3, rd);

	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_POINTS;

	mesh->mNumVertices = numP;
	mesh->vVertices.reserve(mesh->mNumVertices);

	dvec3 p = triangulo->vertices()[rand() % 3];
	dvec3 p1;

	dvec3 vertices[3] = { triangulo->vertices()[0], triangulo->vertices()[1], triangulo->vertices()[2] };

	// An arbitrary initial point inside the triangle
	mesh->vVertices.emplace_back(p);
	// compute and store N-1 new points
	for (uint i = 0; i < numP; i++) {
		int j = rand() % 3; // pick a vertex at random
		// Compute the point halfway between the selected vertex
		// and the previous point
		p1 = (p + vertices[j]) / 2.0;
		mesh->vVertices.emplace_back(p1);
		mesh->vColors.emplace_back(1.0, 0.0, 1.0, 0.0);
		p = p1;
	}

	delete triangulo; triangulo = nullptr;
	return mesh;
}
//-------------------------------------------------------------------------

Mesh * Mesh::createRGBAxes(GLdouble l)
{
  Mesh* mesh = new Mesh();

  mesh->mPrimitive = GL_LINES;

  mesh->mNumVertices = 6;
  mesh->vVertices.reserve(mesh->mNumVertices);

  // X axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(l, 0.0, 0.0);
  // Y axis vertices
  mesh->vVertices.emplace_back(0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, l, 0.0);
  // Z axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, 0.0, l);

  mesh->vColors.reserve(mesh->mNumVertices);
  // X axis color: red  (Alpha = 1 : fully opaque)
  mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
  mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
  // Y axis color: green
  mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
  mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
  // Z axis color: blue
  mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
  mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
 
  return mesh;
}
//-------------------------------------------------------------------------

