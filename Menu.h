#pragma once
#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include "SortSimulation.h"

using namespace sf;

class Menu
{
private:
	SortSimulation* pSimulation;
	Window* window;

	void Move();
	void toCenter();

public:
	Menu(Window* window, SortSimulation* pSimulation);
	void ChangeSize(float X, float Y);
	void update();
};