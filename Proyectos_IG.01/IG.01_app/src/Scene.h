//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Entity.h"
#include "Light.h"


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

	void setLights();

public:
	Scene() {};
	~Scene() { free(); resetGL(); }; // al borrar la segunda escena se hac�a reseteo y pon�a GLColor (global) a color blanco (por defecto)

	Scene(const Scene& s) = delete;  // no copy constructor
	Scene& operator=(const Scene& s) = delete;  // no copy assignment
		
	void init();

    void render(Camera const& cam) const;

	void update();
	void changeScene(int id);
	
	void free(); // ahora es p�blico para poder vaciar la memoria de la segunda escena

	DirLight* g_DirLight() { return dirLight; };
	PosLight* g_PosLight() { return posLight; };
	SpotLight* g_SpotLight() { return spotLight; };
	std::vector<Light*> g_Lights() { return lights; };
	
	void allLights_OFF();
	void allLights_ON();

	void TIEsLightsOn();
	void TIEsLightsOff();

	void toggleSquadOrbit() { squadTIE->toggleOrbit(); };
	void toggleSquadTurn() { squadTIE->toggleTurn(); };
	void orbitSquad() { squadTIE->orbit(); };
	void rotateSquad() { squadTIE->rota(); };
	/*void setPosLight() {
		posLight->setDiff({ 1,1,0,1 });
		posLight->setPosDir({ 500,1000,0 });
	};*/

protected:
	void setGL();
	void resetGL();
	int mId = 1; //
	DirLight* dirLight = nullptr;
	PosLight* posLight = nullptr;
	SpotLight* spotLight = nullptr;
	std::vector<Light*> lights;
	std::vector<Texture*> gTextures;
	std::vector<Abs_Entity*> gObjects;					// Entities (graphic objects) of the scene (opacos)
	std::vector<Abs_Entity*> gBlendObjects;				// Entities (graphic objects) of the scene (transl�cidos)
	std::vector<EntityWithIndexMesh*> gIndexObjects;		// los objetos de EntityWithIndexMesh (opacos)
	std::vector<EntityWithIndexMesh*> gBlendIndexObjects;	// los objetos de EntityWithIndexMesh (transl�cidos)

	familyTIE* squadTIE = nullptr;

private:
	DirLight* initDirLight();
	PosLight* initPosLight();
	SpotLight* initSpotLight();
};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_

