#pragma once
#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include "SortSimulation.h"

class Menu
{
private:
	SortSimulation* pSimulation;
public:
	void foo(float X, float Y);
	Menu(SortSimulation* pSimulation);
};