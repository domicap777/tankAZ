#include "FieldOnTheMap.h"

bool FieldOnTheMap::isNoVisitedNeighbor()
{
	if (noVisitedNeighbors > 0)
	{
		return true;
	}
	return false;
}

void FieldOnTheMap::decrement()
{
	noVisitedNeighbors--;
}

void FieldOnTheMap::visit()
{
	isVisited = true;
}

bool FieldOnTheMap::getIsVisited()
{
	return isVisited;
}

FieldOnTheMap::FieldOnTheMap()
{
	isVisited = false;
	noVisitedNeighbors = 4;
}

