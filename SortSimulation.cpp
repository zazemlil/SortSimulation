#include "SortSimulation.h"

SortSimulation::SortSimulation(int* array, int size, float speed, Sprite sprite, RenderWindow* window, int WIDTH, int HEIGHT, std::atomic<bool>* pause, int* control, int* sortNumber)
{
	this->WIDTH = WIDTH;
	this->HEIGHT = HEIGHT;
	this->size = size;
	this->speed = speed;
	this->array = array;
	this->sprite = sprite;
	this->sprite.setTextureRect(IntRect(300, 0, 10, 600));
	this->window = window;
	this->pause = pause;
	this->control = control;
	this->sortNumber = sortNumber;
	sizeofheaderX = 0.f;
	sizeofheaderY = 0.f;
	maxelem = MaxOfArray(array, size);
	sizeofitemX = float(WIDTH - sizeofheaderX) / float(size);
	sizeofitemY = float(maxelem) / float(HEIGHT - sizeofheaderY);
}

void SortSimulation::Draw()
{
	window->clear(sf::Color::Cyan);
	sizeofitemX = float(WIDTH - sizeofheaderX) / float(size);
	sizeofitemY = float(maxelem) / float(HEIGHT - sizeofheaderY);
	sprite.setScale(Vector2f(sizeofitemX / 25.f, float(HEIGHT)));
	Vector2f v = sprite.getScale();
	for (int i = 0; i < size; i++)
	{
		sprite.setPosition(float(i) * v.x * 25.f, float(HEIGHT) - *(array + i) / sizeofitemY);
		window->draw(sprite);
	}
	window->display();
}

void SortSimulation::update()
{
	while (window->isOpen())
	{
		Controller();
	}
}

void SortSimulation::Pause()
{
	while (*pause)
	{
		std::this_thread::yield();
		Draw();
	}
}

int SortSimulation::MaxOfArray(int* array, int size)
{
	int s = *(array);
	for (int i = 0; i < size; i++)
	{
		if (*(array + i) > s) s = *(array + i);
	}
	return s;
}

void SortSimulation::Timer(float speed)
{
	Clock clock;
	float time = 0;
	float x = 100000.f / speed;

	while (time < x)
	{
		time += clock.getElapsedTime().asMicroseconds();
	}
}

void SortSimulation::setSizeOfHeaderX(float X)
{
	//if (this->sizeofheaderX < 300 && this->sizeofheaderX < 0)
		this->sizeofheaderX += X * float(WIDTH) / 1800.f;
}

void SortSimulation::setSizeOfHeaderY(float Y)
{
	//if (this->sizeofheaderY < 300 && this->sizeofheaderY < 0)
		this->sizeofheaderY += Y * float(HEIGHT) / 1800.f;
}

float SortSimulation::getSizeOfHeaderX()
{
	return sizeofheaderX;
}

float SortSimulation::getSizeOfHeaderY()
{
	return sizeofheaderY;
}

bool SortSimulation::RestartSort()
{
	if (*control == 2)
		return true;
	return false;
}

void SortSimulation::BubbleSort(int reverse)
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
				Pause();
				if (RestartSort()) return;
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
				Pause();
				if (RestartSort()) return;
			}
		}
	}
}

void SortSimulation::ChoiceSort(int reverse)
{
	int mn, kk;
	if (reverse == 1)
	{
		for (int i = 0; i < size - 1; i++)
		{
			mn = i;
			for (int j = i + 1; j < size; j++)
			{
				if (*(array + j) > *(array + mn))
				{
					mn = j;
				}
				Draw();
				Timer(speed);
				Pause();
				if (RestartSort()) return;
			}
			kk = *(array + i);
			*(array + i) = *(array + mn);
			*(array + mn) = kk;
		}
	}
	else
	{
		for (int i = 0; i < size - 1; i++)
		{
			mn = i;
			for (int j = i + 1; j < size; j++)
			{
				if (*(array + j) < *(array + mn))
				{
					mn = j;
				}
				Draw();
				Timer(speed);
				Pause();
				if (RestartSort()) return;
			}
			kk = *(array + i);
			*(array + i) = *(array + mn);
			*(array + mn) = kk;
		}
	}
}

