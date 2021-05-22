#include "Scene.h"
#include "CheckML.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include "IG1App.h"

using namespace glm;

//-------------------------------------------------------------------------

void Scene::showScene_2D()
{
	gObjects.push_back(new EjesRGB(400.0));

	gObjects.push_back(new Poligono(3, 50, { 1.0,1.0,0.0,1.0 })); // triangulo amarillo
	gObjects.push_back(new Poligono(200.0, 200, { 1.0,0.0,1.0,1.0 })); // circulo magenta
	gObjects.push_back(new Sierpinski(200.0, 4000, { 1.0,1.0,0.0,0.0 })); // sierpinski gris
	auto t = (new TrianguloRGB(25));
	gObjects.push_back(t); // triangulo RGB
	t->setModelMat(rotate(dmat4(1), (25.0), dvec3(0, 0, 1)));
	t->setModelMat(translate(t->modelMat(), dvec3(200, 0, 0)));
	auto r = new RectanguloRGB(1000, 500);
	gObjects.push_back(r); // rectangulo RGB
	r->setModelMat(translate(dmat4(1), dvec3(0, 0, -100)));
}

void Scene::showScene_3D()
{
	auto ejes = new EjesRGB(400.0);
	gObjects.push_back(ejes);

	// suelo
	Suelo* suelo = new Suelo(600.0, 600.0, 10, 10);
	suelo->setTexture(loadTexture("..\\IG.01_app\\Bmps\\baldosaC.bmp"));
	addObject(suelo);

	// estrella 3D
	Estrella3D* star3D = new Estrella3D(100.0, 6, 50.0);
	star3D->setTexture(loadTexture("..\\IG.01_app\\Bmps\\baldosaP.bmp"));
	addObject(star3D);

	// caja
	Caja* box = new Caja(100.0);
	box->setTexture(loadTexture("..\\IG.01_app\\Bmps\\container.bmp"));
	box->setTexture2(loadTexture("..\\IG.01_app\\Bmps\\papelC.bmp"));
	addObject(box);

	// foto
	Image* foto = new Image(100.0, 100.0, 1, 1);
	foto->setTexture(loadColorBuffer(IG1App::s_ig1app.winWidth(), IG1App::s_ig1app.winHeight(), GL_FRONT));
	addObject(foto);

	// celda con blend (trasl�cida)
	Celda* s = new Celda(600.0, 600.0, 1, 1);
	s->setTexture(loadTexture("..\\IG.01_app\\Bmps\\windowV.bmp", 100));
	addObject(s);
}

void Scene::showScene_QuadricObjects()
{
	gObjects.push_back(new EjesRGB(400.0));

	Sphere* esfera = new Sphere(100.0);
	gObjects.push_back(esfera);

	Cylinder* cono = new Cylinder(50.0, 0, 100.0, 100.0);
	glm::dmat4 mAux = cono->modelMat();
	mAux = translate(mAux, dvec3(0, 85, 0));
	mAux = rotate(mAux, radians(-90.0), dvec3(1.0, 0, 0));
	cono->setModelMat(mAux);
	gObjects.push_back(cono);

	Disk* disco = new Disk(100.0, 250.0, 10.0);
	mAux = disco->modelMat();
	mAux = translate(mAux, dvec3(0, 250, 0));
	mAux = rotate(mAux, radians(-90.0), dvec3(1.0, 0, 0));
	disco->setModelMat(mAux);
	gObjects.push_back(disco);

	PartialDisk* p_disco = new PartialDisk(100.0, 250.0, 10.0);
	mAux = p_disco->modelMat();
	mAux = translate(mAux, dvec3(0, 120, 0));
	mAux = rotate(mAux, radians(-90.0), dvec3(1.0, 0, 0));
	p_disco->setModelMat(mAux);
	gObjects.push_back(p_disco);
}

