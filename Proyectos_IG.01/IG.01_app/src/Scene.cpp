#include "Scene.h"
#include "CheckML.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;
//-------------------------------------------------------------------------

void Scene::init()
{ 
	setGL();  // OpenGL settings
	
	// allocate memory and load resources
    // Lights
    // Textures
	if (mId == 0) {
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
	else if (mId == 1) {
		auto ejes = new EjesRGB(400.0); // ...trataba ponerlos con perspectiva isométrica
		//ejes->setModelMat(rotate(dmat4(1), (-30.0), dvec3(1, 0, 0)));
		//ejes->setModelMat(rotate(ejes->modelMat(), (30.0), dvec3(0, 1, 0)));
		gObjects.push_back(ejes);

		/*Texture* t = nullptr;
		t->load("Bmps/baldosaC.bmp");
		gTextures.push_back(t);*/
		gObjects.push_back(new Suelo(100.0, 80.0, 5, 10));
		/*Abs_Entity* obj = gObjects.back();
		obj->setTexture(t);*/

		//gObjects.push_back(new Estrella3D(100.0, 6, 50.0));
		//gObjects.push_back(new Caja(50.0));
		

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


