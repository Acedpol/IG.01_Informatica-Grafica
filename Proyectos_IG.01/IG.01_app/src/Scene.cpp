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
		gObjects.push_back(new EjesRGB(400.0));
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
	gObjects.clear();
}
//-------------------------------------------------------------------------
void Scene::setGL() 
{
	// OpenGL basic setting
	glClearColor(0.0, 0.0, 0.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 

}
//-------------------------------------------------------------------------
void Scene::resetGL() 
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	
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


