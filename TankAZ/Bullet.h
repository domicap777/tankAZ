#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include "Wall.h"
#include "GameObject.h"


class Bullet :
	public GameObject
{
protected:
	int radius = 4;
	bool isWallPenetrating = true;
	int	speed;
	int livetime;
public:
	int getRadius();
	bool getIsCollision();
	Bullet* move(vector<Wall*>*);
	int checkCollisions(vector<Wall*>*);
	virtual bool decrement() = 0;
	int checkCollision(Wall *);
	double findNearest(double, double, double, int&);

};

