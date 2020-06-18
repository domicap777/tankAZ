#include "GameController.h"

GameController* GameController::instance = 0;

GameController* GameController::getInstance()
{
	if (instance == 0)
	{
		instance = new GameController();
	}

	return instance;
}

void GameController::start()
{
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		if (timer > delay)
		{
			timer = 0;

			this->checkInput();

			if (boosts.size() < 7 && rand() % 500 == 0)
				boosts.push_back(new Boost(randField()));
			for (int i = 0; i < bullets.size(); i++)
				this->moveBullets(bullets[i]);
			this->viewAll();

			this->bulletColision();
		}
	}
}

Boost* GameController::boostColision(Tank* obiekt)
{
	for (int w = 0; w < boosts.size(); w++)//jak by by³o na for_each(walls.begin(), walls.end(), [&]() {}
	{

		Boost* tmp = (Boost*)obiekt->algorithm->checkCollision(obiekt, boosts[w]);
		if (tmp != NULL)

			return tmp;
	}
	return NULL;
}
void GameController::bulletColision()
{
	for (int i = 0; i < amountPlayers; i++)
	{
		for (int w = 0; w < bullets.size(); w++)//jak by by³o na for_each(walls.begin(), walls.end(), [&]() {}
		{
			GameObject* tmp = (tanks[i]->algorithm->checkCollision(tanks[i], bullets[w]));
			if (tmp != NULL)
			{
				endGame(i);
			}
		}
	}
}

void GameController::collecting(Tank* tanks)
{
	if (tanks->getBulletType() == 0)
	{
		Boost* zebrane = boostColision(tanks);
		if (zebrane != NULL)
		{
			tanks->setBulletType(zebrane->getKindOfBust());
			boosts.erase(find(boosts.begin(), boosts.end(), zebrane));
			delete zebrane;
		}
	}

}

void GameController::endGame(int i)
{
	window.clear(Color::White);
	Texture  texture;
	if (i == 0)
		texture.loadFromFile("grafika/zielony.png");
	else
		texture.loadFromFile("grafika/czerwony.png");
	Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(300, 300);
	window.draw(sprite);
	window.display();
	Sleep(2000);
	freeMemory();
	window.close();
}

GameController::GameController()
{
	window.create(VideoMode(805, 765), "tanks");//805
	srand(time(NULL));
	timer = 0;
	vector < vector < bool >  >  horizontal;
	vector < vector < bool >  >  vertical;
	MapGenerator a(amountWall , horizontal, vertical);
	for (int i = 0; i < amountWall ; i++)
		for (int j = 0; j < amountWall  + 1; j++)
			if (horizontal[i][j] == true)
			{
				walls.push_back({ new Wall(i * 100 + 5, j * 95, 0) });
				walls[walls.size() - 1]->countHitBox();
			}
	for (int i = 0; i < amountWall  + 1; i++)
		for (int j = 0; j < amountWall ; j++)
			if (vertical[i][j] == true)
			{
				walls.push_back({ new Wall(i * 100 + 5, j * 95, 90) });
				walls[walls.size() - 1]->countHitBox();
			}
	for (int i = 0; i < amountWall ; i++)
	{
		fields.push_back(vector<int>());
		for (int j = 0; j < amountWall ; j++)
			fields[i].push_back(0);
	}
	for (int i = 0; i < amountPlayers; i++)
		tanks.push_back(new Tank(randField(), &fields, &bullets, i));

}

void GameController::freeMemory()
{
	for (int i = 0; i < amountPlayers; i++)
		delete tanks[i];
	tanks.clear();
	for (int w = 0; w < walls.size(); w++)
		delete walls[w];
	walls.clear();
	for (int i = 0; i < bullets.size(); i++)
		delete bullets[i];
	bullets.clear();
	for (int i = 0; i < boosts.size(); i++)
		delete boosts[i];
	boosts.clear();

	for (int i = 0; i < fields.size(); i++)
		fields[i].clear();
	fields.clear();
}

void GameController::checkInput()
{
	while (window.pollEvent(event))
	{
		for (int i = 0; i < amountPlayers; i++)
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
				if (event.key.code == tanks[i]->shootKey)
				{
					if ((tanks[i]->getCooldown() == 0 || tanks[i]->getBulletType() != 0) && tanks[i]->getExplodingBullet() == NULL)
						tanks[i]->shot();
					else if (tanks[i]->getExplodingBullet() != NULL)
						tanks[i]->detonate();
				}
			if (event.type == Event::KeyReleased)
				if (event.key.code == tanks[i]->shootKey)
					tanks[i]->stop();
		}
	}
	for (int i = 0; i < amountPlayers; i++)
	{
		dx = 0;
		dr = 0;
		if (Keyboard::isKeyPressed(tanks[i]->controlKeys[0]))
			dx++;
		if (Keyboard::isKeyPressed(tanks[i]->controlKeys[1]))
			dx--;
		if (Keyboard::isKeyPressed(tanks[i]->controlKeys[2]))
			dr--;
		if (Keyboard::isKeyPressed(tanks[i]->controlKeys[3]))
			dr++;
		tanks[i]->move(dx * 2.5);
		tanks[i]->rotate(dr * 3);
		int tmp = checkCollision(tanks[i]);
		if (tmp)
		{
			tanks[i]->rotate(dr * (-3));
			tanks[i]->move(dx * (-2.5));
		}
		collecting(tanks[i]);
	}
}

void GameController::moveBullets(Bullet* pp)
{
	if (pp->move(&walls) != NULL)
	{
		ExplodingBullet* tmpb;
		if (tmpb = dynamic_cast<ExplodingBullet*>(pp))
			tmpb->detonate();
		else
		{
			delete pp;
			bullets.erase(find(bullets.begin(), bullets.end(), pp));
		}
	}
}

void GameController::viewAll()
{
	for (int w = 0; w < walls.size(); w++)
		walls[w]->draw(&window);
	for (int i = 0; i < bullets.size(); i++)
		(*bullets[i]).draw(&window);
	for (int i = 0; i < boosts.size(); i++)
		(*boosts[i]).draw(&window);
	for (int i = 0; i < amountPlayers; i++)
	{
		tanks[i]->draw(&window);
		tanks[i]->decrement();
	}
	window.display();
	window.clear(Color::Green);
}


Vector2f GameController::randField()
{
	int x, y;
	Vector2f vector;
	do
	{
		x = rand() % amountWall ;
		y = rand() % amountWall ;
	} while (fields[x][y] != 0);
	fields[x][y]++;
	vector.x = x * 100 + 55;
	vector.y = y * 95 + 55;
	return vector;
}

int  GameController::checkCollision(Tank* obiekt)
{
	for (int w = 0; w < walls.size(); w++)//jak by by³o na for_each(walls.begin(), walls.end(), [&](??) {}
	{
		GameObject* tmp = obiekt->algorithm->checkCollision(obiekt, walls[w]);
		if (tmp != NULL)
			return 1;
	}
	return 0;
}


GameController::~GameController()
{
}