#pragma once
#include "Bullet.h"
class CommonBullet :public Bullet
{
public:
	CommonBullet(Vector2f position, double rotation, int jakdlugo, bool isWallPenetrating);
	CommonBullet();
	bool decrement();
	~CommonBullet();
};

