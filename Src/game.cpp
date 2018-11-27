#include "game.h"

using namespace std;
void Game::init() {
	initializeRemarks();
	initializeGameVars();
	makeRemark("initWindow", new Point2D(windowWidth, windowHeight));

	srand(std::time(0));

	gameField = new Backstage(relativeCellSizeX, relativeCellSizeY);
	makeRemark("updBackstage", gameField);


	createFigure();

	makeRemark("startEngine", 0);
}

void Game::initializeGameVars() {
	relativeCellSizeX = 0.1f;
	relativeCellSizeY = 0.1f;

}
void Game::createFigure() {
	Figure* tmp = new Figure(0.0f, 0.0f, relativeCellSizeY, relativeCellSizeX);
	tmp->addSupervisor(this);
	figureFlying = tmp;
	makeRemark("updPlayerFigure", figureFlying);
	setFlag("redrawAll", true);

}



void Game::induceMovement() {

	switch (figureFlying->getDirection())
	{
	case ' ':
		figureFlying->rotate();
		break;
	case 'Q':
		figureFlying->boostDown();
		break;
	case 'A':
		figureFlying->moveLeft();
		break;
	case 'D':
		figureFlying->moveRight();
		break;
	case 'S':
		figureFlying->moveDown();
		break;
	case 'W':
		figureFlying->moveUp();
		break;
	case 'E':
		//figureFlying->setHitEarth();
		break;
	}
	if (!gameField->collisionOccured(figureFlying)) {
		figureFlying->fulfilProphecy();
		setFlag("redrawAll", true);
	}
	else {
		figureFlying->discardProphecy();

	}
	//if (!gameField.collisionOccured(figureFlying))
	//{
	//	figureFlying->fulfilProphecy();
	//	setFlag("redrawAll", true);
	//	/*	float tmpx;
	//		float tmpy;
	//		figureFlying->getCoordinates(tmpx, tmpy);
	//		std::cout << gameField->scaledPositionToIndex(tmpy) << std::endl;*/
	//	return;
	//}
	//else
	//{
	//	figureFlying->discardProphecy();
	//	/*gameField->consumeFigure(figureFlying);
	//	notify("immobilized");*/
	//}

}
void Game::initializeRemarks() {
	declareRemark("moveTo", [this](void* ptr)
	{
		induceMovement();
	});
	//declareRemark("immovable", [this](void* ptr)
	//{
	//	gameField.reconstructBackstage();
	//	createFigure();
	//});
	declareRemark("drop", [this](void* ptr)
	{
		changeFlag("drop", true);
	});
	declareRemark("redraw", [this](void* ptr)
	{
		changeFlag("redraw", true);
	});
}