int SortSimulation::partition(int reverse, int start, int pivot)
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
			Pause();
			if (RestartSort()) return -1;
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
			Pause();
			if (RestartSort()) return -1;
		}
	}
	return pivot;
}

void SortSimulation::QuickSort(int reverse, int start, int end)
{
	if (start < end)
	{
		int pivot = partition(reverse, start, end);
		if (pivot == -1) return;
		QuickSort(reverse, start, pivot - 1);
		QuickSort(reverse, pivot + 1, end);
	}
}

void SortSimulation::heapify(int reverse, int list[], int listLength, int root)
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
	Pause();
	if (RestartSort()) return;
}

void SortSimulation::HeapSort(int reverse, int list[], int listLength)
{
	for (int i = listLength / 2 - 1; i >= 0; i--)
		heapify(reverse, list, listLength, i);

	for (int i = listLength - 1; i >= 0; i--)
	{
		std::swap(list[0], list[i]);
		heapify(reverse, list, i, 0);
	}
}

void SortSimulation::merge(int reverse, int array[], int const left, int const mid, int const right)
{
	auto const subArrayOne = mid - left + 1;
	auto const subArrayTwo = right - mid;

	auto* leftArray = new int[subArrayOne];
	auto* rightArray = new int[subArrayTwo];

	for (auto i = 0; i < subArrayOne; i++)
		leftArray[i] = array[left + i];
	for (auto j = 0; j < subArrayTwo; j++)
		rightArray[j] = array[mid + 1 + j];

	auto indexOfSubArrayOne = 0;
	auto indexOfSubArrayTwo = 0; 
	int indexOfMergedArray = left; 

	if (reverse == 0)
	{
		while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo)
		{
			if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo])
			{
				array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
				indexOfSubArrayOne++;
				Draw();
				Timer(speed);
				Pause();
				if (RestartSort()) return;
			}
			else
			{
				array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
				indexOfSubArrayTwo++;
				Draw();
				Timer(speed);
				Pause();
				if (RestartSort()) return;
			}
			indexOfMergedArray++;
		}
		while (indexOfSubArrayOne < subArrayOne)
		{
			array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
			indexOfMergedArray++;
			Draw();
			Timer(speed);
			Pause();
			if (RestartSort()) return;
		}
		while (indexOfSubArrayTwo < subArrayTwo)
		{
			array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
			indexOfMergedArray++;
			Draw();
			Timer(speed);
			Pause();
			if (RestartSort()) return;
		}
	}
	else
	{
		while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo)
		{
			if (leftArray[indexOfSubArrayOne] >= rightArray[indexOfSubArrayTwo])
			{
				array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
				indexOfSubArrayOne++;
				Draw();
				Timer(speed);
				Pause();
				if (RestartSort()) return;
			}
			else
			{
				array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
				indexOfSubArrayTwo++;
				Draw();
				Timer(speed);
				Pause();
				if (RestartSort()) return;
			}
			indexOfMergedArray++;
		}
		while (indexOfSubArrayOne < subArrayOne)
		{
			array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
			indexOfMergedArray++;
			Draw();
			Timer(speed);
			Pause();
			if (RestartSort()) return;
		}
		while (indexOfSubArrayTwo < subArrayTwo)
		{
			array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
			indexOfMergedArray++;
			Draw();
			Timer(speed);
			Pause();
			if (RestartSort()) return;
		}
	}
	delete[] leftArray;
	delete[] rightArray;
}

void SortSimulation::MergeSort(int reverse, int array[], int const begin, int const end)
{
	if (begin >= end)
		return;

	auto mid = begin + (end - begin) / 2;
	MergeSort(reverse, array, begin, mid);
	MergeSort(reverse, array, mid + 1, end);
	merge(reverse, array, begin, mid, end);
}

