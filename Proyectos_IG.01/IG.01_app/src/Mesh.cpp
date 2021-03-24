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
	if (vTexCoords.size() > 0) {
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_DOUBLE, 0, vTexCoords.data());  // components number (rgba=2), type of each component, stride, pointer 
	}
	
	draw();
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

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
	mesh->mNumVertices = 4;
	mesh->vVertices.reserve(mesh->mNumVertices);

	dvec3 p = { -w / 2, h / 2, 0.0 };

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
	m->vTexCoords.emplace_back(0, rh);
	m->vTexCoords.emplace_back(0, 0);
	m->vTexCoords.emplace_back(rw, rh);
	m->vTexCoords.emplace_back(rw, 0);
	return m;
}

Mesh* Mesh::generaEstrellaTexCor(GLdouble re, GLuint np, GLdouble h)
{
	Mesh* m = generaEstrella3D(re, np, h);
	m->vTexCoords.reserve(m->mNumVertices);
	// primer vertice (vertice central)
	double x = 0.5;
	double y = 0.5;
	m->vTexCoords.emplace_back(x, y);
	// recorrido circular de vertices:
	double ang = 0.0;
	double incremento = 45.0;//360.0 / (np * 2.0);
	double hipotenusa = sqrt(pow(0.5, 2) + pow(0.5, 2));
	for (uint i = 0; i < np; ++i)
	{
		// vertice interior
		x = 0.5 + 0.5 * cos(radians(ang));
		y = 0.5 + 0.5 * sin(radians(ang));
		x = round(x * 10) / 10;
		y = round(y * 10) / 10;
		m->vTexCoords.emplace_back(x, y);
		ang = ang + incremento;
		// vertice exterior
		x = round(0.5 + hipotenusa * cos(radians(ang)));
		y = round(0.5 + hipotenusa * sin(radians(ang)));
		m->vTexCoords.emplace_back(x, y);
		ang = ang + incremento;
	}
	// vertice interior
	x = 0.5 + 0.5 * cos(radians(ang));
	y = 0.5 + 0.5 * sin(radians(ang));
	x = round(x * 10) / 10;
	y = round(y * 10) / 10;
	m->vTexCoords.emplace_back(x, y);
	return m;
}

Mesh* Mesh::generaContCuboTexCor(GLdouble ld)
{
	Mesh* mesh = generaContCubo(ld);

	mesh->vTexCoords.reserve(mesh->mNumVertices);

	for (int i = 0; i < mesh->mNumVertices; i++) {
		mesh->vTexCoords.emplace_back(GLdouble(i / 2), i % 2 == 0 ? 1.0 : 0.0);
	}

	return mesh;
}

Mesh* Mesh::generaEstrella3D(GLdouble re, GLuint np, GLdouble h) 
{
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

	dvec3 p = { ld / -2, ld, ld / 2 };

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

