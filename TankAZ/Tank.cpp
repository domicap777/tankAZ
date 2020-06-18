#include "Tank.h"




ExplodingBullet * Tank::getExplodingBullet()
{
	return explodingBullet;
}

void Tank::stop()
{
	rifleCooldown = 0;
	if (bulletType == 1)
		bulletType = 0;
}



void Tank::detonate()
{
	bullets->erase(find(bullets->begin(), bullets->end(), this->getExplodingBullet()));
	for (int i = 0; i < 20; i++)
		bullets->push_back(new CommonBullet(explodingBullet->getPosition(), rand() % 360, 300, false));
	delete explodingBullet;
	bulletType = 0;
	explodingBullet = NULL;
}



void Tank::decrement()
{
	if (cooldown > 0)
		cooldown--;


	if (rifleCooldown > 0)
	{
		if (rifleCooldown == 1)
			stop();
		if (rifleCooldown % 5 == 0)
		{
			Bullet* newBullet = new CommonBullet(getPosition(), getRotation() + rand() % 10 - 5, 400, true);
			bullets->push_back(newBullet);
			for (int i = 0; i < 8; i++)
				newBullet->move(&(GameController::getInstance()->walls));
		}
		rifleCooldown--;
	}
}

int Tank::getCooldown()
{
	return cooldown;
}


void Tank::move(int a)
{
	(*fields)[getPosition().x / 100][getPosition().y / 95]--;
	GameObject::move(a* sin((getRotation() / 180)*M_PI), a* -cos((getRotation() / 180)*M_PI));
	(*fields)[getPosition().x / 100][getPosition().y / 95]++;
	this->countHitBox();
}

void Tank::rotate(int a)
{
	GameObject::rotate(a);
	this->countHitBox();
}


Tank::Tank(Vector2f position, vector<vector<int>>* a, vector<Bullet*>*pociskii, int i)
{
	if (i == 0)
	{
		loadFromFile("grafika/tanks.png");
		shootKey = Keyboard::M;
		controlKeys[0] = (Keyboard::Key::Up);
		controlKeys[1] = (Keyboard::Key::Down);
		controlKeys[2] = (Keyboard::Key::Left);
		controlKeys[3] = (Keyboard::Key::Right);
	}
	else
	{
		loadFromFile("grafika/az2.png");
		shootKey = Keyboard::Q;
		controlKeys[0] = (Keyboard::Key::E);
		controlKeys[1] = (Keyboard::Key::D);
		controlKeys[2] = (Keyboard::Key::S);
		controlKeys[3] = (Keyboard::Key::F);
	}

	o.push_back({ -15, 24 });
	o.push_back({ -15, -16 });
	o.push_back({ -2, -16 });
	o.push_back({ -2, -25 });
	o.push_back({ 1, -25 });
	o.push_back({ 1, -16 });
	o.push_back({ 14, -16 });
	o.push_back({ 14, 24 });
	for (int i = 0; i < 8; i++)
		p.push_back({ 0,0 });
	setTexture();
	setPosition(position);
	setRotation(rand() % 360);
	setOrigin(15, 25);
	fields = a;
	bullets = pociskii;
	this->countHitBox();
}

void Tank::shot()
{
	Bullet* newBullet = NULL;
	if (bulletType == 0)
	{
		newBullet = new CommonBullet(getPosition(), getRotation(), 1000, true);
		bullets->push_back(newBullet);
		cooldown = 1000;
	}
	if (bulletType == 1)
		if (rifleCooldown == 0)
			rifleCooldown = 40;
	if (bulletType == 2)
	{
		newBullet = new ExplodingBullet(this);
		bullets->push_back(newBullet);
		explodingBullet = (ExplodingBullet*)newBullet;
	}
	if (newBullet != NULL)
		for (int i = 0; i < 8; i++)
			newBullet->move(&(GameController::getInstance()->walls));
}

int Tank::getBulletType()
{
	return bulletType;
}

void Tank::setBulletType(int i)
{
	bulletType = i;
}
