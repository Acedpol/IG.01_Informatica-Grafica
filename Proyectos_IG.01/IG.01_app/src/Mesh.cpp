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
	if (vNormals.size() > 0) {
		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_DOUBLE, 0, vNormals.data());
	}
	
	draw();
	glDisableClientState(GL_NORMAL_ARRAY);
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

// -------------------------------------------------------

void IndexMesh::render() const
{
	// Activación de los vertex arrays
	if (vVertices.size() > 0) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_DOUBLE, 0, vVertices.data());  // number of coordinates per vertex, type of each coordinate, stride, pointer 

		if (vColors.size() > 0) { // transfer colors
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(4, GL_DOUBLE, 0, vColors.data());  // components number (rgba=4), type of each component, stride, pointer  
		}

		if (vNormals.size() > 0) {
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_DOUBLE, 0, vNormals.data());
		}
		if (vIndices != nullptr) {
			glEnableClientState(GL_INDEX_ARRAY);
			glIndexPointer(GL_UNSIGNED_INT, 0, vIndices);
		}
		if (vTexCoords.size() > 0) { // transfer texture coors
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer(2, GL_DOUBLE, 0, vTexCoords.data());
        }

		draw();

		// Desactivación de los vertex arrays
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_INDEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
	}
}

void IndexMesh::draw() const {
	glDrawElements(mPrimitive, nNumIndices,
		GL_UNSIGNED_INT, vIndices);
}

IndexMesh* IndexMesh::generaAnilloCuadradoIndexado()
{
	IndexMesh* m = new IndexMesh();
	m->mPrimitive = GL_TRIANGLE_STRIP;
	m->nNumIndices = 10;
	const uint f = 8;
	m->mNumVertices = f;

	static float vertices[f][3] = {
		{30.0, 30.0, 0.0}, {10.0, 10.0, 0.0}, {70.0, 30.0, 0.0}, {90.0, 10.0, 0.0},
		{70.0, 70.0, 0.0}, {90.0, 90.0, 0.0}, {30.0, 70.0, 0.0}, {10.0, 90.0, 0.0}
	};
	static float colors[f][3] = {
		{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0},
		{1.0, 1.0, 0.0}, {1.0, 0.0, 1.0}, {0.0, 1.0, 1.0}, {1.0, 0.0, 0.0}
	};

	m->vVertices.reserve(m->mNumVertices);
	for (int i = 0; i < f; ++i) {
		m->vVertices.emplace_back(glm::dvec3{ vertices[i][0], vertices[i][1], vertices[i][2] });
	}

	m->vColors.reserve(m->mNumVertices);
	for (int i = 0; i < f; ++i) {
		m->vColors.emplace_back(glm::dvec4{ colors[i][0], colors[i][1], colors[i][2], 1.0 });
	}
	
	m->vIndices = new GLuint[m->nNumIndices];
	for (int i = 0; i < m->nNumIndices - 2; ++i) {
		m->vIndices[i] = i;
	}
	m->vIndices[8] = 0;
	m->vIndices[9] = 1;

	m->vNormals.reserve(m->mNumVertices);
	for (int i = 0; i < m->mNumVertices; ++i) {
		m->vNormals.emplace_back(glm::dvec3{ 0, 0, 1 });
	}

	return m;
}

