#pragma once
#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include "SortSimulation.h"
#include <mutex>

using namespace sf;

class Menu
{
private:
	SortSimulation* pSimulation;
	RenderWindow* window;
	Text text;

	void Move();
	void toCenter();
	void NameOfSort();

public:
	Menu(RenderWindow* window, SortSimulation* pSimulation);
	void ChangeSize(float X, float Y);
	void update();
};