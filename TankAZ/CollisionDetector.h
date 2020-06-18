#pragma once
#include "GameObject.h"
class CollisionDetector
{
public:
	CollisionDetector();
	~CollisionDetector();
	GameObject* checkCollision(GameObject*, GameObject*);
};

