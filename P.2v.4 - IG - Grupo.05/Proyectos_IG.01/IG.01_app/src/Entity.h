//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include "Light.h"



//-------------------------------------------------------------------------

class Abs_Entity  // abstract class
{
public:
	Abs_Entity(): mModelMat(1.0), mColor(1) {};  // 4x4 identity matrix
	virtual ~Abs_Entity() {};

	Abs_Entity(const Abs_Entity& e) = delete;  // no copy constructor
	Abs_Entity& operator=(const Abs_Entity& e) = delete;  // no copy assignment

	virtual void render(glm::dmat4 const& modelViewMat) const = 0;  // abstract method
	
	// modeling matrix
	glm::dmat4 const& modelMat() const { return mModelMat; };
	void setModelMat(glm::dmat4 const& aMat) { mModelMat = aMat; };
	void setColor(glm::dvec4 const& color) { mColor = color; };
	void setTexture(Texture* tex) { mTexture = tex; };
	void setTexture2(Texture* tex) { mTexture2 = tex; };	
	virtual void update() {};

	GLuint alphaTex() { 
		if (mTexture != nullptr) return mTexture->alpha();
		else return false;
	};
protected:
	bool renderTy_; // false -> lines; true -> fill
	Texture* mTexture = nullptr;
	Texture* mTexture2 = nullptr;
	Mesh* mMesh = nullptr;		// the mesh
	glm::dmat4 mModelMat;		// modeling matrix
	glm::dvec4 mColor;			// mesh color
	// transfers modelViewMat to the GPU
	virtual void upload(glm::dmat4 const& mModelViewMat) const; 
};

//-------------------------------------------------------------------------

