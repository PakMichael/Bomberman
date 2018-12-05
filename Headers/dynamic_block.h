#ifndef DYNAMIC_BLOCK_H
#define DYNAMIC_BLOCK_H


#include "subordinate.h"
#include "block.h"
#include "primitive.h"
#include <chrono>
#include <thread>

typedef std::chrono::high_resolution_clock clock_;
class TickingBomb {



public:
	Rectangle* bomb_;
	std::chrono::steady_clock::time_point *timePlanted_;
	TickingBomb(Rectangle* bomb) :bomb_(bomb) {
		timePlanted_ = &clock_::now();

	}
	~TickingBomb() {
		delete bomb_;
		delete timePlanted_;
	}
};


class DynamicBlock : public Block {
	std::vector<TickingBomb*> bombsPlanted;
	bool threadActive = false;
public:
	std::thread* t = NULL;
	DynamicBlock(Point2D* displacements, char* texturePath);


	void  placeBombAt(Point2D * pos, Point2D* dimensions);
	//void nudge() override;
private:
	void timeKeeper();

};


#endif