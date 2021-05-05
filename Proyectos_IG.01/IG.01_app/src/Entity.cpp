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

Sierpinski::Sierpinski(GLdouble rd, GLuint numP, glm::dvec4 const& color)
{
	mColor = color;
	mMesh = Mesh::generaSierpinski(rd, numP);
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

//-------------------------------------------------------------------------

Poligono::Poligono(GLdouble rd, GLuint numL, glm::dvec4 const& color)
{
	mColor = color;
	mMesh = Mesh::generaPoligono(rd, numL);
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

//-------------------------------------------------------------------------

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
		
		glLineWidth(2);
		/*glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);*/
		glPolygonMode(GL_BACK, GL_FILL);
		glPolygonMode(GL_FRONT, GL_LINE);
		mMesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//glDisable(GL_CULL_FACE);
		glLineWidth(1);
	}
}

void TrianguloRGB::update()
{
	if (mMesh != nullptr) {
		rotAngle = rotAngle + 25.0;
		++transAngle;
		mModelMat = rotate(dmat4(1), radians(transAngle), dvec3(0, 0, 1));
		mModelMat = translate(mModelMat, dvec3(200, 0, 0));
		mModelMat = rotate(mModelMat, (rotAngle), dvec3(0, 0, 1));
	}
}

//-------------------------------------------------------------------------

RectanguloRGB::RectanguloRGB(GLdouble w, GLdouble h)
{
	mMesh = Mesh::generaRectanguloRGB(w, h);
}

RectanguloRGB::~RectanguloRGB()
{
	delete mMesh; mMesh = nullptr;
}

void RectanguloRGB::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {

		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		glLineWidth(2);
		/*glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);*/
		glPolygonMode(GL_BACK, GL_LINE);
		glPolygonMode(GL_FRONT, GL_FILL);
		mMesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//glDisable(GL_CULL_FACE);
		glLineWidth(1);
	}
}
	//-------------------------------------------------------------------------

Estrella3D::Estrella3D(GLdouble re, GLuint np, GLdouble h)
{
	mMesh = Mesh::generaEstrellaTexCor(re, np, h);
	mModelMat = translate(dmat4(1), dvec3(0, 200.0, 0));
}

Estrella3D::~Estrella3D()
{
	delete mMesh; mMesh = nullptr;
}

void Estrella3D::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication

		upload(aMat);
		mTexture->bind(GL_REPLACE);

		mMesh->render();

		aMat = rotate(aMat, radians(180.0), dvec3(1, 0, 0));
		upload(aMat);

		mMesh->render();
		
		mTexture->unbind();
	}
}
void Estrella3D::update()
{
	if (mMesh != nullptr) {
		rotAngleZ = ++rotAngleZ;
		mModelMat = translate(dmat4(1), dvec3(0, 200.0, 0));
		mModelMat = rotate(mModelMat, radians(rotAngleZ), dvec3(0, 1, 1));
	}
}
//-------------------------------------------------------------------------

Caja::Caja(GLdouble ld)
{
	mMesh = Mesh::generaContCuboTexCor(ld);
}

Caja::~Caja()
{
	delete mMesh; mMesh = nullptr;
}

void Caja::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {

		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		
		upload(aMat);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glColor4dv(value_ptr(mColor));
		mTexture->bind(GL_REPLACE);

		mMesh->render();

		mTexture->unbind();
		glCullFace(GL_FRONT);
		mTexture2->bind(GL_REPLACE);

		mMesh->render();

		mTexture2->unbind();
		glColor3d(1, 1, 1);
		glDisable(GL_CULL_FACE);
	}
}

//-------------------------------------------------------------------------

Suelo::Suelo(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
{
	mMesh = Mesh::generaRectanguloTexCor(w, h, rw, rh);
	setModelMat(glm::rotate(dmat4(1), radians(-90.0), dvec3(1, 0, 0)));
}

Suelo::~Suelo()
{
	delete mMesh; mMesh = nullptr;
}


void Suelo::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		mTexture->bind(GL_REPLACE);

		mMesh->render();

		mTexture->unbind();
	}
}

