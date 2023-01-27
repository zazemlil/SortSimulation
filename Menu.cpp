#include "Menu.h"

void Menu::foo(float X, float Y)
{
	pSimulation->setSizeOfHeaderX(X);
	pSimulation->setSizeOfHeaderY(Y);
}

Menu::Menu(SortSimulation* pSimulation)
{
	this->pSimulation = pSimulation;
}
