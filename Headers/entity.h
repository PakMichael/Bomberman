#ifndef ENTITY_H
#define ENTITY_H

#include "glew/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "primitive.h"
#include "shader.h"
#include <vector>
#include <stb_image.h>

class Entity {

protected:


	float mX, mY;
	float angle;
	float EPSILON;
	int indeciesCount;
	char* texturePath;


private:
	Shader* shader;
	GLuint VAO;
	GLuint texture;
public:
	bool enhanceBrightness=false;
	Entity();
	void outline();
	virtual void moveTo(int key) = 0;
	virtual void nudge() = 0;

protected:
	void Entity::assemble(std::vector<Primitive*> carcass, int points);
	void initializeShader();

private:
	void applyTransitions();
	void constructIndecies(GLuint* indc, int size);
	void setBuffers(GLfloat* vertecies, int vSize, GLuint* indecies, int iSize);
	void loadTexture(char* path);
};



#endif