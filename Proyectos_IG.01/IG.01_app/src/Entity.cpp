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
		glEnable(GL_COLOR_MATERIAL);
		mMesh->render();
		glLineWidth(1);
		glDisable(GL_COLOR_MATERIAL);
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

		glEnable(GL_COLOR_MATERIAL);
		glColor4dv(value_ptr(mColor));
		glPointSize(2);
		mMesh->render();
		glColor4d( 1.0, 1.0, 1.0, 1.0 );
		glPointSize(1);
		glDisable(GL_COLOR_MATERIAL);
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
		glPolygonMode(GL_BACK, GL_FILL);
		glPolygonMode(GL_FRONT, GL_LINE);
		mMesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
		glPolygonMode(GL_BACK, GL_LINE);
		glPolygonMode(GL_FRONT, GL_FILL);
		mMesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
	glColor3f(0.0f, 0.21f, 0.45f);
	// Aquí se puede fijar el modo de dibujar la esfera:
	gluQuadricDrawStyle(q, GLU_FILL);
	gluSphere(q, r, 50, 50);
	// Aquí se debe recuperar el color:
	glColor3f(1.0f, 1.0f, 1.0f);
	glDisable(GL_COLOR_MATERIAL);
}

//-------------------------------------------------------------------------

void Cylinder::render(glm::dmat4 const& modelViewMat) const {
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.0f, 0.21f, 0.45f);
	gluQuadricDrawStyle(q, GLU_FILL);
	gluCylinder(q, rBase, rTop, height, slices, 2);
	glColor3f(1.0f, 1.0f, 1.0f);
	glDisable(GL_COLOR_MATERIAL);
}

//-------------------------------------------------------------------------

void Disk::render(glm::dmat4 const& modelViewMat) const {
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);

	if (mTexture != nullptr) {
		gluQuadricTexture(q, GL_TRUE);
		mTexture->bind(GL_MODULATE); //
		gluQuadricDrawStyle(q, GLU_FILL); //
		gluDisk(q, rInner, rOutter, slices, 200);
		mTexture->unbind();
		gluQuadricTexture(q, GL_FALSE);
	}
	else {
		glEnable(GL_COLOR_MATERIAL);
		glColor3f(0.0f, 0.21f, 0.45f);
		gluQuadricDrawStyle(q, GLU_FILL);
		gluDisk(q, rInner, rOutter, slices, 200);
		glColor3f(1.0f, 1.0f, 1.0f);
		glDisable(GL_COLOR_MATERIAL);
	}
}

//-------------------------------------------------------------------------

void PartialDisk::render(glm::dmat4 const& modelViewMat) const {
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1.0f, 1.0f, 0.0f);
	gluQuadricDrawStyle(q, GLU_FILL);
	gluPartialDisk(q, rInner, rOutter, slices, 10, 50.0, 90.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glDisable(GL_COLOR_MATERIAL);
}

//-------------------------------------------------------------------------

AnilloCuadrado::AnilloCuadrado()
{
	inMesh = IndexMesh::generaAnilloCuadradoIndexado();
	//inMesh->buildNormalVectors();
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
		glColor3f(mColor.r, mColor.g, mColor.b);
		inMesh->render();
		glColor3f(1.0f, 1.0f, 1.0f);
		glDisable(GL_COLOR_MATERIAL);
	}
}

//-------------------------------------------------------------------------

Cubo::Cubo(GLdouble l)
{
	inMesh = IndexMesh::generaCuboConTapasIndexado(l);
	//inMesh->buildNormalVectors();
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
		glDisable(GL_COLOR_MATERIAL);
	}
}

//-------------------------------------------------------------------------

void CompoundEntity::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);

	for (Abs_Entity* el : gObjects)
	{
		el->render(aMat);
	}

	/*if (!lights.empty()) {
		for (Light* li : lights)
		{
			glm::dmat4 auxMat = modelViewMat * mModelMat;
			li->upload(auxMat);
		}
	}*/

	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (Abs_Entity* el : gBlendObjects)
	{
		el->render(aMat);
	}
	//glClear(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
}

//-------------------------------------------------------------------------

