#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include "SortSimulation.h"

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
	

	int size = 250;
	float speed = 2.5f;
	int* array = new int[size];
	for (int i = 0; i < size; i++) *(array + i) = rand()%10000;

	SortSimulation massiv(array, size, speed, itemSprite, pwindow, WIDTH, HEIGHT);

	//window.setActive(false);
	//std::thread t(&SortSimulation::update, massiv);

	window.setActive(false);
	sf::Thread t(&SortSimulation::update, &massiv);
	t.launch();

	bool pause = false;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::P))
		{
			if (!pause)
			{
				//t.wait();
				pause = true;
			}
			else
			{

				pause = false;
			}
		}

	}
	//t.join();
	return 0;
}
// нужны потоки!!!!!!(поток Controller для перезапуска симуляции в irl)
// нужно сделать меню выбора сортировки 