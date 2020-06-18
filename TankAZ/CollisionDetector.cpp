#include "CollisionDetector.h"



CollisionDetector::CollisionDetector()
{
}


CollisionDetector::~CollisionDetector()
{
}

GameObject*CollisionDetector::checkCollision(GameObject *o1, GameObject *o2)
{
	GameObject *obiekt1 = o1;
	GameObject *obiekt2 = o2;
	for (int i = 0; i < 2; i++)
	{
		if (i == 1)
		{
			obiekt1 = o2;
			obiekt2 = o1;
		}
		for (int p = 0; p < obiekt1->p.size(); p++)
		{
			Vector2f p1s = obiekt1->getPosition();
			Vector2f p1e = obiekt1->p[p];
			for (int q = 0; q < obiekt2->p.size(); q++)
			{
				Vector2f p2s = obiekt2->p[q];
				Vector2f p2e = obiekt2->p[(q + 1) % obiekt2->p.size()];
				float h = (p2e.x - p2s.x) * (p1s.y - p1e.y) - (p1s.x - p1e.x) * (p2e.y - p2s.y);
				float t1 = ((p2s.y - p2e.y) * (p1s.x - p2s.x) + (p2e.x - p2s.x) * (p1s.y - p2s.y)) / h;
				float t2 = ((p1s.y - p1e.y) * (p1s.x - p2s.x) + (p1e.x - p1s.x) * (p1s.y - p2s.y)) / h;
				if (t1 >= 0.0f && t1 < 1.0f && t2 >= 0.0f && t2 < 1.0f)
					return o2;
			}
		}
	}
	return NULL;
}
