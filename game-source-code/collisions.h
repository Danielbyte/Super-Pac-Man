#ifndef COLLISIONS_H
#define COLLISIONS_H
#include <memory>

class Collisions
{
public:
	Collisions();
	bool checkCollision(float obj1Xposition, float obj1Yposition, float obj1Width, float obj1Length,
		float obj2Xposition,float obj2Yposition, float obj2Width, float obj2Length);

private:
	bool checkHorizontalCollisions(float obj1Right, float obj1Left, float obj2Right, float obj2Left);
	bool checkVerticalCollisions(float obj1Top, float obj1Bottom, float obj2Top, float obj2Bottom);
};
#endif
