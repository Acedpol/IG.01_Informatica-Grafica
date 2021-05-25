#pragma once
#include <gl\GL.h>
class Light { // Abstract class
protected:
	static GLuint cont; // Atributo para poder generar un nuevo id cada vez
	GLuint id = GL_LIGHT0 + GL_MAX_LIGHTS; // Primer id no válido
	// Atributos lumínicos y geométrico de la fuente de luz
	glm::fvec4 ambient = { 0.1, 0.1, 0.1, 1 };
	glm::fvec4 diffuse = { 0.5, 0.5, 0.5, 1 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
	glm::fvec4 posDir = { 0, 0, 1, 0 };
	// Añade setter’s para cambiar el valor de los atributos lumínicos
public:
	Light();
	virtual ~Light() { disable(); }
	void uploadL();
	// Método abstracto
	virtual void upload(glm::dmat4 const& modelViewMat) const = 0;
	…
};
GLuint Light::cont = 0;
Light() {
	if (cont < GL_MAX_LIGHTS) {
		id = GL_LIGHT0 + cont;
		++cont;
		glEnable(id);
	}
};
void Light::uploadL() {
	// Transfiere las características de la luz a la GPU
	glLightfv(id, GL_AMBIENT, value_ptr(ambient));
	glLightfv(id, GL_DIFFUSE, value_ptr(diffuse));
	glLightfv(id, GL_SPECULAR, value_ptr(specular));
}
void disable() { if (id < GL_LIGHT0 + GL_MAX_LIGHTS) glDisable(id); };
void enable() { if (id < GL_LIGHT0 + GL_MAX_LIGHTS) glEnable(id); };
void setAmb(glm::fvec4 amb) { ambient = amb; upLoadL(); }; //setDiff(), setSpec()

class DirLight : public Light {
public:
	virtual void upload(glm::dmat4 const& modelViewMat) const;
	void setPosDir(glm::fvec3 dir);
};
donde:
void DirLight::upload(glm::dmat4 const& modelViewMat) const {
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat));
	glLightfv(id, GL_POSITION, value_ptr(posDir));
	uploadL();
}
// Ojo al 0.0 que determina que la luz sea remota
void DirLight::setPosDir(glm::fvec3 dir); {
	posDir = glm::fvec4(dir, 0.0);
}

class PosLight : public Light {
protected:
	// Factores de atenuación 
	GLfloat kc = 1, kl = 0, kq = 0;
public:
	virtual void upload(glm::dmat4 const& modelViewMat) const;
	void setPosDir(glm::fvec3 dir);
	void setAtte(GLfloat kc, GLfloat kl, GLfloat kc);
};

void PosLight::upload(glm::dmat4 const& modelViewMat) const {
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat));
	glLightfv(id, GL_POSITION, value_ptr(posDir));
	glLightf(id, GL_CONSTANT_ATTENUATION, kc);
	glLightf(id, GL_LINEAR_ATTENUATION, kl);
	glLightf(id, GL_QUADRATIC_ATTENUATION, kq);
	uploadL();
}
// Ojo al 1.0 que determina que la luz sea local
void PosLight::setPosDir(glm::fvec3 dir); {
	posDir = glm::fvec4(dir, 1.0);
}

class SpotLight : public PosLight {
protected:
	// Atributos del foco
	glm::fvec4 direction = { 0, 0, -1, 0 };
	GLfloat cutoff = 180;
	GLfloat exp = 0;
public:
	SpotLight(glm::fvec3 pos = { 0, 0, 0 })
		: PosLight() {
		posDir = glm::fvec4(pos, 1.0);
	};
	virtual void upload(glm::dmat4 const& modelViewMat) const;
	void setSpot(glm::fvec3 dir, GLfloat cf, GLfloat e);
};

void SpotLight::upload(glm::dmat4 const& modelViewMat) const {
	PosLight::upload(modelViewMat);
	glLightfv(id, GL_SPOT_DIRECTION, value_ptr(direction));
	glLightf(id, GL_SPOT_CUTOFF, cutoff);
	glLightf(id, GL_SPOT_EXPONENT, exp);
}
// Ojo al 0.0: la dirección de emisión del foco es vector
void setSpot(glm::fvec3 dir, GLfloat cf, GLfloat e) {
	direction = glm::fvec4(dir, 0.0);
	cutoff = cf;
	exp = e;
}

