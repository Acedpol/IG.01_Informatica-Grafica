#include "IG1App.h"
#include "CheckML.h"
#include <iostream>

using namespace std;

//-------------------------------------------------------------------------
// static single instance (singleton pattern)

IG1App IG1App::s_ig1app;  // default constructor (constructor with no parameters)

//-------------------------------------------------------------------------

void IG1App::close()  
{
	if (!mStop) {  // if main loop has not stopped
		cout << "Closing glut...\n";
		glutLeaveMainLoop();  // stops main loop and destroy the OpenGL context
		mStop = true;   // main loop stopped  
	}
	free();
}
//-------------------------------------------------------------------------

void IG1App::run()   // enters the main event processing loop
{
	if (mWinId == 0) { // if not initialized
		init();       // initialize the application 
		glutMainLoop();      // enters the main event processing loop 
		mStop = true;  // main loop has stopped  
	}
}
//-------------------------------------------------------------------------

void IG1App::init()
{
	// create an OpenGL Context
	iniWinOpenGL();   

	// create the scene after creating the context 
	// allocate memory and resources
	mViewPort = new Viewport(mWinW, mWinH); //glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)
	mCamera = new Camera(mViewPort);
	mScene = new Scene;
	
	mCamera->set2D_front();
	mScene->init();
}
//-------------------------------------------------------------------------

void IG1App::iniWinOpenGL() 
{  // Initialization
	cout << "Starting glut...\n";
	int argc = 0;
	glutInit(&argc, nullptr);
		
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);  // GLUT_CORE_PROFILE
	glutInitContextFlags(GLUT_DEBUG);		// GLUT_FORWARD_COMPATIBLE

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitWindowSize(mWinW, mWinH);   // window size
	//glutInitWindowPosition (140, 140);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH /*| GLUT_STENCIL*/); // RGBA colors, double buffer, depth buffer and stencil buffer   
	
	mWinId = glutCreateWindow("IG1App");  // with its associated OpenGL context, return window's identifier 
	
	// Callback registration
	glutReshapeFunc(s_resize);
	glutKeyboardFunc(s_key);
	glutSpecialFunc(s_specialKey);
	glutDisplayFunc(s_display);
	glutIdleFunc(s_update);

	// mouse events callbacks
	glutMouseFunc(s_mouse);
	glutMotionFunc(s_motion);
	glutMouseWheelFunc(s_mouseWheel);
	
	cout << glGetString(GL_VERSION) << '\n';
	cout << glGetString(GL_VENDOR) << '\n';
}
//-------------------------------------------------------------------------

void IG1App::free() 
{  // release memory and resources
	delete mScene; mScene = nullptr;
	delete mCamera; mCamera = nullptr;
	delete mViewPort; mViewPort = nullptr;
	// 2 escena en paralelo:
	delete mScene2; mScene2 = nullptr;
	delete mViewPort2; mViewPort2 = nullptr;
	//delete mCamera2; mCamera2 = nullptr;
}
//-------------------------------------------------------------------------

void IG1App::display() const   
{  // double buffering
	if (m2Vistas) {
		if (!m2Escenas)
			display_2Vistas();
		else
			display_2Escenas();
	}
	else {
		display_1Vista();
	}
}

void IG1App::display_1Vista() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clears the back buffer

	mScene->render(*mCamera);  // uploads the viewport and camera to the GPU

	glutSwapBuffers();	// swaps the front and back buffer
}

void IG1App::display_2Vistas() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clears the back buffer

	Camera auxCam = *mCamera;
	Viewport auxVP = *mViewPort;

	mViewPort->setSize(mWinW / 2, mWinH);
	auxCam.setSize(mViewPort->width(), mViewPort->height());

	//mScene->render(*mCamera);  // uploads the viewport and camera to the GPU
	//Vista usuario
	mViewPort->setPos(0, 0);
	mScene->render(auxCam);
	//Vista cenital
	mViewPort->setPos(mWinW / 2, 0);
	auxCam.setCenital(); 
	mScene->render(auxCam); 

	*mViewPort = auxVP; // recupera el puerto de vista

	glutSwapBuffers();	// swaps the front and back buffer
}

void IG1App::display_2Escenas() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clears the back buffer

	Camera auxCam = *mCamera;
	Viewport auxVP = *mViewPort;

	mViewPort->setSize(mWinW / 2, mWinH);
	auxCam.setSize(mViewPort->width(), mViewPort->height());

	//Vista usuario
	mViewPort->setPos(0, 0);
	mScene->render(auxCam);
	//Vista cenital
	mViewPort->setPos(mWinW / 2, 0);
	auxCam.set2D_front();
	mScene2->render(auxCam);

	*mViewPort = auxVP; // recupera el puerto de vista

	glutSwapBuffers();	// swaps the front and back buffer
}

//-------------------------------------------------------------------------

void IG1App::resize(int newWidth, int newHeight) 
{
	mWinW = newWidth; mWinH = newHeight;

	// Resize Viewport to the new window size
	mViewPort->setSize(newWidth, newHeight);

	// Resize Scene Visible Area such that the scale is not modified
	mCamera->setSize(mViewPort->width(), mViewPort->height()); 
}
//-------------------------------------------------------------------------

