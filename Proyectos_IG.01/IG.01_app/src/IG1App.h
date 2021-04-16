//#pragma once
#ifndef _H_IG1App_H_
#define _H_IG1App_H_

//#include <Windows.h>
//#include <gl/GL.h>    // OpenGL
//#include <gl/GLU.h>   // OpenGL Utility Library
//#include <GL/glut.h>  // OpenGL Utility Toolkit

#include <GL/freeglut.h>  // OpenGL Utility Toolkit
#include <glm.hpp>        // OpenGL Mathematics

#include "Viewport.h"
#include "Camera.h"
#include "Scene.h"

//-------------------------------------------------------------------------

class IG1App
{
public:  
	// static single instance (singleton pattern)
	static IG1App s_ig1app;

	IG1App(IG1App const & J) = delete; // no copy constructor
	void operator =(IG1App const & J) = delete; // no copy assignment

	static int winWidth() { return IG1App::s_ig1app.mWinW; };
	static int winHeight() { return IG1App::s_ig1app.mWinH; };
	
	// Viewport position and size
	Viewport const& viewPort() { return *mViewPort; };
	// Camera position, view volume and projection
	Camera const& camera() { return *mCamera; };
	// Graphics objects of the scene
	Scene const& scene() { return *mScene; };

	void run();    // the main event processing loop
	void close();  // the application
	void update();  
	
protected:

	IG1App() {};
	~IG1App() { close(); };

	void init();
	void iniWinOpenGL();
	void free();   
 
	void display() const;   // the scene
	void display_1Vista() const;
	void display_2Vistas() const;
	void display_2Escenas() const;

	void resize(int newWidth, int newHeight);   // the viewport (without changing the scale) 
	void key(unsigned char key, int x, int y);  // keypress event
	void specialKey(int key, int x, int y);     // keypress event for special characters

	// static callbacks 
	static void s_display() { s_ig1app.display(); };
	static void s_resize(int newWidth, int newHeight) { s_ig1app.resize(newWidth, newHeight); };
	static void s_key(unsigned char key, int x, int y) { s_ig1app.key(key, x, y); };
	static void s_specialKey(int key, int x, int y) { s_ig1app.specialKey(key, x, y); };
	static void s_update() { s_ig1app.update(); };

	// mouse events callbacks
	static void s_mouse(int button, int state, int x, int y) { s_ig1app.mouse(button, state, x, y); };
	static void s_motion(int x, int y) { s_ig1app.motion(x, y); };
	static void s_mouseWheel(int n, int d, int x, int y) { s_ig1app.mouseWheel(n, d, x, y); };

	// captura, en mCoord, las coordenadas del ratón (x, y), y en mBot el botón pulsado.
	void mouse(int button, int state, int x, int y);
	// captura las coordenadas del ratón, obtiene el desplazamiento con respecto a las anteriores coordenadas 
	// y, si el botón pulsado es el derecho, mueve la cámara en sus ejes mRight (horizontal) y mUpward (vertical),
	// mientras que si es el botón izquierdo, rota la cámara alrededor de la escena.
	void motion(int x, int y);
	void motionCamera(Camera *c, glm::dvec2 mp);
	// Si no está pulsada ninguna tecla modificadora, desplaza la cámara en su dirección de vista (eje mFront), 
	// hacia delante o hacia atrás según 'd' sea positivo o no; 
	// si se pulsa la tecla Ctrl, escala la escena de nuevo según el valor de 'd'.
	void mouseWheel(int n, int d, int x, int y);
	void mouseWheelCamera(Camera *c, int n, int d, glm::dvec2 mp);

	void chargeDoubleScene(int n);
	void disableDoubleScene();

	// Viewport position and size
	Viewport *mViewPort = nullptr;
	// Camera position, view volume and projection
	Camera *mCamera = nullptr;
	Camera *mCamera2 = nullptr;
	// Graphics objects of the scene
	Scene *mScene = nullptr;
	Scene *mScene2 = nullptr;
	
	bool m2Vistas = false; // duplicar las vistas
	bool m2Escenas = false; // duplicar las vistas
	glm::dvec2 mCoord; // mouse coords
	int mBot; // button clicked
	bool mStop = false; // main event processing loop
	int mWinId = 0;	    // window's identifier
	int mWinW = 800;    // window's width 
	int mWinH = 600;    // window's height
	bool movement = false;
	GLuint mLastUpdateTime;
	bool leftMouseButtonDown = false;
	bool rightMouseButtonDown = false;
	bool scene01 = true;
	bool scene02 = false;
};
//-------------------------------------------------------------------------

#endif //_H_IG1App_H_