class EjesRGB : public Abs_Entity 
{
public:
	explicit EjesRGB(GLdouble l);
	~EjesRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class Poligono : public Abs_Entity
{
public:
	explicit Poligono(GLdouble rd, GLuint numL, glm::dvec4 const& color);
	~Poligono();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------
class Sierpinski : public Abs_Entity
{
public:
	explicit Sierpinski(GLdouble rd, GLuint numP, glm::dvec4 const& color);
	~Sierpinski();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class TrianguloRGB : public Abs_Entity
{
public:
	explicit TrianguloRGB(GLdouble rd);
	~TrianguloRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
private:
	double rotAngle=0, transAngle=0;

};

//-------------------------------------------------------------------------

class RectanguloRGB : public Abs_Entity
{
public:
	explicit RectanguloRGB(GLdouble w, GLdouble h);
	~RectanguloRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	
};

//-------------------------------------------------------------------------


class Estrella3D : public Abs_Entity
{
public:
	explicit Estrella3D(GLdouble re, GLuint np, GLdouble h);
	~Estrella3D();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
private:
	double rotAngleY=0, rotAngleZ=0;
};

//-------------------------------------------------------------------------

class Caja : public Abs_Entity
{
public:
	explicit Caja(GLdouble ld);
	~Caja();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class Suelo : public Abs_Entity
{
public:
	explicit Suelo(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
	~Suelo();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class Image : public Abs_Entity
{
public:
	explicit Image(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
	~Image();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};

//-------------------------------------------------------------------------

class Celda : public Abs_Entity
{
public:
	explicit Celda(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
	~Celda();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class QuadricEntity : public Abs_Entity 
{
public:
	QuadricEntity();
	~QuadricEntity() { gluDeleteQuadric(q); };
protected:
	GLUquadricObj* q;
};

inline QuadricEntity::QuadricEntity() {
	q = gluNewQuadric();
}

//-------------------------------------------------------------------------

class Sphere : public QuadricEntity 
{ 
public:
	Sphere(GLdouble r); // r es el radio de la esfera 
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble r;
};

inline Sphere::Sphere(GLdouble rr) {
	r = rr;
}

//-------------------------------------------------------------------------

class Cylinder : public QuadricEntity
{
public:
	Cylinder(GLdouble rBase, GLdouble rTop, GLdouble height, GLint slices); // r es el radio de la esfera 
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble rBase;
	GLdouble rTop;
	GLdouble height;
	GLint slices;
};

inline Cylinder::Cylinder(GLdouble rrBase, GLdouble rrTop, GLdouble hheight, GLint sslices) {
	rBase = rrBase;
	rTop = rrTop;
	height = hheight;
	slices = sslices;
}

//-------------------------------------------------------------------------

class Disk : public QuadricEntity
{
public:
	Disk(GLdouble rInner, GLdouble rOutter, GLint slices); // r es el radio de la esfera 
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble rInner;
	GLdouble rOutter;
	GLint slices;
};

inline Disk::Disk(GLdouble rrInner, GLdouble rrOuter, GLint sslices) {
	rInner = rrInner;
	rOutter = rrOuter;
	slices = sslices;
}

//-------------------------------------------------------------------------

class PartialDisk : public QuadricEntity
{
public:
	PartialDisk(GLdouble rInner, GLdouble rOutter, GLint slices); // r es el radio de la esfera 
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble rInner;
	GLdouble rOutter;
	GLint slices;
};

inline PartialDisk::PartialDisk(GLdouble rrInner, GLdouble rrOuter, GLint sslices) {
	rInner = rrInner;
	rOutter = rrOuter;
	slices = sslices;
}

//-------------------------------------------------------------------------

class EntityWithIndexMesh : public Abs_Entity
{
public:
	EntityWithIndexMesh() : Abs_Entity() {};
	virtual ~EntityWithIndexMesh() {};

	IndexMesh* getIndexMesh() { return inMesh; };
	void setIndexMesh(IndexMesh* im) { inMesh = im; };
protected:
	IndexMesh* inMesh = nullptr;
};

//-------------------------------------------------------------------------

class AnilloCuadrado : public EntityWithIndexMesh
{
public:
	explicit AnilloCuadrado();
	~AnilloCuadrado();
	virtual void render(glm::dmat4 const& modelViewMat) const;	
};

//-------------------------------------------------------------------------

class Cubo : public EntityWithIndexMesh
{
public:
	explicit Cubo(GLdouble l);
	~Cubo();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class CompoundEntity: public Abs_Entity 
{
public:
	CompoundEntity() {};
	virtual ~CompoundEntity() {
		for (Light* li : lights)
		{
			delete li; li = nullptr;
		}
		lights.clear();
		for (Abs_Entity* el : gObjects)
		{
			delete el;  el = nullptr;
		}
		for (Abs_Entity* el : gBlendObjects)
		{
			delete el;  el = nullptr;
		}
		gBlendObjects.clear();
		gObjects.clear();
	};
	void addEntity(Abs_Entity* ae) {
		gObjects.push_back(ae);
	};
	void addBlendEntity(Abs_Entity* ae) {
		gBlendObjects.push_back(ae);
	};
	void render(glm::dmat4 const& modelViewMat) const;

	std::vector<Light*> getLights() { return lights; };

protected:
	std::vector<Abs_Entity*> gObjects;			// Entities (graphic objects) of the scene
	std::vector<Abs_Entity*> gBlendObjects;		// (graphic objects) with Blend apply
	std::vector<Light*> lights;
};

//-------------------------------------------------------------------------

class TIE : public CompoundEntity
{
private:
	SpotLight* light;
public:
	TIE(Texture* t, bool scale);
	virtual ~TIE() {};

	Light* getLight() { return light; };
	void setLight();

	void render(glm::dmat4 const& modelViewMat) const {
		CompoundEntity::render(modelViewMat);
		if (light != nullptr) {
			glm::dmat4 auxMat = modelViewMat * modelMat();
			light->upload(auxMat);
		}
	};	
};

//-------------------------------------------------------------------------

class familyTIE : public CompoundEntity
{
private:
	TIE* newTIE(Texture* t, int x, int y);
	//double rot_orbit;	// angulo respecto al planeta
	//double rot_squad;	// angulo del escuadron = direccion a la que se mueven
	bool s_orbit;
	bool s_turn;
public:
	familyTIE(Texture* t, bool mode);
	virtual ~familyTIE() {};

	virtual void update();
	void toggleOrbit() { s_orbit = !s_orbit; };
	void toggleTurn() { s_turn = !s_turn; };
	void orbit();
	void rota();
	/*void TIEsLightsOn(); 
	void TIEsLightsOff();
	void uploadLights();*/

};

//-------------------------------------------------------------------------

class Cono : public Abs_Entity
{
public:
	explicit Cono(GLdouble h, GLdouble r, GLuint n, bool fill);
	virtual ~Cono() { delete mMesh; mMesh = nullptr; };
	virtual void render(glm::dmat4 const& modelViewMat) const;	
};

//-------------------------------------------------------------------------

class EntityWithMaterial : public Abs_Entity {
public:
	EntityWithMaterial() : Abs_Entity() {};
	virtual ~EntityWithMaterial() {};
	virtual void render(glm::dmat4 const& modelViewMat) const;
	void setMaterial(Material* matl) { material = matl; };
protected:
	Material* material = nullptr;
};

//-------------------------------------------------------------------------

class Esfera : public EntityWithMaterial
{
public:
	explicit Esfera(GLdouble r, GLuint p, GLuint m, bool fill);
	virtual ~Esfera() {};
	virtual void render(glm::dmat4 const& modelViewMat) const;	
};

//-------------------------------------------------------------------------

class Grid : public Abs_Entity
{
public:
	explicit Grid(GLdouble lado, GLuint nDiv, bool fill, Texture* t = nullptr);
	virtual ~Grid() {};
	virtual void render(glm::dmat4 const& modelViewMat) const;	
};

//-------------------------------------------------------------------------

class GridCube : public CompoundEntity
{
public:
	explicit GridCube(GLdouble lado, GLuint nDiv, bool fill, GLuint scale, bool tex);
	virtual ~GridCube() {};
	//virtual void render(glm::dmat4 const& modelViewMat) const;
private:
	void addFloor(GLdouble lado, GLuint nDiv, bool fill, Texture* tex, GLuint height, double alphaZ);
	void addWall(GLdouble lado, GLuint nDiv, bool fill, Texture* tex, GLuint side);
};

//-------------------------------------------------------------------------




#endif //_H_Entities_H_