IndexMesh* IndexMesh::generaCuboConTapasIndexado(GLdouble l)
{
	IndexMesh* m = new IndexMesh();
	m->mPrimitive = GL_TRIANGLES;
	m->nNumIndices = 36; // 3 vertices x 2 por cuadrado x 6 caras del cubo = indices totales usados por los triangulos
	const uint f = 8; // 4 vertices x 2 caras = uniendo vertices de ambas caras, se forma el cubo
	m->mNumVertices = f;

	GLdouble k = l / 2;
	static float vertices[f][3] = {
		{k, k, -k}, {k, k, k}, {k, -k, k}, {k, -k, -k},
		{-k, k, -k}, {-k, k, k}, {-k, -k, k}, {-k, -k, -k}
	};

	m->vVertices.reserve(m->mNumVertices);
	for (int i = 0; i < m->mNumVertices; ++i) {
		m->vVertices.emplace_back(glm::dvec3{ vertices[i][0], vertices[i][1], vertices[i][2] });
	}

	m->vColors.reserve(m->mNumVertices);
	for (int i = 0; i < m->mNumVertices; ++i) {
		m->vColors.emplace_back(glm::dvec4{ 0.0, 1.0, 0.0, 1.0 });
	}

	m->vIndices = new GLuint[m->nNumIndices];
	unsigned int stripIndices[] = { 
		0,1,2,
		2,3,0,
		/*4,7,3,
		3,0,4,*/
		0,4,7,
		7,3,0,
		5,6,7,
		7,4,5,
		1,5,6,
		6,2,1,
		4,5,1,
		1,0,4,
		/*0,4,5,
		5,1,0,*/
		7,6,2,
		2,3,7		
		/*3,7,6,
		6,2,3*/
		/*0, 1, 2,
		2, 1, 3,
		2, 3, 4,
		4, 3, 5,
		4, 5, 6,
		6, 5, 7,
		6, 7, 0,
		0, 7, 1,
		4, 6, 2,
		2, 6, 0,
		1, 7, 3,
		3, 7, 5*/
		/*1, 0, 3, 
		3, 2, 1, 
		1, 7, 4, 
		4, 2, 1, 
		1, 7, 6, 
		6, 0, 1, 
		0, 6, 5, 
		5, 3, 0, 
		7, 6, 5, 
		5, 4, 7, 
		4, 5, 3, 
		3, 2, 4*/
	};

	for (int i = 0; i < m->nNumIndices; ++i) {
		m->vIndices[i] = stripIndices[i];
	}

	//m->buildNormalVectors();
	m->vNormals.reserve(f);
	for (int i = 0; i < f; ++i) {
		m->vNormals.emplace_back(glm::normalize(glm::dvec3{ vertices[i][0], vertices[i][1], vertices[i][2] }));
	}

	return m;
}

void IndexMesh::buildNormalVectors() 
{
	vNormals.reserve(mNumVertices);
	for (int i = 0; i < mNumVertices; i++) 
		vNormals.emplace_back(0.0, 0.0, 0.0);

	for (int i = 0; i < nNumIndices; i += 3)
	{
		dvec3 a = vVertices[vIndices[i]];
		dvec3 b = vVertices[vIndices[i + 1]];
		dvec3 c = vVertices[vIndices[i + 2]];

		dvec3 n = cross((b - a), (c - a));

		vNormals[vIndices[i]] = +n;
		vNormals[vIndices[i + 1]] = +n;
		vNormals[vIndices[i + 2]] = +n;
		/*for (int j = i; j < i + 3; j++) 
			vNormals[vIndices[j]] += n;*/
   }

	for (int i = 0; i < mNumVertices; i++)
		vNormals[i] = glm::normalize(vNormals[i]);

	/* Como lo teniamos antes:
	uint f = vVertices.size();
	vNormals.reserve(f);
	for (int i = 0; i < f; ++i) {
		vNormals.emplace_back(glm::normalize(glm::dvec3{ vVertices[i] }));
	}
	*/
}

//-------------------------------------------------------------------------

