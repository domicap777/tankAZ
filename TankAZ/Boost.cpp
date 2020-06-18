#include "Boost.h"




Boost::Boost(Vector2f position)
{
	kindOfBust = rand() % 2 + 1;
	if (kindOfBust == 1)
		loadFromFile("grafika/karabin_zbierajka.png");
	if (kindOfBust == 2)
		loadFromFile("grafika/bomba_zbierajka.png");
	setTexture();
	setOrigin(10, 10);
	setPosition(position);
	o.push_back({ 10, 10 });
	o.push_back({ -10, 10 });
	o.push_back({ -10,-10 });
	o.push_back({ 10, -10 });
	for (int i = 0; i < 4; i++)
		p.push_back({ 0,0 });
	this->countHitBox();
}

Boost::~Boost()
{
}

int Boost::getKindOfBust()
{
	return kindOfBust;
}
