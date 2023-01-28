#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include "SortSimulation.h"
#include "Menu.h"
#include <atomic>

using namespace sf;

const int WIDTH = 1200;
const int HEIGHT = 800;


int main()
{
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "SortSimulation");
	RenderWindow* pwindow = &window;

	Image itemImg;
	itemImg.loadFromFile("line.png");
	Texture itemTexture;
	itemTexture.loadFromImage(itemImg);
	Sprite itemSprite;
	itemSprite.setTexture(itemTexture);
	

	int size = 200;
	float speed = 2.5f;
	int* array = new int[size];
	for (int i = 0; i < size; i++) *(array + i) = rand()%10000;

	std::atomic<bool> pause(false);
	int control = 0;
	int sortNumber = 0;
	SortSimulation massiv(array, size, speed, itemSprite, pwindow, WIDTH, HEIGHT, &pause, &control, &sortNumber);

	window.setActive(false);
	std::thread t(&SortSimulation::update, &massiv);

	Menu menu(pwindow, &massiv);
	std::thread mn(&Menu::update, &menu);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			if (event.mouseWheel.delta == 1 || Keyboard::isKeyPressed(Keyboard::Equal))
			{
				menu.ChangeSize(-50.f, -50.f);
				continue;
			}
			if (event.mouseWheel.delta == -1 || Keyboard::isKeyPressed(Keyboard::Hyphen))
			{
				menu.ChangeSize(50.f, 50.f);
				continue;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::P))
		{
			pause = true;
			continue;
		}
		if (Keyboard::isKeyPressed(Keyboard::O))
		{
			pause = false;
			continue;
		}
		if (Keyboard::isKeyPressed(Keyboard::Space) && !pause)
		{
			control = 1;
			continue;
		}
		if (Keyboard::isKeyPressed(Keyboard::LShift) && !pause)
		{
			control = 2;
			continue;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num1))
		{
			sortNumber = 1;
			continue;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num2))
		{
			sortNumber = 2;
			continue;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num3))
		{
			sortNumber = 3;
			continue;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num4))
		{
			sortNumber = 4;
			continue;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num5))
		{
			sortNumber = 5;
			continue;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num6))
		{
			sortNumber = 6;
			continue;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num7))
		{
			sortNumber = 7;
			continue;
		}
	}
	mn.join();
	t.join();
	return 0;
}
// сделать нормальный размер по высоте
// нужно сделать меню выбора сортировки 
// немного криво масштабируетс€ после уменьшени€(сверху зазор)