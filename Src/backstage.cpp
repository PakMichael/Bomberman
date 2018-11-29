#include "backstage.h"

float indx2Grid(int index, float cellSize, int offsetIndex = 0) {
	return index * cellSize + offsetIndex * cellSize;
}

Backstage::Backstage(float relativeCellSizeX, float relativeCellSizeY) {
	mapDisplacements = new Point2D(0,0);
	relativeCellWidth = relativeCellSizeX;
	relativeCellHeight = relativeCellSizeY;
	wall = new Block(mapDisplacements);
	wall->enhanceBrightness = true;
	corridor = new Block(mapDisplacements, "Textures/BackgroundTile.png");
	bombs = new DynamicBlock(mapDisplacements, "Textures/Bomb/Bomb_f01.png");
	bombs->addToTextures(new std::string("Textures/Bomb/Bomb_f02.png"));
	bombs->addToTextures(new std::string("Textures/Bomb/Bomb_f03.png"));
	//wall->addBrick(0, -0.5, relativeCellWidth, relativeCellHeight);
	//wall->addBrick(indx2Grid(2, relativeCellWidth), -0.5, relativeCellWidth, relativeCellHeight);
	//wall->addBrick(indx2Grid(4, relativeCellWidth), -0.5, relativeCellWidth, relativeCellHeight);
	//wall->addBrick(indx2Grid(6, relativeCellWidth), -0.5, relativeCellWidth, relativeCellHeight);

 //

	constructLabyrinth();
	constructWalls();
	wall->constructCarcass();
	corridor->constructCarcass();
	bombs->constructCarcass();

}



Block * Backstage::getWall()
{
	return wall;
}

Block * Backstage::getCorridor()
{
	return corridor;
}

DynamicBlock * Backstage::getBombs()
{
	return bombs;
}

void Backstage::displaceMap(Point2D * pos)
{
	*mapDisplacements = *pos;
}



void Backstage::constructLabyrinth()
{

	for (int a = 0; a < 20; ++a) {
		for (int b = 0; b < 20; ++b) {
			map[a][b] = false;
		}

	}
	g = new Graph();

	for (int a = 0; a < 20; ++a)
		for (int b = 0; b < 20; ++b) {
			g->createNode(a * 20 + b);
		}

	for (int a = 1; a < 20; ++a)
		for (int b = 1; b < 20; ++b) {
			g->connectTwo(a * 20 + b, a * 20 + b - 1);
			g->connectTwo(a * 20 + b, (a - 1) * 20 + b);
		}
	for (int a = 1; a < 20; ++a) {
		g->connectTwo(a * 20, (a - 1) * 20);
		g->connectTwo(a, a - 1);
	}
	DFS* dfs = new DFS();
	dfs->traverse(g, 105, 100);
	for (Node* nd : dfs->visited) {
		int indx = nd->getIndex();
		map[indx / 20][indx - (indx / 20) * 20] = true;
	}

	//for (int a = 0; a < 20; ++a) {
	//	for (int b = 0; b < 20; ++b) {
	//		std::cout << map[a][b] << ", ";
	//	}
	//	std::cout << "\n";
	//}



}

void Backstage::constructWalls()
{

	//for (int b = 0; b < 7; ++b) {
	//	int index = rand() % 20;
	//	for (int a = 0; a < 20; ++a) {
	//		map[a][index] = false;
	//		map[a][index] = false;
	//		map[index][a] = false;
	//		map[index][a] = false;
	//	}
//}

	for (int a = 0; a < 20; ++a) {
		map[a][0] = false;
		map[a][19] = false;
		map[0][a] = false;
		map[19][a] = false;
		//map[8][a] = true;
		//map[9][a] = true;
		//map[10][a] = true;
		//map[11][a] = true;
	}


	//for (int a = 0; a < 22; ++a) {
	//	wall->addBrick(indx2Grid(a, relativeCellWidth, -10), 11 * relativeCellHeight, relativeCellWidth, relativeCellHeight); // -------
	//	wall->addBrick(-11 * relativeCellWidth, indx2Grid(a, relativeCellHeight, -10), relativeCellWidth, relativeCellHeight);//|
	//	wall->addBrick(10 * relativeCellWidth, indx2Grid(a, relativeCellHeight, -10), relativeCellWidth, relativeCellHeight); //       |
	//	wall->addBrick(indx2Grid(a, relativeCellWidth, -10), -10 * relativeCellHeight, relativeCellWidth, relativeCellHeight);// _______ 
	//}

	for (int a = 0; a < 20; ++a) {
		for (int b = 0; b < 20; ++b) {
			if (!map[a][b]) {
				wall->addBrick(indx2Grid(b, relativeCellWidth, -10), indx2Grid(19 - a, relativeCellHeight, -9), relativeCellWidth, relativeCellHeight);
			}
			else {
				corridor->addBrick(indx2Grid(b, relativeCellWidth, -10), indx2Grid(19 - a, relativeCellHeight, -9), relativeCellWidth, relativeCellHeight);

			}

		}
	}

}



