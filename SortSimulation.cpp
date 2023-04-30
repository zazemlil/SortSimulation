#include "SortSimulation.h"

SortSimulation::SortSimulation(int* array, int size, float* speed, int* step, Sprite sprite, RenderWindow* window, int WIDTH, int HEIGHT, bool* pause, int* control, int* sortNumber)
{
	this->WIDTH = WIDTH;
	this->HEIGHT = HEIGHT;
	this->size = size;
	this->speed = speed;
	this->array = array;
	this->sprite = sprite;
	this->sprite.setTextureRect(IntRect(300, 0, 10, 1));
	this->window = window;
	this->pause = pause;
	this->control = control;
	this->sortNumber = sortNumber;
	this->comparisons = new int;
	this->step = step;
	*comparisons = 0;
	sizeofheaderX = 0.f;
	sizeofheaderY = 0.f;
	maxelem = MaxOfArray(array, size);
	sizeofitemX = float(WIDTH - sizeofheaderX) / float(size);
	sizeofitemY = float(maxelem) / float(HEIGHT - sizeofheaderY);
	offset.x = 0;
	offset.y = 0;
	font.loadFromFile("font.ttf");
	text.setFont(font);
	text.setCharacterSize(40);
	text.setFillColor(Color::Red);
	text.setStyle(sf::Text::Bold);
	text.setPosition(5, -7);

	supportElem = new SupportElements(size);

	Image itemImg;
	itemImg.loadFromFile("line.png");
	Texture itemTexture;
	itemTexture.loadFromImage(itemImg);
	Sprite itemSprite;
	itemSprite.setTexture(itemTexture);
	this->sprite = itemSprite;
	this->sprite.setTextureRect(IntRect(300, 0, 10, 1));
}

SortSimulation::~SortSimulation()
{
	delete comparisons;
}

void SortSimulation::Draw()
{
	window->clear(sf::Color::Cyan);
	sizeofitemX = float(WIDTH - sizeofheaderX) / float(size);
	sizeofitemY = float(maxelem) / float(HEIGHT - sizeofheaderY);
	Vector2f v = sprite.getScale();

	for (int i = 0; i < size; i++)
	{
		switch (supportElem->GetElement(i))
		{
		case 1:
			sprite.setColor(sf::Color::Red);
			break;
		case 2:
			sprite.setColor(sf::Color::Green);
			break;
		case 3:
			sprite.setColor(sf::Color::Blue);
			break;
		default:
			sprite.setColor(sf::Color::Black);
			break;
		}

		sprite.setScale(Vector2f(sizeofitemX / 25.f, 1 + *(array + i) / sizeofitemY));
		sprite.setPosition(float(i) * v.x * 25.f + offset.x, float(HEIGHT) - *(array + i) / sizeofitemY + offset.y);
		window->draw(sprite);
		window->draw(text);
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
	static int stp = *step;
	

	while (*pause)
	{
		int flag = 0;
		if (stp - 1 >= 0)
		{
			stp--;
			flag = 1;
			return;
		}
		
		while (Keyboard::isKeyPressed(Keyboard::Right))
		{
			if (stp <= 0) stp = *step;
		}
		if (flag == 1)
		{
			return;
		}
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

void SortSimulation::Timer(float* speed)
{
	Clock clock;
	float time = 0;
	float x = 1000000000.f / *speed;
	while (time < x)
	{
		time += clock.getElapsedTime().asMicroseconds();
	}
}

void SortSimulation::setSizeOfHeaderX(float X)
{
	if (this->sizeofheaderX + X * float(WIDTH) / 1800.f <= float(WIDTH) / 1.75f && this->sizeofheaderX + X * float(WIDTH) / 1800.f >= 0)
		this->sizeofheaderX += X * float(WIDTH) / 1800.f;
}

void SortSimulation::setSizeOfHeaderY(float Y)
{
	if (this->sizeofheaderY + Y * float(HEIGHT) / 1800.f <= float(HEIGHT) / 1.75f && this->sizeofheaderY + Y * float(HEIGHT) / 1800.f >= 0)
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

void SortSimulation::setOffset(Vector2f offset)
{
	this->offset = offset;
}

Vector2f SortSimulation::getOffset()
{
	return offset;
}

int SortSimulation::getNumberOfSort()
{
	return *sortNumber;
}

bool SortSimulation::RestartSort()
{
	if (*control == 2)
		return true;
	return false;
}

Vector2f SortSimulation::getResolution()
{
	Vector2f vec(WIDTH, HEIGHT);
	return vec;
}

void SortSimulation::setText(sf::String text)
{
	this->text.setString(text);
}

int* SortSimulation::getComp()
{
	return comparisons;
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
				supportElem->SetElement(i, 1);
				supportElem->SetElement(j, 2);
				*comparisons += 1;
				Draw();
				Timer(speed);
				Pause();
				supportElem->Clear(j);
				if (RestartSort()) return;
			}
			supportElem->Clear(i);
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
				supportElem->SetElement(i, 1);
				supportElem->SetElement(j, 2);
				*comparisons += 1;
				Draw();
				Timer(speed);
				Pause();
				supportElem->Clear(j);
				if (RestartSort()) return;
			}
			supportElem->Clear(i);
		}
	}
	supportElem->Clear();
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
				supportElem->SetElement(i, 1);
				supportElem->SetElement(j, 2);
				*comparisons += 1;
				Draw();
				Timer(speed);
				Pause();
				supportElem->Clear(j);
				if (RestartSort()) return;
			}
			supportElem->Clear(i);
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
				supportElem->SetElement(i, 1);
				supportElem->SetElement(j, 2);
				*comparisons += 1;
				Draw();
				Timer(speed);
				Pause();
				supportElem->Clear(j);
				if (RestartSort()) return;
			}
			supportElem->Clear(i);
			kk = *(array + i);
			*(array + i) = *(array + mn);
			*(array + mn) = kk;
		}
	}
	supportElem->Clear();
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
			*comparisons += 1;
			supportElem->SetElement(i, 2);
			supportElem->SetElement(pivot, 3);
			supportElem->SetElement(start, 1);
			Draw();
			Timer(speed);
			Pause();
			supportElem->Clear(i);
			supportElem->Clear(start);
			supportElem->Clear(pivot);
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
			*comparisons += 1;
			supportElem->SetElement(i, 2);
			supportElem->SetElement(pivot, 3);
			supportElem->SetElement(start, 1);
			Draw();
			Timer(speed);
			Pause();
			supportElem->Clear(i);
			supportElem->Clear(start);
			supportElem->Clear(pivot);
			if (RestartSort()) return -1;
		}
	}
	supportElem->Clear();
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

