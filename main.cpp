#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include "SortSimulation.h"
#include "Menu.h"
#include <math.h>
#include <Windows.h>

using namespace sf;

const int WIDTH = 1200;
const int HEIGHT = 800;

#define MAXSPEED 2.1f

int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	ContextSettings settings;
	settings.antialiasingLevel = 4;
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "SortSimulation", Style::Default, settings);
	RenderWindow* pwindow = &window;
	 
	Image itemImg;
	itemImg.loadFromFile("line.png");
	Texture itemTexture;
	itemTexture.loadFromImage(itemImg);
	Sprite itemSprite;
	itemSprite.setTexture(itemTexture);
	
	int size = 100;
	float speed = MAXSPEED;
	std::string speedRatio = "speed x1.00";
	int step = 16;
	int* array = new int[size];
	for (int i = 0; i < size; i++) *(array + i) = rand()%10000;

	bool pause = false;
	int control = 0;
	int sortNumber = 0;
	SortSimulation massiv(array, size, &speed, &step, itemSprite, pwindow, WIDTH, HEIGHT, &pause, &control, &sortNumber);

	window.setActive(false);
	std::thread t(&SortSimulation::update, &massiv);

	Menu menu(pwindow, &massiv, &speedRatio);
	std::thread mn(&Menu::update, &menu);
	
	bool flag1 = false, flag2 = false;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				control = 2;
				pause = false;
				window.close();
				mn.join();
				t.join();
				return 0;
			}
			if ((event.mouseWheel.delta == 1 || Keyboard::isKeyPressed(Keyboard::Equal)) && Mouse::getPosition(window).x > 2)
			{
				menu.ChangeSize(-50.f, -50.f);
				continue;
			}
			if ((event.mouseWheel.delta == -1 || Keyboard::isKeyPressed(Keyboard::Hyphen)) && Mouse::getPosition(window).x > 2)
			{
				menu.ChangeSize(50.f, 50.f);
				continue;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			control = 2;
			pause = false;
			window.close();
			mn.join();
			t.join();
			return 0;
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

		if (flag1 == false)
		{
			if (Keyboard::isKeyPressed(Keyboard::Up) && speed + 0.5f <= 2.1f)
			{
				speed += 0.5f;
				step *= 2;
				flag1 = true; 
				speedRatio = "speed x" + std::to_string(round((speed / MAXSPEED) * 100.0) / 100.0);
			}
		}
		else if (event.type == Event::KeyReleased && (event.key.code == Keyboard::Up)) flag1 = false;

		if (flag2 == false)
		{
			if (Keyboard::isKeyPressed(Keyboard::Down) && speed - 0.5f >= 0.01f)
			{
				speed -= 0.5f;
				step /= 2;
				flag2 = true;
				speedRatio = "speed x" + std::to_string(round((speed / MAXSPEED) * 100.0) / 100.0);
			}
		}
		else if (event.type == Event::KeyReleased && (event.key.code == Keyboard::Down)) flag2 = false;

		if (Keyboard::isKeyPressed(Keyboard::Num1) && !pause && control == 0)
		{
			sortNumber = 1;
			continue;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num2) && !pause && control == 0)
		{
			sortNumber = 2;
			continue;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num3) && !pause && control == 0)
		{
			sortNumber = 3;
			continue;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num4) && !pause && control == 0)
		{
			sortNumber = 4;
			continue;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num5) && !pause && control == 0)
		{
			sortNumber = 5;
			continue;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num6) && !pause && control == 0)
		{
			sortNumber = 6;
			continue;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num7) && !pause && control == 0)
		{
			sortNumber = 7;
			continue;
		}
	}
	return 0;
}