#pragma once
#define _USE_MATH_DEFINES

#include <cmath>
#include "Bullet.h"
#include "CommonBullet.h"
#include "ExplodingBullet.h"
#include "GameObject.h"
#include "CollisionDetector.h"
#include "GameController.h"

class ExplodingBullet;


class Tank :public GameObject
{

	int bulletType;
	int cooldown;
	int rifleCooldown;
	vector<vector<int>>* fields;
	vector < Bullet*  > *bullets;
	ExplodingBullet * explodingBullet = NULL;
public:
	CollisionDetector * algorithm = new CollisionDetector;
	ExplodingBullet * getExplodingBullet();
	void stop();
	int shootKey;
	sf::Keyboard::Key controlKeys[4];
	void detonate();
	void decrement();
	int getCooldown();
	void move(int);
	void rotate(int);
	Tank(Vector2f, vector<vector<int>>*, vector < Bullet*  >*, int);
	void shot();
	int getBulletType();
	void setBulletType(int);
};