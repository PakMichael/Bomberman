#include "game.h"

using namespace std;
void Game::init() {
	initializeRemarks();
	initializeGameVars();
	makeRemark("initWindow", new Point2D(windowWidth, windowHeight));

	srand(std::time(0));

	gameField = new Backstage(relativeCellSizeX, relativeCellSizeY);
	gameField->addSupervisor(this);
	makeRemark("updBackstage", gameField->getWall());
	makeRemark("updCorridor", gameField->getCorridor());
	makeRemark("updBombs",gameField->getBombs());

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
 
	if (!gameField->getWall()->intersects(figureFlying->getRectangle())) {
		figureFlying->fulfilProphecy();
		gameField->displaceMap(new Point2D(figureFlying->vecX,figureFlying->vecY));
		makeRemark("displaceMap", 0);
		setFlag("redrawAll", true);

	}
	else {
		figureFlying->discardProphecy();

	}
 

}
void Game::initializeRemarks() {
	declareRemark("moveTo", [this](void* ptr)
	{
		induceMovement();
	});
	declareRemark("drop", [this](void* ptr)
	{
		setFlag("drop", true);
	});
	declareRemark("redraw", [this](void* ptr)
	{
		setFlag("redrawAll", true);
	});

	declareRemark("bombPlantedAt", [this](void* ptr)
	{
		gameField->getBombs()->placeBombAt((Point2D*)ptr,new Point2D(relativeCellSizeX, relativeCellSizeY));
		setFlag("redrawAll", true);
	});

	declareRemark("nudgeBombs", [this](void* ptr)
	{
//		makeRemark("nudgeBomb", 0);
		setFlag("redrawAll", true);
	});
	 
}
