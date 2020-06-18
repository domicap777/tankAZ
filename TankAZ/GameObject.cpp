
#define _USE_MATH_DEFINES
#include "GameObject.h"
#include <cmath>



void GameObject::countHitBox()
{
	for (int i = 0; i < o.size(); i++)
	{
		p[i].x = (o[i].x * cos((getRotation() / 180)*M_PI) - (o[i].y * sin((getRotation() / 180)*M_PI)) + getPosition().x);
		p[i].y = (o[i].x * sin((getRotation() / 180)*M_PI) + (o[i].y * cos((getRotation() / 180)*M_PI)) + getPosition().y);
	}
}
Vector2f GameObject::getPosition()
{
	return sprite.getPosition();
}
double GameObject::getRotation()
{
	return sprite.getRotation();
}


void GameObject::draw(RenderWindow * window)
{
	window->draw(sprite);
}

void GameObject::loadFromFile(string plik)
{
	texture.loadFromFile(plik);
}

void GameObject::setTexture()
{
	sprite.setTexture(texture);
}

void GameObject::setPosition(double x, double y)
{
	sprite.setPosition(x, y);
}

void GameObject::setPosition(Vector2f p)
{
	sprite.setPosition(p);
}


void GameObject::setRotation(double r)
{
	sprite.setRotation(r);
}

void GameObject::setOrigin(int x, int y)
{
	sprite.setOrigin(x, y);
}

void GameObject::move(double x, double y)
{
	sprite.move(x, y);
}

double GameObject::getRealWidth()
{
	return sprite.getTextureRect().width*sprite.getScale().x;
}

void GameObject::rotate(double r)
{
	sprite.rotate(r);
}

double GameObject::getRealHeight()
{
	return sprite.getTextureRect().height*sprite.getScale().y;
}