void IG1App::key(unsigned char key, int x, int y) 
{
	bool need_redisplay = true;
	
	switch (key) {
	case 27:  // Escape key 
		glutLeaveMainLoop();  // stops main loop and destroy the OpenGL context
	case '+':
		mCamera->setScale(+0.01);  // zoom in  (increases the scale)
		break;
	case '-':
		mCamera->setScale(-0.01);  // zoom out (decreases the scale)
		break;
	case 'l':
		mCamera->set3D();
		break;
	case 'o':
		mCamera->set2D_front();
		break;
	case 'b':
		mCamera->set2D_back();
		break;
	case 'p':
		mCamera->changePrj();
		break;
	case 'q':
		mCamera->orbit(1.0, 1.0);
		break;
	case 'k':
		m2Vistas = !m2Vistas;
		break;
	case 'j':
		m2Vistas = !m2Vistas;
		if (!m2Escenas) {
			m2Escenas = true;
			mScene2 = new Scene;
			mScene2->changeScene(0);
			//mCamera2 = new Camera(mViewPort);
			//mCamera2->set2D_front();
		}
		else {
			m2Escenas = false;
			mScene2->free(); mScene2 = nullptr;
			//delete mCamera2; mCamera2 = nullptr;
		}
		break;
	case 'r':
		s_resize(400, 200);
		break;
	case 'u':
		movement = !movement;
		break;
	case '0':
		mScene->changeScene(0);
		mCamera->set2D_front();
		break;
	case '1':
		mScene->changeScene(1);
		mCamera->setOrtogonal();
		break;
	case '2':
		mScene->changeScene(2);
		mCamera->setPerspective();
		break;
	default:
		need_redisplay = false;
		break;
	} //switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to display()
}
//-------------------------------------------------------------------------

void IG1App::specialKey(int key, int x, int y) 
{
	bool need_redisplay = true;
	int mdf = glutGetModifiers(); // returns the modifiers (Shift, Ctrl, Alt)

	switch (key) {
	case GLUT_KEY_RIGHT:
		if (mdf == GLUT_ACTIVE_CTRL)
			//mCamera->pitch(-1);   // rotates -1 on the X axis
		//else
			//mCamera->pitch(1);    // rotates 1 on the X axis
		break;
	case GLUT_KEY_LEFT:
		if (mdf == GLUT_ACTIVE_CTRL)
		    //mCamera->yaw(1);      // rotates 1 on the Y axis 
		//else 
			//mCamera->yaw(-1);     // rotate -1 on the Y axis 
		break;
	case GLUT_KEY_UP:
		//mCamera->roll(1);    // rotates 1 on the Z axis
		break;
	case GLUT_KEY_DOWN:
		//mCamera->roll(-1);   // rotates -1 on the Z axis
		break;
	default:
		need_redisplay = false;
		break;
	}//switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to display()
}

void IG1App::update() {
	if (movement && glutGet(GLUT_ELAPSED_TIME) - mLastUpdateTime > 45) {
		mLastUpdateTime = glutGet(GLUT_ELAPSED_TIME);
		mScene->update();
		glutPostRedisplay();
		
	}
}
//-------------------------------------------------------------------------

void IG1App::mouse(int button, int state, int x, int y)
{
	mBot = button;
	y = glutGet(GLUT_WINDOW_HEIGHT) - y;
	mCoord = { x,y };

	// Save the left button state
	if (button == GLUT_LEFT_BUTTON)
	{
		leftMouseButtonDown = (state == GLUT_DOWN);
	}
	
	else if (button == GLUT_RIGHT_BUTTON)
	{
		rightMouseButtonDown = (state == GLUT_DOWN);
	}
}
void IG1App::motion(int x, int y)
{
	glm::dvec2 mp = mCoord - glm::dvec2(x, y);
	mCoord = { x,y };

	int mdf = glutGetModifiers();
	// click izquierdo mantenido
	if (leftMouseButtonDown) { 
		if (mdf == 0) {
			mCamera->orbit(mp.x * 0.25, mp.y + 0.25); // rotate move: orbit
		}
		else if (mdf > 0 && mdf == GLUT_ACTIVE_CTRL) {
			int k = glutGet(GLUT_WINDOW_HEIGHT) - mp.y;
			mCamera->orbitBalloon(mp.x * 0.25, k + 0.05); // rotate move: orbit en forma de globo, no funciona bien, no me ha dado tiempo (extra)
		}		
	}
	// click derecho mantenido
	if (rightMouseButtonDown) { 
		// UP / DOWN
		if (mp.y != 0) { 
			if (mdf == 0) {
				mCamera->moveUD(mp.y); // move: up / down
			}
			else if (mdf > 0 && mdf == GLUT_ACTIVE_CTRL) {
				mCamera->lookUD(mp.y); // look: up / down (extra)
			}
		}
		// LEFT / RIGHT
		if (mp.x != 0) { 
			if (mdf == 0) {
				mCamera->moveLR(mp.x); // move: left / right
			}
			else if (mdf > 0 && mdf == GLUT_ACTIVE_CTRL) {
				mCamera->lookLR(mp.x); // look: left / right (extra)
			}
		}
	}
	glutPostRedisplay();
}
void IG1App::mouseWheel(int n, int d, int x, int y)
{
	int mdf = glutGetModifiers();
	if (mdf == 0) {
		mCamera->moveFB(d * 10.0); // zoom: farward / backward
	}
	else if (mdf > 0 && mdf == GLUT_ACTIVE_CTRL) {
		mCamera->setScale(d * -0.05); // set scale
	}
	glutPostRedisplay();
}