TIE::TIE(Texture* t, bool SCALE)
{
	glm::dmat4 mAux;

	// Ambas alas
	Disk* wingL = new Disk(0.0, 200.0, 6);
	mAux = wingL->modelMat();
	mAux = translate(mAux, dvec3(-250, 0, 0));
	mAux = rotate(mAux, radians(90.0), dvec3(0, 1, 0));
	wingL->setModelMat(mAux);
	addBlendEntity(wingL);
	wingL->setTexture(t);

	Disk* wingR = new Disk(0.0, 200.0, 6);
	mAux = wingR->modelMat();
	mAux = translate(mAux, dvec3(250, 0, 0));
	mAux = rotate(mAux, radians(90.0), dvec3(0, 1, 0));
	wingR->setModelMat(mAux);
	addBlendEntity(wingR);
	wingR->setTexture(t);

	// Core
	Sphere* core = new Sphere(100.0);
	addEntity(core);

	// Shaft
	Cylinder* shaft = new Cylinder(50.0, 50.0, 500.0, 100);
	mAux = shaft->modelMat();
	mAux = translate(mAux, dvec3(250, 0, 0));
	mAux = rotate(mAux, radians(-90.0), dvec3(0, 1, 0));
	shaft->setModelMat(mAux);
	addEntity(shaft);

	// Front
	CompoundEntity* front = new CompoundEntity();
	Cylinder* base = new Cylinder(75.0, 75.0, 100.0, 100);
	mAux = base->modelMat();
	mAux = translate(mAux, dvec3(0, 0, 25));
	mAux = rotate(mAux, radians(0.0), dvec3(0, 1, 0));
	base->setModelMat(mAux);
	front->addEntity(base);

	Disk* tapa = new Disk(0.0, 75.0, 100);
	mAux = tapa->modelMat();
	mAux = translate(mAux, dvec3(0, 0, 120));
	mAux = rotate(mAux, radians(0.0), dvec3(0, 1, 0));
	tapa->setModelMat(mAux);
	front->addEntity(tapa);

	addEntity(front);

	if (SCALE) {
		mAux = modelMat();
		mAux = scale(mAux, dvec3(0.1, 0.1, 0.1));
		setModelMat(mAux);
	}

	// Light
	setLight();
}

void TIE::setLight()
{
	light = new SpotLight();
	light->setPosDir(dvec3(0.0, 0.0, 0.0));
	light->setAmb(fvec4(0.0, 0.0, 0.0, 1.0));
	light->setDiff(fvec4(1.0, 1.0, 1.0, 1.0));
	light->setSpec(fvec4(0.5, 0.5, 0.5, 1.0));
	light->setSpot(fvec3(0.0, -1.0, 0.0), 45.0, 0.2);
	light->disable();
	light->enable();
}

//-------------------------------------------------------------------------

Cono::Cono(GLdouble h, GLdouble r, GLuint n, bool fill) {
	renderTy_ = fill;
	// h=altura del cono, r=radio de la base
    // n=número de muestras, m=número de puntos del perfil
    int m = 3;
    dvec3* perfil = new dvec3[m];
    perfil[0] = dvec3(0.5, 0.0, 0.0);
    perfil[1] = dvec3(r, 0.0, 0.0);
    perfil[2] = dvec3(0.5, h, 0.0);
    mMesh = MbR::generaIndexMeshByRevolution(m,  n,  perfil);
}

void Cono::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {

		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		glEnable(GL_COLOR_MATERIAL);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glColor3f(0.0f, 0.25f, 0.42f);

		mMesh->render();

		glColor3f(1.0f, 1.0f, 1.0f);
		glDisable(GL_COLOR_MATERIAL);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

//-------------------------------------------------------------------------

Esfera::Esfera(GLdouble r, GLuint p, GLuint m, bool fill) {
	renderTy_ = fill;
	glm::dvec3* perfil = new dvec3[p];

	// construccion del circulo:
	double ang = 0.0;
	double inc = 180.0 / (p - 1);

	for (uint i = 0; i < p; i++)
	{
		double y = 0 + r * cos(radians(ang));
		double x = 0 + r * sin(radians(ang));
		ang = ang + inc;
		perfil[i] = glm::dvec3(x, -y, 0.0);
	}

	mMesh = MbR::generaIndexMeshByRevolution(p, m, perfil);
}

void Esfera::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		if (material != nullptr){
			glShadeModel(GL_FLAT);
			material->upload();
		}
		else{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glEnable(GL_COLOR_MATERIAL);
			glColor3f(mColor.r, mColor.g, mColor.b);
		}		

		mMesh->render();

		if (material==nullptr) {
			glColor3f(1.0f, 1.0f, 1.0f);
			glDisable(GL_COLOR_MATERIAL);
		}

	}
}

