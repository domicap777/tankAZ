#include "Bullet.h"



int Bullet::getRadius()
{
	return radius;
}

bool Bullet::getIsCollision()
{
	return isWallPenetrating;
}


Bullet* Bullet::move(vector<Wall*>*walls)
{
	GameObject::move(speed * sin((getRotation() / 180)*M_PI), speed * -cos((getRotation() / 180)*M_PI));
	countHitBox();
	if (getIsCollision())
	{
		int tmp = checkCollisions(walls);
		if (tmp != 0)
		{
			if (tmp == 3)
				setRotation(-getRotation());
			else if (tmp == 2)
				setRotation(180 - getRotation());
			else
				setRotation(180 + getRotation());
		}
	}
	if (decrement())
		return this;
	else return NULL;

}

int Bullet::checkCollisions(vector<Wall*>*walls)
{
	for (int w = 0; w < walls->size(); w++)
	{
		int tmp = checkCollision(walls->at(w));
		if (tmp != 0)
			return tmp;
	}
	return 0;
}


int Bullet::checkCollision(Wall*wall)
{
	double nearestX;
	double nearestY;
	int x = 0, y = 0;
	int feedback  = 0;
	if (wall->getRotation() == 0)
	{
		nearestX = findNearest(this->getPosition().x, wall->getPosition().x, wall->getRealWidth(), x);
		nearestY = findNearest(this->getPosition().y, wall->getPosition().y, wall->getRealHeight(), y);
	}
	else
	{
		nearestX = findNearest(this->getPosition().x, wall->getPosition().x - wall->getRealHeight(), wall->getRealHeight(), x);
		nearestY = findNearest(this->getPosition().y, wall->getPosition().y, wall->getRealWidth(), y);
	}
	double distanceX = this->getPosition().x - nearestX;
	double distanceY = this->getPosition().y - nearestY;
	double totalDistance = (distanceX * distanceX) + (distanceY * distanceY);
	if (totalDistance < (this->getRadius() * this->getRadius()))
	{
		feedback  = 1 + x + 2 * y;
		if (feedback  != 1)
			return feedback ;
	}

	else return feedback ;
}

double Bullet::findNearest(double a, double b, double c, int& d)
{
	if (a < b)
		return b;
	if (a > b + c)
		return b + c;
	else
	{
		d = 1;
		return a;
	}
}

