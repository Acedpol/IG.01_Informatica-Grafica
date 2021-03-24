#include "Scene.h"
#include "CheckML.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include "IG1App.h"

using namespace glm;
//-------------------------------------------------------------------------

void Scene::init()
{ 
	setGL();  // OpenGL settings
	
	// allocate memory and load resources
    // Lights
    // Textures
	if (mId == 0) { // 2D
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
	else if (mId == 1) { // 3D
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
		/*tf->loadColorBuffer(IG1App::s_ig1app.winWidth(), IG1App::s_ig1app.winHeight(), GL_FRONT);
		tf->save("..\\IG.01_app\\Bmps\\bitmap.bmp");*/
		tf->load("..\\IG.01_app\\Bmps\\container.bmp");
		gObjects.back()->setTexture(tf);
	}
    // Graphics objects (entities) of the scene
	

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
	gTextures.clear();
	gObjects.clear();
}
//-------------------------------------------------------------------------
void Scene::setGL() 
{
	// OpenGL basic setting
	glClearColor(0.0, 0.0, 0.0, 1.0);  // background color (alpha=1 -> opaque)
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