int SortSimulation::heapify(int reverse, int list[], int listLength, int root)
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
	*comparisons += 1;
	supportElem->SetElement(largest, 2);
	supportElem->SetElement(root, 3);
	supportElem->SetElement(listLength, 1);
	Draw();
	Timer(speed);
	Pause();
	supportElem->Clear(largest);
	supportElem->Clear(listLength);
	supportElem->Clear(root);
	if (RestartSort()) return -1;
	return 1;
}

void SortSimulation::HeapSort(int reverse, int list[], int listLength)
{
	for (int i = listLength / 2 - 1; i >= 0; i--)
		if (heapify(reverse, list, listLength, i) == -1) return;

	for (int i = listLength - 1; i >= 0; i--)
	{
		std::swap(list[0], list[i]);
		if (heapify(reverse, list, i, 0) == -1) return;
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
			}
			else
			{
				array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
				indexOfSubArrayTwo++;
			}
			*comparisons += 1;
			supportElem->SetElement(indexOfMergedArray, 2);
			supportElem->SetElement(left, 1);
			supportElem->SetElement(right, 1);
			Draw();
			Timer(speed);
			Pause();
			supportElem->Clear(indexOfMergedArray);
			supportElem->Clear(left);
			supportElem->Clear(right);
			if (RestartSort()) return;
			indexOfMergedArray++;
		}
		supportElem->Clear();
		while (indexOfSubArrayOne < subArrayOne)
		{
			array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
			indexOfMergedArray++;
			supportElem->SetElement(indexOfMergedArray, 2);
			supportElem->SetElement(left, 1);
			supportElem->SetElement(right, 1);
			Draw();
			Timer(speed);
			Pause();
			supportElem->Clear(indexOfMergedArray);
			supportElem->Clear(left);
			supportElem->Clear(right);
			if (RestartSort()) return;
		}
		supportElem->Clear();
		while (indexOfSubArrayTwo < subArrayTwo)
		{
			array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
			indexOfMergedArray++;
			supportElem->SetElement(indexOfMergedArray, 2);
			supportElem->SetElement(left, 1);
			supportElem->SetElement(right, 1);
			Draw();
			Timer(speed);
			Pause();
			supportElem->Clear(indexOfMergedArray);
			supportElem->Clear(left);
			supportElem->Clear(right);
			if (RestartSort()) return;
		}
		supportElem->Clear();
	}
	else
	{
		while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo)
		{
			if (leftArray[indexOfSubArrayOne] >= rightArray[indexOfSubArrayTwo])
			{
				array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
				indexOfSubArrayOne++;
			}
			else
			{
				array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
				indexOfSubArrayTwo++;
			}
			*comparisons += 1;
			supportElem->SetElement(indexOfMergedArray, 2);
			supportElem->SetElement(left, 1);
			supportElem->SetElement(right, 1);
			Draw();
			Timer(speed);
			Pause();
			supportElem->Clear(indexOfMergedArray);
			supportElem->Clear(left);
			supportElem->Clear(right);
			if (RestartSort()) return;
			indexOfMergedArray++;
		}
		while (indexOfSubArrayOne < subArrayOne)
		{
			array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
			indexOfMergedArray++;
			supportElem->SetElement(indexOfMergedArray, 2);
			supportElem->SetElement(left, 1);
			supportElem->SetElement(right, 1);
			Draw();
			Timer(speed);
			Pause();
			supportElem->Clear(indexOfMergedArray);
			supportElem->Clear(left);
			supportElem->Clear(right);
			if (RestartSort()) return;
		}
		while (indexOfSubArrayTwo < subArrayTwo)
		{
			array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
			indexOfMergedArray++;
			supportElem->SetElement(indexOfMergedArray, 2);
			supportElem->SetElement(left, 1);
			supportElem->SetElement(right, 1);
			Draw();
			Timer(speed);
			Pause();
			supportElem->Clear(indexOfMergedArray);
			supportElem->Clear(left);
			supportElem->Clear(right);
			if (RestartSort()) return;
		}
	}
	supportElem->Clear();
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
				if (a[i] > a[i + 1]) 
				{
					std::swap(a[i], a[i + 1]);
					swapped = true;
				}
				*comparisons += 1;
				supportElem->SetElement(i, 2);
				supportElem->SetElement(end, 1);
				supportElem->SetElement(start, 1);
				Draw();
				Timer(speed);
				Pause();
				supportElem->Clear(i);
				supportElem->Clear(end);
				supportElem->Clear(start);
				if (RestartSort()) return;
			}
		}
		else
		{
			for (int i = start; i < end; ++i) {
				if (a[i] < a[i + 1]) {
					std::swap(a[i], a[i + 1]);
					swapped = true;
				}
				*comparisons += 1;
				supportElem->SetElement(i, 2);
				supportElem->SetElement(end, 1);
				supportElem->SetElement(start, 1);
				Draw();
				Timer(speed);
				Pause();
				supportElem->Clear(i);
				supportElem->Clear(end);
				supportElem->Clear(start);
				if (RestartSort()) return;
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
				}
				*comparisons += 1;
				supportElem->SetElement(i, 2);
				supportElem->SetElement(end, 1);
				supportElem->SetElement(start, 1);
				Draw();
				Timer(speed);
				Pause();
				supportElem->Clear(i);
				supportElem->Clear(end);
				supportElem->Clear(start);
				if (RestartSort()) return;
			}
		}
		else
		{
			for (int i = end - 1; i >= start; --i) {
				if (a[i] < a[i + 1]) {
					std::swap(a[i], a[i + 1]);
					swapped = true;
				}
				*comparisons += 1;
				supportElem->SetElement(i, 2);
				supportElem->SetElement(end, 1);
				supportElem->SetElement(start, 1);
				Draw();
				Timer(speed);
				Pause();
				supportElem->Clear(i);
				supportElem->Clear(end);
				supportElem->Clear(start);
				if (RestartSort()) return;
			}
		}
		++start;
		supportElem->Clear();
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

