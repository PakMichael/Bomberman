#ifndef GAME_H
#define GAME_H

#include "supervisor.h"
#include "subordinate.h"
#include "figure.h"
#include "backstage.h"
#include <vector>
#include <string>
#include <thread>


class Game : public Supervisor, public Subordinate {
	Figure* figureFlying;
	
	std::thread t;


public:
	Backstage* gameField;
private:
	int windowHeight = 650;
	int windowWidth = 650;
	float relativeCellSizeX = 0.1f;
	float relativeCellSizeY = 0.1f;
public:
	void init();
	void createFigure();
	void induceMovement();



private:
	void initializeRemarks();
	void initializeGameVars();






};






#endif 