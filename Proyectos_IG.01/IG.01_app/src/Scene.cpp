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

	//gObjects.push_back(new Poligono(3, 50, { 1.0,1.0,0.0,1.0 })); // triangulo amarillo
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
	Texture* ts = new Texture();
	gObjects.push_back(new Suelo(600.0, 600.0, 10, 10));
	ts->load("..\\IG.01_app\\Bmps\\baldosaC.bmp");
	gTextures.push_back(ts);
	gObjects.back()->setTexture(ts);

	// estrella 3D
	Texture* te = new Texture();
	gObjects.push_back(new Estrella3D(100.0, 6, 50.0));
	te->load("..\\IG.01_app\\Bmps\\baldosaP.bmp");
	gTextures.push_back(te);
	gObjects.back()->setTexture(te);

	// caja
	Texture* t = new Texture();
	Texture* t2 = new Texture();
	gObjects.push_back(new Caja(100.0));
	t->load("..\\IG.01_app\\Bmps\\container.bmp");
	t2->load("..\\IG.01_app\\Bmps\\papelC.bmp");
	gTextures.push_back(t);
	gTextures.push_back(t2);
	gObjects.back()->setTexture(t);
	gObjects.back()->setTexture2(t2);

	// foto
	Texture* tf = new Texture();
	gObjects.push_back(new Image(100.0, 100.0, 1, 1));
	tf->loadColorBuffer(IG1App::s_ig1app.winWidth(), IG1App::s_ig1app.winHeight(), GL_FRONT);
	gTextures.push_back(tf);
	gObjects.back()->setTexture(tf);

	// celda con blend (traslúcida)
	Texture* tc = new Texture();
	Celda* s = new Celda(600.0, 600.0, 1, 1);
	gObjects.push_back(s);
	tc->load("..\\IG.01_app\\Bmps\\windowV.bmp", 100);
	gTextures.push_back(tc);
	gObjects.back()->setTexture(tc);
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
	/*TIE* tie = new TIE();
	gObjects.push_back(tie);
	Sphere* core = new Sphere(100.0);
	tie->addEntity(core);

	Cylinder* shaft = new Cylinder(50.0, 50.0, 500.0, 100.0);
	glm::dmat4 mAux = shaft->modelMat();
	mAux = translate(mAux, dvec3(250, 0, 0));
	mAux = rotate(mAux, radians(-90.0), dvec3(0, 1, 0));
	shaft->setModelMat(mAux);
	tie->addEntity(shaft);


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
	tie->addEntity(front);
	

	Texture* t = new Texture();
	t->load("..\\IG.01_app\\Bmps\\noche.bmp", 200);
	gTextures.push_back(t);

	Disk* wingL = new Disk(0.0, 200.0, 6.0);
	mAux = wingL->modelMat();
	mAux = translate(mAux, dvec3(-250, 0, 0));
	mAux = rotate(mAux, radians(90.0), dvec3(0, 1, 0));
	wingL->setModelMat(mAux);
	tie->addEntity(wingL);
	gObjects.back()->setTexture(t);

	Disk* wingR = new Disk(0.0, 200.0, 6.0);
	mAux = wingR->modelMat();
	mAux = translate(mAux, dvec3(250, 0, 0));
	mAux = rotate(mAux, radians(90.0), dvec3(0, 1, 0));
	wingR->setModelMat(mAux);
	tie->addEntity(wingR);
	gObjects.back()->setTexture(t);*/
}

//-------------------------------------------------------------------------

void Scene::init()
{ 
	setGL();  // OpenGL settings
	
	// allocate memory and load resources
    // Lights
    // Textures

	// Graphics objects (entities) of the scene
	if (mId == 0) { // 2D
		showScene_2D();
	}
	else if (mId == 1) { // 3D -> Ortogonal
		showScene_3D();
	}
	else if (mId == 2) { // 3D -> Perspectiva (Testing Camara)
		showScene_3D();
		// el cambio de camara se hace en "void IG1App::key(unsigned char key, int x, int y)"
	}
	else if (mId == 3) {
		showScene_QuadricObjects();
	}
	else if (mId == 4) {
		showScene_imperialTIE();
	}
	else if (mId == 5) {
		gObjects.push_back(new EjesRGB(400.0));

		AnilloCuadrado* a = new AnilloCuadrado();
		gObjects.push_back(a);
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
	gObjects.clear();
	gTextures.clear();
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

