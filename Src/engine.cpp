#include "engine.h"



Engine::Engine() {
	playersFigure = 0;
	initializeRemarks();
	initializeFlags();
}


void Engine::initializeGL() {
	glfwInitialize();
	glewInitialize();
	eventsInitialize();
}

void Engine::start() {

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		screenHeight++;
		screenWidth++;

		if (getFlagValue("nudgeBackstage")) {
			changeFlag("nudgeBackstage", false);
			backstage->nudge();
		}
		if (getFlagValue("redrawAll"))
		{

			changeFlag("redrawAll", false);
			glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			draw(backstage);
			draw(corridor);
			draw(playersFigure);

			glfwSwapBuffers(window);
		}
	}
	glfwDestroyWindow(window);



}

void Engine::draw(Entity* obj) {
	if (obj != nullptr)
		obj->outline();

}

void Engine::updatePlayerFigure(Entity* objPtr) {
	playersFigure = objPtr;
}
void Engine::updateBackstage(Entity* objPtr) {
	backstage = objPtr;
}



void Engine::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {


	if (action == GLFW_PRESS)
		playersFigure->moveTo(key);
	if (action == GLFW_REPEAT)
		playersFigure->moveTo(key);

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void Engine::glfwInitialize() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	//const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	//screenWidth = mode->width;
	//screenHeight = mode->height;
	windowInitialize(&screenHeight, &screenWidth);
	if (window == GLEW_OK)std::cout << "widnow ok" << std::endl;
	glfwSetWindowUserPointer(window, this);
}

void Engine::glewInitialize() {
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		throw "Failed to initialize GLEW";
	}
}

void Engine::eventsInitialize() {
	auto lam = [](GLFWwindow* window, int key, int scancode, int action, int mode) {
		static_cast<Engine*>(glfwGetWindowUserPointer(window))->key_callback(window, key, scancode, action, mode);
	};
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
	glfwSetKeyCallback(window, lam);
}

void Engine::windowInitialize(int* h, int* w) {
	window = glfwCreateWindow(*w, *h, "Bomberman", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		throw "Failed to create window";
	}
	glfwMakeContextCurrent(window);
	glViewport(0, 0, *w, *h);
}

void Engine::initializeRemarks() {
	declareRemark("updPlayerFigure", [this](void* ptr) {
		this->updatePlayerFigure((Entity*)ptr);
	});
	declareRemark("updBackstage", [this](void* ptr) {
		this->updateBackstage((Entity*)ptr);
	});
	declareRemark("updCorridor", [this](void* ptr) {
		corridor = (Entity*)ptr;
	});
	declareRemark("startEngine", [this](void* ptr) {
		this->start();
	});
	declareRemark("initWindow", [this](void* ptr) {
		screenHeight = ((Point2D*)ptr)->getY();
		screenWidth = ((Point2D*)ptr)->getX();
		initializeGL();
	});
}
void Engine::initializeFlags() {
	declareFlag("redrawAll", true);
	declareFlag("immobilized");
	declareFlag("nudgeBackstage");
	declareFlag("drop");
	declareFlag("size");
}

