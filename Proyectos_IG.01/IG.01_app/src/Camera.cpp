#include "Camera.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/matrix_access.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

Camera::Camera(Viewport* vp): mViewPort(vp), mViewMat(1.0), mProjMat(1.0),  
							  xRight(vp->width() / 2.0), xLeft(-xRight),
							  yTop(vp->height() / 2.0), yBot(-yTop)
{
    setPM();
}

//-------------------------------------------------------------------------

void Camera::uploadVM() const 
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(mViewMat)); // transfers view matrix to the GPU 
}

//-------------------------------------------------------------------------

void Camera::setVM() 
{
	mViewMat = lookAt(mEye, mLook, mUp);  // glm::lookAt defines the view matrix 
	setAxes();
}

//-------------------------------------------------------------------------

void Camera::set2D_front() 
{
	mEye = dvec3(0, 0, 400);
	mLook = dvec3(0, 0, 0);
	mUp = dvec3(0, 1, 0);
	setVM();
}

//-------------------------------------------------------------------------

void Camera::set3D() 
{
	mEye = dvec3(400, 400, 400);  
	mLook = dvec3(0, 10, 0);   
	mUp = dvec3(0, 1, 0);
	mAng = -45;
	mRadio = 500;
	mScaleFact = 1;
	setVM();
}

//-------------------------------------------------------------------------

void Camera::set2D_back()
{
	mEye = dvec3(0, 0, -500); // camera position
	mLook = dvec3(0, 0, 0);	// view direction
	mUp = dvec3(0, 1, 0); // vector 'normal' de la camara
	setVM();
}

void Camera::orbit(GLdouble ax)
{
	mAng += ax;
	mEye.x = mLook.x + cos(radians(mAng)) * mRadio;
	mEye.z = mLook.z - sin(radians(mAng)) * mRadio;
	setVM();
}

void Camera::orbit(GLdouble incAng, GLdouble incY)
{
	orbit(incAng);
	mEye.y += incY;
	setVM();
}

void Camera::orbitBalloon(GLdouble incAng, GLdouble incY)
{
	orbit(incAng);
	//mEye.y += (mLook.y - 10) - sin(radians(mAng)) * mRadio;
	setVM();
}

void Camera::changePrj()
{
	bOrto = !bOrto;
	setPM();
}

void Camera::setCenital()
{
	mEye = dvec3(0, 500, 0);
	mLook = dvec3(0, 0, 0);
	mUp = dvec3(0, 0, 1);
	mAng = 180;
	mRadio = 50;
	setVM();
}

//-------------------------------------------------------------------------

void Camera::setOrtogonal()
{
	set3D();
	bOrto = true;
	setPM();
}

void Camera::setPerspective()
{
	set3D();
	bOrto = false;
	setPM();
}

//-------------------------------------------------------------------------

//void Camera::pitch(GLdouble a) 
//{  
//	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(1.0, 0, 0));
//	// glm::rotate returns mViewMat * rotationMatrix
//}
////-------------------------------------------------------------------------
//
//void Camera::yaw(GLdouble a) 
//{
//	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(0, 1.0, 0));
//	// glm::rotate returns mViewMat * rotationMatrix
//}
////-------------------------------------------------------------------------
//
//void Camera::roll(GLdouble a) 
//{
//	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(0, 0, 1.0));
//	// glm::rotate returns mViewMat * rotationMatrix
//}

//--- Move Eye -------------------------------------------------------------

// zoom (out/in)
void Camera::moveFB(GLdouble cs) // mFront = eje N
{
	mEye += -mFront * cs; 
	setVM(); 
}

// eje horizontal
void Camera::moveLR(GLdouble cs) // mRight = eje U
{
	mEye += mRight * -cs; 
	mLook += mRight * -cs;
	setVM();
}

// eje vertical
void Camera::moveUD(GLdouble cs) // mUpward = eje V
{
	mEye += mUpward * cs; 
	mLook += mUpward * cs;
	setVM();
}

//--- Rotate Look -----------------------------------------------------------

void Camera::lookLR(GLdouble cs) // mRight = eje U
{
	mLook += mRight * -cs; 
	setVM();
}

void Camera::lookUD(GLdouble cs) // mUpward = eje V
{
	mLook += mUpward * cs; 
	setVM();
}

//--- Setters -----------------------------------------------------------

void Camera::setAxes()
{
	mRight = row(mViewMat, 0);
	mUpward = row(mViewMat, 1);
	mFront = -row(mViewMat, 2);
}

void Camera::setSize(GLdouble xw, GLdouble yh)
{
	xRight = xw / 2.0;
	xLeft = -xRight;
	yTop = yh / 2.0;
	yBot = -yTop;
	setPM();
}
//-------------------------------------------------------------------------

void Camera::setScale(GLdouble s) 
{
	mScaleFact -= s;
	if (mScaleFact < 0) mScaleFact = 0.01;
	setPM();
}

//-------------------------------------------------------------------------

void Camera::setPM() 
{
	if (bOrto) { //  if orthogonal projection
		mProjMat = ortho(xLeft*mScaleFact, xRight*mScaleFact, yBot*mScaleFact, yTop*mScaleFact, mNearVal, mFarVal);
		// glm::ortho defines the orthogonal projection matrix
	}
	else {
		mProjMat = frustum(xLeft*mScaleFact, xRight*mScaleFact, yBot*mScaleFact, yTop*mScaleFact, mNearVal*500, mFarVal*500);
		//mProjMat = frustum(xLeft, xRight, yBot, yTop, mNearVal, mFarVal);
	}
}

//-------------------------------------------------------------------------

void Camera::uploadPM() const 
{
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(value_ptr(mProjMat)); // transfers projection matrix to the GPU
	glMatrixMode(GL_MODELVIEW);
}

//-------------------------------------------------------------------------


