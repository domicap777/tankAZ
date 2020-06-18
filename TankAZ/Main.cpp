#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <vector>
#include "GameController.h"

int main()
{
	GameController::getInstance()->start();
	return 0;
}
