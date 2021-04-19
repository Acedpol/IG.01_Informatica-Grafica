//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Entity.h"


#include <vector>

//-------------------------------------------------------------------------

class Scene	
{ 
private:
	void showScene_2D();
	void showScene_3D();
	void showScene_QuadricObjects();
	void showScene_imperialTIE();
	void sceneDirLight(Camera const& cam) const;
public:
	Scene() {};
	~Scene() { free(); resetGL(); }; // al borrar la segunda escena se hacía reseteo y ponía GLColor (global) a color blanco (por defecto)

	Scene(const Scene& s) = delete;  // no copy constructor
	Scene& operator=(const Scene& s) = delete;  // no copy assignment
		
	void init();

    void render(Camera const& cam) const;

	void update();
	void changeScene(int id);
	
	void free(); // ahora es público para poder vaciar la memoria de la segunda escena
	
protected:
	void setGL();
	void resetGL();
	int mId = 4;
	std::vector<Abs_Entity*> gObjects;  // Entities (graphic objects) of the scene
	std::vector<Texture*> gTextures;
};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_

