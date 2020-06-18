#include "MapGenerator.h"



MapGenerator::MapGenerator(int amount, vector < vector < bool >  > & horizontal, vector < vector < bool >  > & vertical)
{
	range = amount;
	amountFields = range * range - 1;
	for (int i = 0; i < range; i++)
	{
		fields.push_back(vector<shared_ptr < FieldOnTheMap >>());
		for (int j = 0; j < range; j++)
		{
			shared_ptr < FieldOnTheMap > tmp(new FieldOnTheMap);
			fields[i].push_back(tmp);
		}
	}
	fields[0][0]->visit();
	for (int i = 0; i < range; i++)
	{
		(fields[range - 1][i])->decrement();
		(fields[0][i])->decrement();
		(fields[i][range - 1])->decrement();
		(fields[i][0])->decrement();
	}
	for (int i = 0; i < range; i++)
	{
		horizontal.push_back(vector<bool>());
		for (int j = 0; j < range + 1; j++)
			horizontal[i].push_back(1);
	}
	for (int i = 0; i < range + 1; i++)
	{
		vertical.push_back(vector<bool>());
		for (int j = 0; j < range; j++)
			vertical[i].push_back(1);
	}
	if (range > 1)
	{
		fields[0][1]->decrement();
		fields[1][0]->decrement();
	}
	this->tworz(horizontal, vertical);
}

MapGenerator::~MapGenerator()
{

}

void MapGenerator::tworz(vector < vector < bool >  > & horizontal, vector < vector < bool >  >& vertical)
{
	srand(time(NULL));
	int dx, dy;
	while (amountFields != 0)
	{
		if ((fields[x][y])->isNoVisitedNeighbor() == true)
		{
			randField(dx, dy);
			amountFields--;
			if (dy != 0)
				horizontal[x][y + ((dy + 1) / 2)] = false;
			else
				vertical[x + ((dx + 1) / 2)][y] = false;
			zx.push(x);
			zy.push(y);
			x = x + dx;
			y = y + dy;
			fields[x][y]->visit();
			try {
				(fields.at(x + 1)).at(y)->decrement();
			}
			catch (...) {}
			try {
				(fields.at(x - 1)).at(y)->decrement();
			}
			catch (...) {}
			try {
				(fields.at(x)).at(y + 1)->decrement();
			}
			catch (...) {}
			try {
				(fields.at(x)).at(y - 1)->decrement();
			}
			catch (...) {}
		}
		else
		{
			x = zx.top();
			y = zy.top();
			zx.pop();
			zy.pop();
		}
	}
}

void MapGenerator::randField(int & dx, int & dy)
{
	int jump;
	do
	{
		jump = rand() % 4;
		if (jump > 1)
		{
			dy = jump % 2 * 2 - 1;
			dx = 0;
		}
		else
		{
			dy = 0;
			dx = jump % 2 * 2 - 1;
		}
	} while (x + dx < 0 || x + dx >= range || y + dy < 0 || y + dy >= range || fields[x + dx][y + dy]->getIsVisited() == true);
}