//-------------------------------------------------------------------------

Grid::Grid(GLdouble lado, GLuint nDiv, bool fill, Texture* t)
{
	renderTy_ = fill;

	if (t != nullptr) {
		mMesh = MbR::generaGridTex(lado, nDiv);
		mTexture = t;
	}
	else {
		mMesh = MbR::generaGrid(lado, nDiv);
	}
}

void Grid::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		if (mTexture != nullptr) {
			mTexture->bind(GL_REPLACE);
		}
		glEnable(GL_COLOR_MATERIAL);
		glLineWidth(2);
		if (!renderTy_) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glColor3f(0.0f, 0.25f, 0.42f);

		mMesh->render();

		glColor3f(1.0f, 1.0f, 1.0f);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(1);
		glDisable(GL_COLOR_MATERIAL);
		if (mTexture != nullptr) {
			mTexture->unbind();
		}
	}
}

//-------------------------------------------------------------------------

GridCube::GridCube(GLdouble lado, GLuint nDiv, bool fill, GLuint scale)
{
	GLdouble L = lado * scale;		//40*5
	GLuint nDiv_ = nDiv * scale;	//4*5

	Texture* tex_ = new Texture();
	tex_->load("..\\IG.01_app\\Bmps\\stones.bmp", 255);

	Texture* tex2_ = new Texture();
	tex2_->load("..\\IG.01_app\\Bmps\\checker.bmp", 255);
	
	addFloor(L, nDiv_, fill, tex2_, 0);
	for (int i = 0; i < 4; i++) addWall(L, nDiv_, fill, tex_, i);
	addFloor(L, nDiv_, fill, tex2_, GLuint(L));
}

void GridCube::addFloor(GLdouble lado, GLuint nDiv, bool fill, Texture* tex, GLuint height)
{
	glm::dmat4 mAux;
	Grid* gr;
	gr = new Grid(lado, nDiv, fill, tex);
	mAux = gr->modelMat();
	mAux = translate(mAux, dvec3(lado / 2, height, lado / 2));
	gr->setModelMat(mAux);
	gr->setTexture(tex);
	if (tex->alpha() != 255) gBlendObjects.push_back(gr);
	else gObjects.push_back(gr);
}

void GridCube::addWall(GLdouble lado, GLuint nDiv, bool fill, Texture* tex, GLuint side)
{
	glm::dmat4 mAux;
	Grid* gr;
	gr = new Grid(lado, nDiv, fill, tex);
	mAux = gr->modelMat();

	switch (side)
	{
	case 0:	// plano ZY
		mAux = translate(mAux, dvec3(0, lado / 2, lado / 2));
		//mAux = rotate(mAux, radians(-90.0), dvec3(0.0, 0.0, 1.0));
		mAux = rotate(mAux, radians(-90.0), dvec3(0.0, 1.0, 0.0));
		mAux = rotate(mAux, radians(-90.0), dvec3(1.0, 0.0, 0.0));
		break;
	case 1:	// plano XY
		mAux = translate(mAux, dvec3(lado / 2, lado / 2, 0));
		mAux = rotate(mAux, radians(90.0), dvec3(1.0, 0.0, 0.0));
		break;
	case 2:	// paralelo al plano ZY
		mAux = translate(mAux, dvec3(lado, lado / 2, lado / 2));
		//mAux = rotate(mAux, radians(90.0), dvec3(0.0, 0.0, 1.0));
		mAux = rotate(mAux, radians(-90.0), dvec3(0.0, 1.0, 0.0));
		mAux = rotate(mAux, radians(-90.0), dvec3(1.0, 0.0, 0.0));
		break;
	case 3:	// paralelo al plano XY
		mAux = translate(mAux, dvec3(lado / 2, lado / 2, lado));
		mAux = rotate(mAux, radians(-90.0), dvec3(1.0, 0.0, 0.0));
		break;
	default:
		break;
	}
	
	gr->setModelMat(mAux);
	gr->setTexture(tex);
	if (tex->alpha() != 255) gBlendObjects.push_back(gr);
	else gObjects.push_back(gr);
}

