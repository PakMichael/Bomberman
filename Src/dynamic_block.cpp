#include "dynamic_block.h"





DynamicBlock::DynamicBlock(Point2D * displacements, char * texturePath) :Block(displacements, texturePath) {
	textureIndexOffset = 0;


}


void DynamicBlock::timeKeeper() {
	threadActive = true;
	//while (bombsPlanted.size() > 0) {
	//	for (TickingBomb* bomb : bombsPlanted) {
	//		if (clock_::now() - *bomb->timePlanted_ > std::chrono::duration<double>(3)) {
	//			removeBrick(bomb->bomb_);
	//			bombsPlanted.erase(find(bombsPlanted.begin(), bombsPlanted.end(), bomb));
	//			//makeRemark("bombExploded", 0);
	//		}
	//	}
	//}


	std::chrono::time_point<clock_> pause = clock_::now();
	std::chrono::time_point<clock_> texPause = clock_::now();
	while (clock_::now() - pause < std::chrono::duration<double>(10.0f)) {
		if (clock_::now() - texPause > std::chrono::duration<double>(0.15f)) {
			++indexTexture;
			if (indexTexture >= 3)indexTexture = 0;
			texPause = clock_::now();
			makeRemark("bombRedraw", 0);
		}
		//}
		//while (clock_::now() - pause < std::chrono::duration<double>(3.0f)) {}; //0.15
		//for (TickingBomb* bomb : bombsPlanted) {

		//	removeBrick(bomb->bomb_);
		//	auto it = std::find(std::begin(bombsPlanted), std::end(bombsPlanted), bomb);
		//	if (it != std::end(bombsPlanted))
		//		bombsPlanted.erase(it);
		//	makeRemark("bombExploded", 0);
		//}


	}
	threadActive = false;
}



void DynamicBlock::placeBombAt(Point2D * pos, Point2D* dimensions)
{

	TickingBomb* temp = new TickingBomb(new Rectangle(pos->getX(), pos->getY(), dimensions->getX(), dimensions->getY()));
	bombsPlanted.push_back(temp);
	addBrick(temp->bomb_);
	if (t == NULL) {
		t = new std::thread(&DynamicBlock::timeKeeper, this);
	}
	else {
		if (!threadActive) {
			t = new std::thread(&DynamicBlock::timeKeeper, this);
		}
	}
	constructCarcass();
}
//
//void DynamicBlock::nudge()
//{
//	constructCarcass();
//}
