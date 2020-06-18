#pragma once
class FieldOnTheMap
{
	bool isVisited;
	int noVisitedNeighbors;
public:
	FieldOnTheMap();
	bool isNoVisitedNeighbor();
	void decrement();
	void visit();
	bool getIsVisited();
};
