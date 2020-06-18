#include "CommonBullet.h"



CommonBullet::CommonBullet(Vector2f position, double rotation, int jakdlugo, bool isWallPenetrating)
{
	if (isWallPenetrating == true)
		loadFromFile("grafika/CommonBullet.png");
	else
		loadFromFile("grafika/maly.png");
	setTexture();
	setPosition(position);
	setRotation(rotation);
	setOrigin(4, 4);
	this->isWallPenetrating = isWallPenetrating;
	o.push_back({ 4, 0 });
	o.push_back({ 0, 4 });
	o.push_back({ -4, 0 });
	o.push_back({ 0, -4 });
	for (int i = 0; i < 4; i++)
		p.push_back({ 0,0 });
	speed = 4;
	livetime = jakdlugo;
}


CommonBullet::CommonBullet()
{
}

bool CommonBullet::decrement()
{
	if (--livetime == 0)
		return true;
	return false;
}


CommonBullet::~CommonBullet()
{
}