void EntityWithMaterial::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		if (mTexture != nullptr) {
			mTexture->bind(GL_REPLACE);
		}
		glEnable(GL_COLOR_MATERIAL);
		glLineWidth(2);
		if (!renderTy_) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glColor3f(0.0f, 0.25f, 0.42f);

		mMesh->render();

		glColor3f(1.0f, 1.0f, 1.0f);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(1);
		glDisable(GL_COLOR_MATERIAL);
		if (mTexture != nullptr) {
			mTexture->unbind();
		}
	}
}

//-------------------------------------------------------------------------

TIE* familyTIE::newTIE(Texture* t, int x, int z)
{
	glm::dmat4 mAux;

	TIE* tie = new TIE(t, true);

	mAux = tie->modelMat();
	mAux = translate(mAux, dvec3(x, 0, z));
	//mAux = scale(mAux, dvec3(0.1, 0.1, 0.1));
	tie->setModelMat(mAux);

	gObjects.push_back(tie);
	lights.push_back(tie->getLight());

	return tie;
}

familyTIE::familyTIE(Texture* t, bool mode)
{
	glm::dmat4 mAux;

	s_orbit = false;
	s_turn = false;

	if (mode) {
		TIE* tie1 = new TIE(t, false);
		gObjects.push_back(tie1);
		lights.push_back(tie1->getLight());

		TIE* tie2 = new TIE(t, false);
		mAux = tie2->modelMat();
		mAux = translate(mAux, dvec3(200, 100, 0));
		mAux = scale(mAux, dvec3(0.3, 0.3, 0.3));
		tie2->setModelMat(mAux);
		gObjects.push_back(tie2);
		lights.push_back(tie2->getLight());

		TIE* tie3 = new TIE(t, false);
		mAux = tie3->modelMat();
		mAux = translate(mAux, dvec3(-200, 100, 0));
		mAux = scale(mAux, dvec3(0.3, 0.3, 0.3));
		tie3->setModelMat(mAux);
		gObjects.push_back(tie3);
		lights.push_back(tie2->getLight());
	}
	else {
		TIE* tie1 = newTIE(t, 0, 500);

		TIE* tie2 = newTIE(t, 500, 0);
		mAux = tie2->modelMat();
		mAux = rotate(mAux, radians(-30.0), dvec3(0.0, 1.0, 1.0));
		tie2->setModelMat(mAux);

		TIE* tie3 = newTIE(t, -500, 0);
		mAux = tie3->modelMat();
		mAux = rotate(mAux, radians(30.0), dvec3(0.0, 0.0, 1.0));
		tie3->setModelMat(mAux);
	}
}

void familyTIE::update()
{
	if (s_orbit) {
		orbit();
	}
	if (s_turn) {
		rota();
	}
}

void familyTIE::orbit()
{
	mModelMat = translate(mModelMat, dvec3(0, -520, 0));
	mModelMat = rotate(mModelMat, radians(-1.0), dvec3(0, 0, 1));
	mModelMat = translate(mModelMat, dvec3(0, 520, 0));
}

void familyTIE::rota()
{
	mModelMat = rotate(mModelMat, radians(1.0), dvec3(0, 1, 0));
}

//void familyTIE::TIEsLightsOn()
//{
//	for (Light* li : lights)
//	{
//		li->enable();
//	}
//}
//
//void familyTIE::TIEsLightsOff()
//{
//	for (Light* li : lights)
//	{
//		li->disable();
//	}
//}

//familyTIE::~familyTIE()
//{
//	for (TIE* tie : family)
//	{
//		delete tie;  tie = nullptr;
//	}
//	family.clear();
//}
