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
	RenderWindow* window;
	Text text;
	Text comp;
	std::string* speedRatio;

	void Move();
	void toCenter();
	void NameOfSort();

public:
	Menu(RenderWindow* window, SortSimulation* pSimulation, std::string* speedRatio);
	void ChangeSize(float X, float Y);
	void update();
};