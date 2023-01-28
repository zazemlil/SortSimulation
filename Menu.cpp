#include "Menu.h"

void Menu::ChangeSize(float X, float Y)
{
	pSimulation->setSizeOfHeaderX(X);
	pSimulation->setSizeOfHeaderY(Y);
}

void Menu::Move()
{
	Vector2i pixelPos1 = Mouse::getPosition(*window) - pSimulation->getOffset();
	
	Vector2i pixelPos2;
	while (Mouse::isButtonPressed(Mouse::Left))
	{
		pixelPos2 = Mouse::getPosition(*window) - pixelPos1;
		pSimulation->setOffset(pixelPos2);
	}
}

void Menu::toCenter()
{
	if (Keyboard::isKeyPressed(Keyboard::Tab))
	{
		pSimulation->setOffset(Vector2i(0, 0));
	}
}

Menu::Menu(Window* window, SortSimulation* pSimulation)
{
	this->pSimulation = pSimulation;
	this->window = window;
}

void Menu::update()
{
	while (window->isOpen())
	{
		Move();
		toCenter();
	}
}