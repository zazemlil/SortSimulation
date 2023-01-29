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
		if (windowVec.x < mouseVec.x && windowVec.x + pSimulation->getResolution().x + 30 > mouseVec.x) // window->getSize().x
		{
			if (windowVec.y < mouseVec.y && windowVec.y + pSimulation->getResolution().y + 30 > mouseVec.y) // window->getSize().y
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
	//Mutex mute;
	Font font;
	font.loadFromFile("font.ttf");
	Text text;
	text.setFont(font);
	text.setCharacterSize(30);
	//text.setColor(Color::Red);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	switch (pSimulation->getNumberOfSort())
	{
	case 1:
		text.setString("11111111111");
		break;
	case 2:
		text.setString("22222222222");
		break;
	case 3:
		text.setString("33333333333");
		break;
	case 4:
		text.setString("44444444444");
		break;
	case 5:
		text.setString("55555555555");
		break;
	case 6:
		text.setString("66666666666");
		break;
	case 7:
		text.setString("77777777777");
		break;
	default:
		text.setString("00000000000");
		break;
	}
	text.setPosition(500, 500);
	//mute.lock();
	//window->setActive(true);
	//window->draw(text);
	//window->display();
	//window->setActive(false);
	//mute.unlock();
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