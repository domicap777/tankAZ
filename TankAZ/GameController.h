#pragma once
#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
//#include <vld.h>
#include <algorithm> 
#include <iostream>
#include <windows.h>
#include <thread>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <vector>
#include "Tank.h"
#include "Bullet.h"
#include "Wall.h"
#include "GameObject.h"
#include "MapGenerator.h"
#include "Boost.h"


using namespace sf;
using namespace std;
class Tank;
class GameController
{
	const int amountPlayers = 2;
	int dx, dr;
	static GameController* instance;
	GameController();
	vector < Bullet*  > bullets;
	vector < Boost*  > boosts;
	RenderWindow window;
	Clock clock;
	double timer;
	const double delay = 0.015;
	const int  amountWall  = 8;
	vector <Tank*>tanks;
	vector <vector <int>> fields;
	Event event;
public:
	void freeMemory();
	vector <  Wall*  > walls;
	void checkInput();
	void moveBullets(Bullet*);
	void viewAll();
	Vector2f randField();
	int checkCollision(Tank *obiekt);
	static GameController* getInstance();
	void start();
	Boost * boostColision(Tank *obiekt);
	void bulletColision();
	void collecting(Tank*);
	void endGame(int);
	~GameController();
};