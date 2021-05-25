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
	void showAnilloCuadrado();
	void showCuboConTapas();
	void showCono();
	void showDoubleSpheres();
	void showGrid();
	void showGridCube();
	void showTieWithPlanet();

	void sceneDirLight(Camera const& cam) const;

	void setTexture(std::string fileName, GLuint n, GLubyte alpha = 255);
	Texture* loadTexture(std::string fileName, GLubyte alpha = 255);
	Texture* loadColorBuffer(GLint width, GLint height, GLint buffer);

	void addObject(Abs_Entity* en);
	void addIndexObject(EntityWithIndexMesh* in);

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
	int mId = 5; //
	std::vector<Texture*> gTextures;
	std::vector<Abs_Entity*> gObjects;					// Entities (graphic objects) of the scene (opacos)
	std::vector<Abs_Entity*> gBlendObjects;				// Entities (graphic objects) of the scene (translúcidos)
	std::vector<EntityWithIndexMesh*> gIndexObjects;		// los objetos de EntityWithIndexMesh (opacos)
	std::vector<EntityWithIndexMesh*> gBlendIndexObjects;	// los objetos de EntityWithIndexMesh (translúcidos)
};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_

