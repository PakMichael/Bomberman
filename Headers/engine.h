#ifndef ENGINE_H
#define ENGINE_H


#include "glew/glew.h"
#include "GLFW/glfw3.h"
#include "entity.h"
#include <supervisor.h>
#include <string>
#include <vector>


class Engine : public Supervisor{
	Entity* backstage;
	Entity* playersFigure;
	GLFWwindow* window;
	int screenHeight, screenWidth;


public:
	Engine();
	void start();


private:
	void updatePlayerFigure(Entity* objPtr);
	void updateBackstage(Entity* objPtr);
	void draw(Entity* obj);
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	void glfwInitialize();
	void glewInitialize();
	void eventsInitialize();
	void windowInitialize(int* h, int* w);
	void initializeGL();
	void initializeRemarks();
	void initializeFlags();
};

#endif