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

	if (vTexCoords.size()>0){
	  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glTexCoordPointer(2, GL_DOUBLE, 0, vTexCoords.data());  // components number (rgba=2), type of each component, stride, pointer 
	}
	draw();

    glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  }
}

//-------------------------------------------------------------------------

Mesh* Mesh::generaPoligono(GLdouble rd, GLuint numL)
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
        ang = ang + (360.0 / mesh->mNumVertices);
        mesh->vVertices.emplace_back(x, y, 0.0);
    }
    return mesh;
}

//-------------------------------------------------------------------------

Mesh* Mesh::generaTriangleRGB(GLdouble rd)
{
	Mesh* mesh = generaPoligono(rd, 3);
	mesh->mPrimitive = GL_TRIANGLES;
	
	mesh->vColors.clear();
	mesh->vColors.reserve(mesh->mNumVertices); 
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	return mesh;
}

//-------------------------------------------------------------------------

Mesh* Mesh::generaRectangulo(GLdouble w, GLdouble h)
{
	Mesh* mesh = new Mesh();
	GLuint numP = 4; //
	mesh->mPrimitive = GL_TRIANGLE_STRIP;
	mesh->mNumVertices = numP;
	mesh->vVertices.reserve(mesh->mNumVertices);

	dvec3 p = { w / -2, h / 2, 0.0 };

	mesh->vVertices.emplace_back(p); // V0
	p.y = p.y - h;
	mesh->vVertices.emplace_back(p); // V1
	p.y = p.y + h;
	p.x = p.x + w;
	mesh->vVertices.emplace_back(p); // V2
	p.y = p.y - h;
	mesh->vVertices.emplace_back(p); // V3
	return mesh;
}

//-------------------------------------------------------------------------

Mesh* Mesh::generaRectanguloRGB(GLdouble w, GLdouble h)
{
	Mesh* mesh = generaRectangulo(w, h);
	dvec3 p = { w / -2, h / 2, 0.0 };

	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0); // V0
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0); // V1
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0); // V2
	mesh->vColors.emplace_back(0.0, 1.0, 1.0, 1.0); // V3
	return mesh;
}

//-------------------------------------------------------------------------

Mesh* Mesh::generaSierpinski(GLdouble rd, GLuint numP) {
	Mesh* triangulo = generaPoligono(rd, 3);

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

Mesh* Mesh::generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
{
	Mesh* m = generaRectangulo(w, h);
	m->vTexCoords.reserve(m->mNumVertices);
	m->vTexCoords.emplace_back(0, h * rh);
	m->vTexCoords.emplace_back(0, 0);
	m->vTexCoords.emplace_back(w * rw, h * rh);
	m->vTexCoords.emplace_back(w * rw, 0);
	return m;
	/*Mesh* m = new Mesh();
	int numV = 4 * rw * rh;
	m->vTexCoords.reserve(numV);
	for (int i = 1; i <= rw; ++i) {
		for (int j = 1; j <= rh; ++j) {
			m->vTexCoords.emplace_back(0, h * j);
			m->vTexCoords.emplace_back(0, 0);
			m->vTexCoords.emplace_back(w * i, h * j);
			m->vTexCoords.emplace_back(w * i, 0);
		}
	}
	return m;*/
}

Mesh* Mesh:: generaEstrella3D(GLdouble re, GLuint np, GLdouble h) {
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_FAN;
	mesh->mNumVertices = 2 * np + 2;
	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0); //V0
	// construccion del circulo:
	double ang = 0.0;
	double incremento = 360.0 / (np * 2.0);
	for (uint i = 0; i < np; ++i)
	{
		// vertice interior
		double x = 0 + re / 2 * cos(radians(ang));
		double y = 0 + re / 2 * sin(radians(ang));
		mesh->vVertices.emplace_back(x, y, h);
		ang = ang + incremento;
		// vertice exterior
		x = 0 + re * cos(radians(ang));
		y = 0 + re * sin(radians(ang));
		mesh->vVertices.emplace_back(x, y, h);
		ang = ang + incremento;
	}
	ang = 0.0;
	// vertice interior
	double x = 0 + re/2 * cos(radians(ang));
	double y = 0 + re/2 * sin(radians(ang));
	mesh->vVertices.emplace_back(x, y, h);

	return mesh;
}

Mesh* Mesh::generaContCubo(GLdouble ld) {
	Mesh* mesh = new Mesh();
	GLuint numP = 8 + 2; //
	mesh->mPrimitive = GL_TRIANGLE_STRIP;
	mesh->mNumVertices = numP;
	mesh->vVertices.reserve(mesh->mNumVertices);

	dvec3 p = { 0.0, ld, ld };

	mesh->vVertices.emplace_back(p); // V0
	p.y = p.y - ld;
	mesh->vVertices.emplace_back(p); // V1
	p.y = p.y + ld;
	p.x = p.x + ld;
	mesh->vVertices.emplace_back(p); // V2
	p.y = p.y - ld;
	mesh->vVertices.emplace_back(p); // V3
	p.z = p.z - ld;
	p.y = p.y + ld;
	mesh->vVertices.emplace_back(p); // V4
	p.y = p.y - ld;
	mesh->vVertices.emplace_back(p); // V5
	p.y = p.y + ld;
	p.x = p.x - ld;
	mesh->vVertices.emplace_back(p); // V6
	p.y = p.y - ld;
	mesh->vVertices.emplace_back(p); // V7
	p.y = p.y + ld;
	p.z = p.z + ld;
	mesh->vVertices.emplace_back(p); // V0
	p.y = p.y - ld;
	mesh->vVertices.emplace_back(p); // V1
	return mesh;
}

//-------------------------------------------------------------------------