MbR* MbR::generaIndexMeshByRevolution(int mm, int nn, glm::dvec3* perfil) {
	MbR* mesh = new MbR(mm, nn, perfil);
	mesh->mPrimitive = GL_TRIANGLES;
	mesh->mNumVertices = nn * mm;
	dvec3* vertices = new dvec3[mesh->mNumVertices];

	for (int i = 0; i < nn; i++) {
		GLdouble theta = i * 360 / nn;
		GLdouble c = cos(radians(theta));
		GLdouble s = sin(radians(theta));

		for (int j = 0; j < mm; j++) {
			int indice = i * mm + j;
			GLdouble x = c * perfil[j].x + s * perfil[j].z;
			GLdouble z = -s * perfil[j].x + c * perfil[j].z;
			vertices[indice] = dvec3(x, perfil[j].y, z);
		}
	}

	mesh->vVertices.reserve(mesh->mNumVertices);
	for (int i = 0; i < mesh->mNumVertices; i++) {
		mesh->vVertices.emplace_back(vertices[i]);
	}

	mesh->nNumIndices = nn * mm * 6 - (6 * nn);
	mesh->vIndices = new GLuint[mesh->nNumIndices];
	int indiceMayor = 0;
	for (int i = 0; i < nn; i++) {
		for (int j = 0; j < mm - 1; j++) {
			int indice = i * mm + j;

			//primer triangulo
			mesh->vIndices[indiceMayor] = indice;
			indiceMayor++;
			mesh->vIndices[indiceMayor] = (indice + mm) % (nn * mm);
			indiceMayor++;
			mesh->vIndices[indiceMayor] = (indice + mm + 1) % (nn * mm);
			indiceMayor++;
			//Segundo triangulo
			mesh->vIndices[indiceMayor] = (indice + mm + 1) % (nn * mm);
			indiceMayor++;
			mesh->vIndices[indiceMayor] = indice + 1;
			indiceMayor++;
			mesh->vIndices[indiceMayor] = indice;
			indiceMayor++;
		}
	}

	mesh->buildNormalVectors();
	return mesh;
}

IndexMesh* IndexMesh::generaGrid(GLdouble lado, GLuint numDiv) 
{ 
		// Grid cuadrado de lado*lado, centrado en el plano Y=0, 
		// dividido en numDiv*numDiv celdas (cada celda son 2 triángulos)
		IndexMesh* m = new IndexMesh();

		// Generación de vértices
		GLdouble incrXZ = lado / numDiv; // = 10 -> incremento para la coordenada x, y la c. z
		GLuint nFC = numDiv + 1; // = 5 -> número de vértices por filas y columnas
		m->mNumVertices = nFC * nFC; 
		m->vVertices.reserve(m->mNumVertices);

		float z = -lado / 2;
		float x = -lado / 2;
		// Para cada fila f y Para cada columna c
		for (float f = 0.0f; f < nFC; f++) {
			for (float c = 0.0f; c < nFC; c++) {
				//m->vertices[f * nFC + c] = dvec3(x + c * incrXZ, 0, z + f * incrXZ);
				m->vVertices.emplace_back(x + c * incrXZ, 0, z + f * incrXZ);
			}
		}

		// Generación de índices
		m->nNumIndices = numDiv * numDiv * 6; 
		m->vIndices = new GLuint[m->nNumIndices];

		int i = 0; // array de índices
		// Para cada fila h y Para cada columna k
		for (float f = 0.0f; f < numDiv; f++) {
			for (float c = 0.0f; c < numDiv; c++) {
				GLuint iv = f * nFC + c;

				m->vIndices[i++] = iv;
				m->vIndices[i++] = iv + nFC;
				m->vIndices[i++] = iv + 1;

				m->vIndices[i++] = iv + 1;
				m->vIndices[i++] = iv + nFC;
				m->vIndices[i++] = iv + nFC + 1;
			}
		}
		return m; 
}

IndexMesh* IndexMesh::generaGridTex(GLdouble lado, GLuint nDiv) 
{ 
	IndexMesh* m = IndexMesh::generaGrid(lado, nDiv);

    GLuint numFC = nDiv + 1;

    m->vTexCoords.reserve(m->mNumVertices);

    int s = 0;	// coord horizontal
    int t = 1;	// coord vertical

    float incremento =  1.0f / nDiv;
    for (int f = 0; f < numFC; f++) {
        for (int c = 0; c < numFC; c++) {
			//m->texCoords[f * nFC + c]
            m->vTexCoords.emplace_back(s + incremento * c, t - incremento * f);
        }
    }

    return m;
}