void Scene::showScene_imperialTIE()
{
	gObjects.push_back(new EjesRGB(400.0));

	Texture* t = new Texture();
	t->load("..\\IG.01_app\\Bmps\\noche.bmp", 200);
	gTextures.push_back(t);

	TIE* tie = new TIE(t);
	gObjects.push_back(tie);
}

void Scene::showAnilloCuadrado()
{
	gObjects.push_back(new EjesRGB(400.0));

	AnilloCuadrado* a = new AnilloCuadrado();
	gIndexObjects.push_back(a);
}

void Scene::showCuboConTapas()
{
	gObjects.push_back(new EjesRGB(400.0));

	Cubo* c = new Cubo(200);
	gIndexObjects.push_back(c);
}

void Scene::showCono()
{
	gObjects.push_back(new EjesRGB(400.0));

	Cono* c = new Cono(200, 150, 30, true);
	gObjects.push_back(c);
}

//-------------------------------------------------------------------------

void Scene::showDoubleSpheres()
{
	glm::dmat4 mAux;
	gObjects.push_back(new EjesRGB(400.0));

	Esfera* e = new Esfera(100, 21, 20, true);
	mAux = e->modelMat();
	mAux = translate(mAux, dvec3(200, 100, 0));
	e->setModelMat(mAux);
	gObjects.push_back(e);

	Sphere* esfera = new Sphere(100.0);
	mAux = esfera->modelMat();
	mAux = translate(mAux, dvec3(0, 100, 200));
	esfera->setModelMat(mAux);
	gObjects.push_back(esfera);
}

void Scene::showGrid()
{
	glm::dmat4 mAux;
	GLdouble L = 40;
	GLdouble scale = 5;
	gObjects.push_back(new EjesRGB(400.0));

	//Grid* e = new Grid(40, 4, false); -> ejemplo base
	Grid* gr = new Grid(L * scale, 4 * 5, true, loadTexture("..\\IG.01_app\\Bmps\\container.bmp", 255));
	mAux = gr->modelMat();
	mAux = translate(mAux, dvec3(L / 2 * scale, 0, L / 2 * scale));
	gr->setModelMat(mAux);
	gObjects.push_back(gr);
}

void Scene::showGridCube()
{
	GLdouble L = 40;
	GLuint nDiv = 4;
	GLdouble scale = 5;
	gObjects.push_back(new EjesRGB(400.0));

	GridCube* gr = new GridCube(L, nDiv, true, scale);
	gObjects.push_back(gr);
}

//-------------------------------------------------------------------------

void Scene::init()
{ 
	setGL();  // OpenGL settings
	
	// allocate memory and load resources
    // Lights
    // Textures

	// Graphics objects (entities) of the scene
	// el cambio de camara se hace en "void IG1App::key(unsigned char key, int x, int y)"
	if (mId == 10) {		// Escena 2D
		showScene_2D();
	}
	else if (mId == 9) {	// Escena 3D -> Ortogonal
		showScene_3D();
	}
	else if (mId == 8) {	// Escena 3D -> Perspectiva (Testing Camara)
		showScene_3D();
	}
	else if (mId == 7) {	// QuadricObjets -> la malla se contruye directamente cuando se dibuja
		showScene_QuadricObjects();
	}
	else if (mId == 6) {	// Cono formadas con malla por revoluci�n
		showCono();
	}
	else if (mId == 5) {	// Cubo formado por Grid
		showGridCube();
	}
	else if (mId == 4) {	// Dos esferas formadas con mallas por revoluci�n
		showDoubleSpheres();
	}
	else if (mId == 3) {	// Primer objeto formado por un IndexMesh -> objeto plano
		showAnilloCuadrado();
	}
	else if (mId == 2) {	// Segundo objeto con IndexMesh -> objeto 3D (cubo)
		showCuboConTapas();
	}
	else if (mId == 1) {	// Primer objeto formado como CompoundEntity
		showScene_imperialTIE();
	}
}

