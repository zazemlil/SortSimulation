#include <SFML/Graphics.hpp>
#include <ctime>
#include <Windows.h>
#include <iostream>

using namespace sf;

const int WIDTH = 800;
const int HEIGHT = 600;

class SortSimulation
{
private: 
	int size;
	float speed;
	int* array;
	float sizeofitemX, sizeofitemY;
	int maxelem;
	int k, f = 1;
	RenderWindow* window;
	
	int MaxOfArray(int* array, int size)
	{
		int s = *(array);
		for (int i = 0; i < size; i++)
		{
			if (*(array + i) > s) s = *(array + i);
		}
		return s;
	}

	void Timer(float speed)
	{
		Clock clock;
		float time = 0;
		float x = 0.01f / speed;

		while (time < x)
		{
			time += clock.getElapsedTime().asMicroseconds();
		}
	}

	void BubleSort(int reverse)
	{
		if (reverse == 1)
		{
			for (int i = 0; i < 100; i++)
			{
				for (int j = i; j < 100; j++)
				{

					if (*(array + i) < *(array + j))
					{
						k = *(array + i);
						*(array + i) = *(array + j);
						*(array + j) = k;
					}
					Draw();
				}
			}
		}
		else
		{
			for (int i = 0; i < 100; i++)
			{
				for (int j = i; j < 100; j++)
				{

					if (*(array + i) > *(array + j))
					{
						k = *(array + i);
						*(array + i) = *(array + j);
						*(array + j) = k;
					}
					Draw();
				}
			}
		}
	}

	void Controller()
	{
		if (Keyboard::isKeyPressed(Keyboard::LShift))
		{
			srand(std::time(NULL));
			for (int i = 0; i < size; i++)
			{
				*(array + i) = rand() % 1000;
			}
			Draw();
		}
		if (Keyboard::isKeyPressed(Keyboard::Space) && f == 1)
		{
			BubleSort(0);
			f = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::Space) && f == 0)
		{
			BubleSort(1);
			f = 1;
		}
	}

	void Draw()
	{
		window->clear(sf::Color::Cyan);
		for (int i = 0; i < size; i++)
		{
			Timer(speed);
			sprite.setScale(Vector2f(100.f/float(WIDTH),float(HEIGHT)));
			sprite.setPosition(float(i)*7.f, float(HEIGHT) - *(array+i)/sizeofitemY);
			//sprite.setScale(Vector2f(32.f / (float(WIDTH) / float(size)), float(HEIGHT)));
			////sprite.setPosition(float(i) * float(WIDTH) / float(size), float(HEIGHT) - *(array+i)/sizeofitemY);
			//sprite.setPosition(float(i) * float(WIDTH) / float(size) / 50.f, float(HEIGHT) - *(array + i) / sizeofitemY);
			window->draw(sprite);
		}
		window->display();
	}
public:
	Sprite sprite;
	SortSimulation(int* array, int size, float speed, Sprite sprite, RenderWindow* window)
	{
		this->size = size;
		this->speed = speed;
		this->array = array;
		this->sprite = sprite;
		this->window = window;
		maxelem = MaxOfArray(array, size);
		sizeofitemX = float(WIDTH) / float(size);
		sizeofitemY = float(maxelem)/float(HEIGHT);
		Draw();
	}

	void update()
	{
		Controller();
	}
};


int main()
{
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "main");
	RenderWindow* pwindow = &window;

	Image itemImg;
	itemImg.loadFromFile("line.png");
	Texture itemTexture;
	itemTexture.loadFromImage(itemImg);
	Sprite itemSprite;
	itemSprite.setTexture(itemTexture);

	int size = 100;
	float speed = 0.1f;
	int* array = new int[size];
	for (int i = 0; i < size; i++) *(array + i) = rand()%1000;

	SortSimulation massiv(array, size, speed, itemSprite, pwindow);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		massiv.update();
	}
	return 0;
}
//не могу подобрать разрешение для спрайта
//мб нужны потоки