//-------------------------------------------------------------------------

#include "IG1App.h"
Image::Image(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
{
	mMesh = Mesh::generaRectanguloTexCor(w, h, rw, rh);
	setModelMat(glm::rotate(dmat4(1), radians(90.0), dvec3(1, 0, 0)));
	setModelMat(glm::translate(mModelMat, dvec3(0, 100.0, -0.1)));
}

Image::~Image()
{
	delete mMesh; mMesh = nullptr;
}

void Image::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		mTexture->bind(GL_REPLACE);

		mMesh->render();

		mTexture->unbind();
	}
}

void Image::update()
{
	mTexture->loadColorBuffer(IG1App::s_ig1app.winWidth(), IG1App::s_ig1app.winHeight(), GL_FRONT);
}

//-------------------------------------------------------------------------

Celda::Celda(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
{
	mMesh = Mesh::generaRectanguloTexCor(w, h / 2, rw, rh);
	setModelMat(glm::translate(mModelMat, dvec3(0, h / 4, 0)));
}

Celda::~Celda()
{
	delete mMesh; mMesh = nullptr;
}


void Celda::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
		
		mTexture->bind(GL_REPLACE);

		aMat = translate(aMat, dvec3(0, 0, 300));
		upload(aMat); // P1
		mMesh->render();

		aMat = translate(aMat, dvec3(0, 0, -600));
		upload(aMat); // P2
		mMesh->render();

		aMat = translate(aMat, dvec3(0, 0, 300));
		aMat = translate(aMat, dvec3(300, 0, 0));
		aMat = rotate(aMat, radians(90.0), dvec3(0, 1, 0));
		upload(aMat); // P3
		mMesh->render();

		aMat = translate(aMat, dvec3(0, 0, -600));
		upload(aMat); // P4
		mMesh->render();

		mTexture->unbind();

		glClear(GL_DEPTH_BUFFER_BIT);
		glDisable(GL_BLEND);
	} // no se cómo, pero me ha salido a la primera :D
}

//-------------------------------------------------------------------------

void Sphere::render(glm::dmat4 const& modelViewMat) const {
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	// Aquí se puede fijar el color de la esfera así:
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.0, 0.21, 0.45);
	// Aquí se puede fijar el modo de dibujar la esfera:
	gluQuadricDrawStyle(q, GLU_FILL);
	gluSphere(q, r, 50, 50);
	// Aquí se debe recuperar el color:
	glColor3f(1.0, 1.0, 1.0);
}

//-------------------------------------------------------------------------

void Cylinder::render(glm::dmat4 const& modelViewMat) const {
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	// Aquí se puede fijar el color de la esfera así:
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.0, 0.21, 0.45);
	// Aquí se puede fijar el modo de dibujar la esfera:
	gluQuadricDrawStyle(q, GLU_FILL);
	gluCylinder(q, rBase, rTop, height, slices, 2);
	// Aquí se debe recuperar el color:
	glColor3f(1.0, 1.0, 1.0);
}

//-------------------------------------------------------------------------

void Disk::render(glm::dmat4 const& modelViewMat) const {
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);

	if (mTexture != nullptr) {
		glEnable(GL_BLEND);
		gluQuadricTexture(q, GL_TRUE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		mTexture->bind(GL_REPLACE);
		gluQuadricDrawStyle(q, GLU_FILL); //
		gluDisk(q, rInner, rOutter, slices, 200);
		mTexture->unbind();
		glClear(GL_DEPTH_BUFFER_BIT);
		gluQuadricTexture(q, GL_FALSE);
		glDisable(GL_BLEND);
	}
	else {
		// Aquí se puede fijar el color de la esfera así:
		glEnable(GL_COLOR_MATERIAL);
		glColor3f(0.0, 0.21, 0.45);
		// Aquí se puede fijar el modo de dibujar la esfera:
		gluQuadricDrawStyle(q, GLU_FILL);
		gluDisk(q, rInner, rOutter, slices, 200);
		// Aquí se debe recuperar el color:
		glColor3f(1.0, 1.0, 1.0);
	}
}

