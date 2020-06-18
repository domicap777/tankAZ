#include "Wall.h"

Wall::Wall(int x, int y, int r)
{
	loadFromFile("grafika/sciana.png");
	setTexture();
	setRotation(r);
	setPosition(x, y);
	o.push_back({ 0, 0 });
	o.push_back({ 99, 0 });
	o.push_back({ 99, 4 });
	o.push_back({ 0, 4 });
	p.push_back({ 0, 0 });
	p.push_back({ 99, 0 });
	p.push_back({ 99, 4 });
	p.push_back({ 0, 4 });
}

