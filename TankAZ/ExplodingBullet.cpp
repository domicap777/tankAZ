#include "ExplodingBullet.h"


void ExplodingBullet::detonate()
{
	sender->detonate();
}

ExplodingBullet::ExplodingBullet(Tank* tanks)
{
	loadFromFile("grafika/bomba.png");
	setTexture();
	setPosition(tanks->getPosition());
	setRotation(tanks->getRotation());
	sender = tanks;
	setOrigin(4, 4);
	o.push_back({ 4, 0 });
	o.push_back({ 0, 4 });
	o.push_back({ -4, 0 });
	o.push_back({ 0, -4 });
	for (int i = 0; i < 4; i++)
		p.push_back({ 0,0 });
	speed = 4;
	livetime = 1000;
}

bool ExplodingBullet::decrement()
{
	if (--livetime == 0)
		return true;
	return false;
}


ExplodingBullet::~ExplodingBullet()
{
}