//-------------------------------------------------------------------------

void PartialDisk::render(glm::dmat4 const& modelViewMat) const {
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	// Aquí se puede fijar el color de la esfera así:
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1.0, 1.0, 0.0);
	// Aquí se puede fijar el modo de dibujar la esfera:
	gluQuadricDrawStyle(q, GLU_FILL);
	gluPartialDisk(q, rInner, rOutter, slices, 10, 50.0, 90.0);
	// Aquí se debe recuperar el color:
	glColor3f(1.0, 1.0, 1.0);
}

//-------------------------------------------------------------------------

AnilloCuadrado::AnilloCuadrado()
{
	inMesh = IndexMesh::generaAnilloCuadradoIndexado();
}

AnilloCuadrado::~AnilloCuadrado()
{
	delete inMesh; inMesh = nullptr;
}


void AnilloCuadrado::render(glm::dmat4 const& modelViewMat) const
{
	if (inMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		glEnable(GL_COLOR_MATERIAL);
		inMesh->render();
	}
}

//-------------------------------------------------------------------------

Cubo::Cubo(GLdouble l)
{
	inMesh = IndexMesh::generaCuboConTapasIndexado(l);
	inMesh->buildNormalVectors();
}

Cubo::~Cubo()
{
	delete inMesh; inMesh = nullptr;
}


void Cubo::render(glm::dmat4 const& modelViewMat) const
{
	if (inMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		glEnable(GL_COLOR_MATERIAL);
		inMesh->render();
	}
}

//-------------------------------------------------------------------------

void CompoundEntity::render(glm::dmat4 const& modelViewMat) const
{
	for (Abs_Entity* el : gObjects)
	{
		el->render(modelViewMat);
	}
}

TIE::TIE(Texture* t)
{
	glm::dmat4 mAux;

	// Ambas alas
	Disk* wingL = new Disk(0.0, 200.0, 6.0);
	mAux = wingL->modelMat();
	mAux = translate(mAux, dvec3(-250, 0, 0));
	mAux = rotate(mAux, radians(90.0), dvec3(0, 1, 0));
	wingL->setModelMat(mAux);
	addEntity(wingL);
	wingL->setTexture(t);

	Disk* wingR = new Disk(0.0, 200.0, 6.0);
	mAux = wingR->modelMat();
	mAux = translate(mAux, dvec3(250, 0, 0));
	mAux = rotate(mAux, radians(90.0), dvec3(0, 1, 0));
	wingR->setModelMat(mAux);
	addEntity(wingR);
	wingR->setTexture(t);

	// Core
	Sphere* core = new Sphere(100.0);
	addEntity(core);

	// Shaft
	Cylinder* shaft = new Cylinder(50.0, 50.0, 500.0, 100.0);
	mAux = shaft->modelMat();
	mAux = translate(mAux, dvec3(250, 0, 0));
	mAux = rotate(mAux, radians(-90.0), dvec3(0, 1, 0));
	shaft->setModelMat(mAux);
	addEntity(shaft);

	// Front
	CompoundEntity* front = new CompoundEntity();
	Cylinder* base = new Cylinder(75.0, 75.0, 100.0, 100.0);
	mAux = base->modelMat();
	mAux = translate(mAux, dvec3(0, 0, 25));
	mAux = rotate(mAux, radians(0.0), dvec3(0, 1, 0));
	base->setModelMat(mAux);
	front->addEntity(base);

	Disk* tapa = new Disk(0.0, 75.0, 100.0);
	mAux = tapa->modelMat();
	mAux = translate(mAux, dvec3(0, 0, 120));
	mAux = rotate(mAux, radians(0.0), dvec3(0, 1, 0));
	tapa->setModelMat(mAux);
	front->addEntity(tapa);
	
	addEntity(front);
}
