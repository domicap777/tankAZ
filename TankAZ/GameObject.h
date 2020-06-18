#pragma once
#include <SFML/Graphics.hpp>
#include<string.h>
#include <iostream>


using namespace sf;
using namespace std;

class GameObject
{
protected:

	Texture texture;
public:
	void countHitBox();
	Vector2f getPosition();
	double getRotation();
	std::vector<Vector2f> p; ///zmana nazwy
	std::vector<Vector2f> o;
	Sprite sprite;
	void draw(RenderWindow *window);
	void loadFromFile(string);
	void setTexture();
	void setPosition(double, double);
	void setPosition(Vector2f);
	void setRotation(double);
	void setOrigin(int, int);
	void move(double, double);
	double getRealWidth();
	void rotate(double);
	double getRealHeight();

};
