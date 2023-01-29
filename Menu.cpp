#include "Menu.h"

void Menu::ChangeSize(float X, float Y)
{
	pSimulation->setSizeOfHeaderX(X);
	pSimulation->setSizeOfHeaderY(Y);
}

void Menu::Move()
{
	Vector2f pixelPos1 = window->mapPixelToCoords(Mouse::getPosition(*window)) - pSimulation->getOffset();
	Vector2f pixelPos2;
	while (Mouse::isButtonPressed(Mouse::Left))
	{
		Vector2f mouseVec = window->mapPixelToCoords(Mouse::getPosition());
		Vector2f windowVec = window->mapPixelToCoords(window->getPosition());
		if (windowVec.x < mouseVec.x && windowVec.x + pSimulation->getResolution().x + 30 > mouseVec.x)
		{
			if (windowVec.y < mouseVec.y && windowVec.y + pSimulation->getResolution().y + 30 > mouseVec.y)
			{
				pixelPos2 = window->mapPixelToCoords(Mouse::getPosition(*window)) - pixelPos1;
				pSimulation->setOffset(pixelPos2);
			}
		}
	}
}

void Menu::toCenter()
{
	if (Keyboard::isKeyPressed(Keyboard::Tab))
	{
		pSimulation->setOffset(Vector2f(0, 0));
	}
}

void Menu::NameOfSort()
{
	switch (pSimulation->getNumberOfSort())
	{
	case 1:
		text.setString("Bubble Sort");
		break;
	case 2:
		text.setString("Choice Sort");
		break;
	case 3:
		text.setString("Quick Sort");
		break;
	case 4:
		text.setString("Heap Sort");
		break;
	case 5:
		text.setString("Merge Sort");
		break;
	case 6:
		text.setString("Cocktail Sort");
		break;
	case 7:
		text.setString("Random sorting(");
		break;
	default:
		text.setString("NaN");
		break;
	}
	pSimulation->setText(text.getString());
}

Menu::Menu(RenderWindow* window, SortSimulation* pSimulation)
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
		NameOfSort();
	}
}