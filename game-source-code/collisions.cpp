#include "collisions.h"

Collisions::Collisions(){}

bool Collisions::checkCollision(float obj1Xposition, float obj1Yposition, float obj1Width, float obj1Length,
	float obj2Xposition, float obj2Yposition, float obj2Width, float obj2Length)
{
	float obj1Left = obj1Xposition - (obj1Length / 2.0f);
	float obj1Right = obj1Xposition + (obj1Length / 2.0f);
	float obj1Top = obj1Yposition - (obj1Width / 2.0f);
	float obj1Bottom = obj1Yposition + (obj1Width / 2.0f);

	float obj2Left = obj2Xposition - (obj2Length / 2.0f);
	float obj2Right = obj2Xposition + (obj2Length / 2.0f);
	float obj2Top = obj2Yposition - (obj2Width / 2.0f);
	float obj2Bottom = obj2Yposition + (obj2Width / 2.0f);

	auto horizontalCol = checkHorizontalCollisions(obj1Right, obj1Left, obj2Right, obj2Left);
	auto verticalCol = checkVerticalCollisions(obj1Top, obj1Bottom, obj2Top, obj2Bottom);

	if (horizontalCol && verticalCol)
		return true;

	return false;
}

bool Collisions::checkHorizontalCollisions(float obj1Right, float obj1Left, float obj2Right, float obj2Left)
{
	if (obj1Right < obj2Left || obj1Left > obj2Right)
		return false;

	return true;
}

bool Collisions::checkVerticalCollisions(float obj1Top, float obj1Bottom, float obj2Top, float obj2Bottom)
{
	if (obj1Bottom < obj2Top || obj1Top > obj2Bottom)
		return false;

	return true;
}