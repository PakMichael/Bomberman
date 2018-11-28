#include "wall.h"

Wall::Wall(float x, float y, float width, float height)
{
	rectangle = new Rectangle(x, y, width, height);
	mX = x;
	mY = y;
	outline();
	constructCarcass();
}

void Wall::constructCarcass()
{
	std::vector<Primitive*> carcass;
	carcass.push_back(rectangle);

	assemble(carcass, 4);
}

bool Wall::intersects(Rectangle* rec) {
	return *rectangle == *rec;
}
