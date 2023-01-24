#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>

using namespace sf;

const int WIDTH = 1200;
const int HEIGHT = 900;

class SortSimulation
{
private: 
	int size;
	float speed;
	int* array;
	float sizeofitemX, sizeofitemY;
	int maxelem;
	int k, f = 1;
	float sizeofheaderX = 0.f;
	float sizeofheaderY = 0.f;
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
		float x = 100000.f / speed;

		while (time < x)
		{
			time += clock.getElapsedTime().asMicroseconds();
		}
	}

	void BubbleSort(int reverse)
	{
		if (reverse == 1)
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = i; j < size; j++)
				{
					if (*(array + i) < *(array + j))
					{
						k = *(array + i);
						*(array + i) = *(array + j);
						*(array + j) = k;
					}
					Draw();
					Timer(speed);
				}
			}
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = i; j < size; j++)
				{

					if (*(array + i) > *(array + j))
					{
						k = *(array + i);
						*(array + i) = *(array + j);
						*(array + j) = k;
					}
					Draw();
					Timer(speed);
				}
			}
		}
	}

	void ChoiceSort(int reverse)
	{
		int mn, kk;
		if (reverse == 1)
		{
			for (int i = 0; i < size-1; i++)
			{
				mn = i;
				for (int j = i+1; j < size; j++)
				{
					if (*(array + j) > *(array + mn))
					{
						mn = j;
					}
					Draw();
					Timer(speed);
				}
				kk = *(array + i);
				*(array + i) = *(array + mn);
				*(array + mn) = kk;
			}
		}
		else
		{
			for (int i = 0; i < size-1; i++)
			{
				mn = i;
				for (int j = i+1; j < size; j++)
				{
					if (*(array + j) < *(array + mn))
					{
						mn = j;
					}
					Draw();
					Timer(speed);
				}
				kk = *(array + i);
				*(array + i) = *(array + mn);
				*(array + mn) = kk;
			}
		}
	}

	int partition(int reverse, int start, int pivot)
	{
		int i = start;
		if (reverse == 1)
		{
			while (i < pivot)
			{
				if (*(array + i) < *(array + pivot) && i == pivot - 1)
				{
					std::swap(*(array + i), *(array + pivot));
					pivot--;
				}
				else if (*(array + i) < *(array + pivot))
				{
					std::swap(*(array + pivot - 1), *(array + pivot));
					std::swap(*(array + i), *(array + pivot));
					pivot--;
				}
				else i++;
				Draw();
				Timer(speed);
			}
		}
		else
		{
			while (i < pivot)
			{
				if (*(array + i) > *(array + pivot) && i == pivot - 1)
				{
					std::swap(*(array + i), *(array + pivot));
					pivot--;
				}
				else if (*(array + i) > *(array + pivot))
				{
					std::swap(*(array + pivot - 1), *(array + pivot));
					std::swap(*(array + i), *(array + pivot));
					pivot--;
				}
				else i++;
				Draw();
				Timer(speed);
			}
		}
		return pivot;
	}

	void QuickSort(int reverse, int start, int end)
	{
		if (start < end)
		{
			int pivot = partition(reverse, start, end);

			QuickSort(reverse, start, pivot - 1);
			QuickSort(reverse, pivot + 1, end);
		}
	}

	void heapify(int reverse, int list[], int listLength, int root)
	{
		int largest = root;
		int l = 2 * root + 1;
		int r = 2 * root + 2;
		if (reverse == 1)
		{
			if (l < listLength && list[l] < list[largest])
				largest = l;

			if (r < listLength && list[r] < list[largest])
				largest = r;
		}
		else
		{
			if (l < listLength && list[l] > list[largest])
				largest = l;

			if (r < listLength && list[r] > list[largest])
				largest = r;
		}
		if (largest != root)
		{
			std::swap(list[root], list[largest]);
			heapify(reverse, list, listLength, largest);
		}
		Draw();
		Timer(speed);
	}

	void HeapSort(int reverse, int list[], int listLength)
	{
		for (int i = listLength / 2 - 1; i >= 0; i--)
			heapify(reverse, list, listLength, i);

		for (int i = listLength - 1; i >= 0; i--)
		{
			std::swap(list[0], list[i]);
			heapify(reverse, list, i, 0);
		}
	}

	void Controller()
	{
		if (Keyboard::isKeyPressed(Keyboard::LShift))
		{
			srand(std::time(NULL));
			for (int i = 0; i < size; i++)
			{
				*(array + i) = rand() % 10000;
			}
			maxelem = MaxOfArray(array, size);
			sizeofitemY = float(maxelem) / float(HEIGHT - sizeofheaderY);
			Draw();
		}
		if (Keyboard::isKeyPressed(Keyboard::Space) && f == 1)
		{
			//BubbleSort(0);
			//ChoiceSort(0);
			//QuickSort(0, 0, size);
			HeapSort(0, array, size);
			f = 0;
			Timer(0.000001f);
		}
		if (Keyboard::isKeyPressed(Keyboard::Space) && f == 0)
		{
			//BubbleSort(1);
			//ChoiceSort(1);
			//QuickSort(1, 0, size);
			HeapSort(1, array, size);
			f = 1;
			Timer(0.000001f);
		}
		Draw();
	}

	void Draw()
	{
		window->clear(sf::Color::Cyan);
		sprite.setScale(Vector2f(sizeofitemX / 25.f, float(HEIGHT)));
		Vector2f v = sprite.getScale();;
		for (int i = 0; i < size; i++)
		{
			sprite.setPosition(float(i) * v.x * 25.f, float(HEIGHT) - *(array + i) / sizeofitemY);
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
		this->sprite.setTextureRect(IntRect(300, 0, 10, 600));
		this->window = window;
		maxelem = MaxOfArray(array, size);
		sizeofitemX = float(WIDTH - sizeofheaderX) / float(size);
		sizeofitemY = float(maxelem)/float(HEIGHT - sizeofheaderY);
	}

	void update()
	{
		while (window->isOpen())
		{
			Controller();
		}
	}
};


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
	

	int size = 500;
	float speed = 2.5f;
	int* array = new int[size];
	for (int i = 0; i < size; i++) *(array + i) = rand()%10000;

	SortSimulation massiv(array, size, speed, itemSprite, pwindow);
	window.setActive(false);
	std::thread t(&SortSimulation::update, massiv);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
	}
	t.join();
	return 0;
}
//нужны потоки!!!!!!
//нужно сделать меню