#include "block.h"




void Block::constructCarcass()
{
	assemble(bricks, 4);
}

Block::Block(char* texPath)
{
	mX = mY = 0;
	texturePath = texPath;
	//texturePaths.push_back(texPath);
}

bool Block::intersects(Rectangle* rec) {
	//for (Primitive* r : bricks) {
	//	if (*static_cast<Rectangle*>(r) == *rec)return true;
	//}

	float xL = rec->getX();
	float xR = xL + rec->getWidth();
	float yU = rec->getY();
	float yD = yU - rec->getHeight();


	for (Primitive* r : bricks) {

		Rectangle* vari = static_cast<Rectangle*>(r);

		float BxL = vari->getX()+ vari->getWidth()*0.25;
		float BxR = BxL + vari->getWidth()*0.5;
		float ByU = vari->getY()- vari->getHeight()*0.25;
		float ByD = ByU -vari->getHeight()*0.5;
 
		if (
			xL < BxR &&
			xR > BxL &&
			yU > ByD &&
			yD < ByU
		) return true;


	}


	return  false;
}

void Block::addBrick(float posX, float posY, float width, float height)
{
	bricks.push_back(new Rectangle(posX, posY, width, height));
}
