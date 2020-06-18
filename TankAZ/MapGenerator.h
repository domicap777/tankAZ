#pragma once
#include <vector>
#include <stack>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "FieldOnTheMap.h"
using namespace std;
class MapGenerator
{
	int range;
	int amountFields;
	vector < vector < shared_ptr < FieldOnTheMap >>  > fields;
	stack <int> zx;
	stack <int> zy;
	int x, y;
public:
	MapGenerator(int, vector < vector < bool >  > &, vector < vector < bool >  >&);
	~MapGenerator();
	void tworz(vector < vector < bool >  > &, vector < vector < bool >  >&);
	void randField(int&, int&);
};