void SortSimulation::CocktailSort(int reverse, int a[], int n)
{
	bool swapped = true;
	int start = 0;
	int end = n - 1;

	while (swapped) 
	{
		swapped = false;

		if (reverse == 0)
		{
			for (int i = start; i < end; ++i) {
				if (a[i] > a[i + 1]) {
					std::swap(a[i], a[i + 1]);
					swapped = true;
					Draw();
					Timer(speed);
					Pause();
					if (RestartSort()) return;
				}
			}
		}
		else
		{
			for (int i = start; i < end; ++i) {
				if (a[i] < a[i + 1]) {
					std::swap(a[i], a[i + 1]);
					swapped = true;
					Draw();
					Timer(speed);
					Pause();
					if (RestartSort()) return;
				}
			}
		}
		if (!swapped)
			break;

		swapped = false;

		--end;

		if (reverse == 0)
		{
			for (int i = end - 1; i >= start; --i) {
				if (a[i] > a[i + 1]) {
					std::swap(a[i], a[i + 1]);
					swapped = true;
					Draw();
					Timer(speed);
					Pause();
					if (RestartSort()) return;
				}
			}
		}
		else
		{
			for (int i = end - 1; i >= start; --i) {
				if (a[i] < a[i + 1]) {
					std::swap(a[i], a[i + 1]);
					swapped = true;
					Draw();
					Timer(speed);
					Pause();
					if (RestartSort()) return;
				}
			}
		}
		++start;
	}
}

bool SortSimulation::isSorted(int reverse, int a[], int n)
{
	while (--n > 0)
		if (reverse == 0)
		{
			if (a[n] < a[n - 1])
				return false;
		}
		else
		{
			if (a[n] > a[n - 1])
				return false;
		}
	return true;
}

void SortSimulation::shuffle(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		std::swap(a[i], a[rand() % n]);
		Draw();
		Timer(speed);
		Pause();
		if (RestartSort()) return;
	}
}

void SortSimulation::BogoSort(int reverse, int a[], int n)
{
	while (!isSorted(reverse, a, n))
		shuffle(a, n);
}

void SortSimulation::Controller()
{
	switch (*control)
	{
	case 1:
	{
		if (f == 0)
		{
			switch (*sortNumber)
			{
			case 1:
				BubbleSort(1);
				break;
			case 2:
				ChoiceSort(1);
				break;
			case 3:
				QuickSort(1, 0, size);
				break;
			case 4:
				HeapSort(1, array, size);
				break;
			case 5:
				MergeSort(1, array, 0, size - 1);
				break;
			case 6:
				CocktailSort(1, array, size);
				break;
			case 7:
				BogoSort(1, array, size);
				break;
			}
			//BubbleSort(1);
			//ChoiceSort(1);
			//QuickSort(1, 0, size);
			//HeapSort(1, array, size);
			//MergeSort(1, array, 0, size-1);
			//CocktailSort(1, array, size);
			//BogoSort(1, array, size);
			f = 1;
			Timer(0.000001f);
		}
		else
		{
			switch (*sortNumber)
			{
			case 1:
				BubbleSort(0);
				break;
			case 2:
				ChoiceSort(0);
				break;
			case 3:
				QuickSort(0, 0, size);
				break;
			case 4:
				HeapSort(0, array, size);
				break;
			case 5:
				MergeSort(0, array, 0, size - 1);
				break;
			case 6:
				CocktailSort(0, array, size);
				break;
			case 7:
				BogoSort(0, array, size);
				break;
			}
			//BubbleSort(0);
			//ChoiceSort(0);
			//QuickSort(0, 0, size);
			//HeapSort(0, array, size);
			//MergeSort(0, array, 0, size-1);
			//CocktailSort(0, array, size);
			//BogoSort(0, array, size);
			f = 0;
			Timer(0.000001f);
		}
		*control = 0;
		break;
	}
	case 2:
	{
		srand(std::time(NULL));
		for (int i = 0; i < size; i++)
		{
			*(array + i) = rand() % 10000;
		}
		maxelem = MaxOfArray(array, size);
		sizeofitemY = float(maxelem) / float(HEIGHT - sizeofheaderY);
		Draw();
		*control = 0;
		break;
	}
	}
	Draw();
	Pause();
}