//-------------------------------------------------------------------------
void Scene::free() 
{ // release memory and resources   

	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}
	for (Texture* txt : gTextures)
	{
		delete txt;  txt = nullptr;
	}
	for (EntityWithIndexMesh* in : gIndexObjects)
	{
		delete in;  in = nullptr;
	}

	gIndexObjects.clear();
	gObjects.clear();
	gTextures.clear();

	for (Abs_Entity* el : gBlendObjects)
	{
		delete el;  el = nullptr;
	}
	for (EntityWithIndexMesh* in : gBlendIndexObjects) 
	{
		delete in;  in = nullptr;
	}

	gBlendIndexObjects.clear();
	gBlendObjects.clear();
}
//-------------------------------------------------------------------------

void Scene::setGL() 
{
	// OpenGL basic setting
	glClearColor(0.7, 0.8, 0.9, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test
	glEnable(GL_TEXTURE_2D);

}

//-------------------------------------------------------------------------

void Scene::resetGL() 
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	
	glDisable(GL_TEXTURE_2D);
}

//-------------------------------------------------------------------------

void Scene::render(Camera const& cam) const 
{
	sceneDirLight(cam); // luces activadas!
	cam.upload();

	for (Abs_Entity* el : gObjects)
	{
		el->render(cam.viewMat());
	}

	for (EntityWithIndexMesh* in : gIndexObjects) {
		in->render(cam.viewMat());
	}

	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (Abs_Entity* el : gBlendObjects)
	{
		el->render(cam.viewMat());
	}
	for (EntityWithIndexMesh* in : gBlendIndexObjects) {
		in->render(cam.viewMat());
	}
	//glClear(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);

	
}

//-------------------------------------------------------------------------

void Scene::update()
{
	for (Abs_Entity* el : gObjects)
	{
		el->update();
	}
}

void Scene::changeScene(int id)
{
	mId = id;
	free();
	init();
}

//-------------------------------------------------------------------------

void Scene::sceneDirLight(Camera const&cam) const 
{ 
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glm::fvec4 posDir = { 1, 1, 1, 0 }; 
	glMatrixMode(GL_MODELVIEW); 
	glLoadMatrixd(value_ptr(cam.viewMat())); 
	glLightfv(GL_LIGHT0, GL_POSITION, value_ptr(posDir)); 
	glm::fvec4 ambient = { 0, 0, 0, 1 };
	glm::fvec4 diffuse = { 1, 1, 1, 1 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 }; 
	glLightfv(GL_LIGHT0, GL_AMBIENT, value_ptr(ambient)); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, value_ptr(diffuse)); 
	glLightfv(GL_LIGHT0, GL_SPECULAR, value_ptr(specular));
}

// facilita a�adir textura a la �ltima entidad a�adida
void Scene::setTexture(std::string fileName, GLuint n, GLubyte alpha)
{
	Texture* t = new Texture();
	switch (n)
	{
	case 1:
		gObjects.back()->setTexture(loadTexture(fileName, alpha));
		break;
	case 2:
		gObjects.back()->setTexture2(loadTexture(fileName, alpha));
		break;
	default:
		delete t; t = nullptr;
		break;
	}
}

// carga una nueva textura a la escena y la devuelve
Texture* Scene::loadTexture(std::string fileName, GLubyte alpha)
{
	Texture* t = new Texture();
	t->load(fileName, alpha);
	gTextures.push_back(t);
	return t;
}

Texture* Scene::loadColorBuffer(GLint width, GLint height, GLint buffer)
{
	Texture* t = new Texture();
	t->loadColorBuffer(width, height, buffer);
	gTextures.push_back(t);
	return t;
}

void Scene::addObject(Abs_Entity* en)
{
	if (en->alphaTex() != 255) gBlendObjects.push_back(en);
	else gObjects.push_back(en);
}

void Scene::addIndexObject(EntityWithIndexMesh* in)
{
	if (in->alphaTex() != 255) gBlendIndexObjects.push_back(in);
	else gIndexObjects.push_back(in);
}

