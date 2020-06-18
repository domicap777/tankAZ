#pragma once
#include "Bullet.h"
#include "Tank.h"

class Tank;

class ExplodingBullet :
	public Bullet
{
	Tank * sender;
public:
	void detonate();
	ExplodingBullet(Tank *);
	bool decrement();
	~ExplodingBullet();
};