int SortSimulation::shuffle(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		int j = rand() % n;
		std::swap(a[i], a[j]);
		*comparisons += 1;
		supportElem->SetElement(j, 2);
		supportElem->SetElement(i, 1);
		Draw();
		Timer(speed);
		Pause();
		supportElem->Clear(j);
		supportElem->Clear(i);
		if (RestartSort()) return -1;
	}
	return 1;
}

void SortSimulation::BogoSort(int reverse, int a[], int n)
{
	while (!isSorted(reverse, a, n))
		if (shuffle(a, n) == -1) return;
}

void SortSimulation::Controller()
{
	switch (*control)
	{
	case 1:
	{
		*comparisons = 0;
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
			f = 1;
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
			f = 0;
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

SupportElements::SupportElements(int size)
{
	this->size = size;
	array = new int[size];
	for (int i = 0; i < size; i++) *(array + i) = 0;
}

SupportElements::~SupportElements() 
{ 
	delete[] array; 
}

void SupportElements::Clear()
{
	for (int i = 0; i < size; i++)
	{
		*(array + i) = 0;
	}
}

void SupportElements::Clear(int index)
{
	*(array + index) = 0;
}

void SupportElements::SetElement(int index, int color)
{
	*(array + index) = color;
}

int SupportElements::GetElement(int index)
{
	return *(array + index);
}