#pragma once
#include "GameObject.h"
class Boost :
	public GameObject
{
	int kindOfBust;
public:
	Boost(Vector2f);
	~Boost();
	int getKindOfBust();
};

