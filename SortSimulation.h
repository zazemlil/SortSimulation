#pragma once
#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>

using namespace sf;

class SortSimulation
{
private:
	int size;
	float speed;
	int* array;
	float sizeofitemX, sizeofitemY;
	int maxelem;
	int k, f = 1;
	float sizeofheaderX = 0.f, sizeofheaderY = 0.f;
	RenderWindow* window;
	int WIDTH, HEIGHT;
	Sprite sprite;

	void BubbleSort(int reverse);

	void ChoiceSort(int reverse);

	int partition(int reverse, int start, int pivot);
	void QuickSort(int reverse, int start, int end);

	void heapify(int reverse, int list[], int listLength, int root);
	void HeapSort(int reverse, int list[], int listLength);

	void merge(int reverse, int array[], int const left, int const mid, int const right);
	void MergeSort(int reverse, int array[], int const begin, int const end);

	void CocktailSort(int reverse, int a[], int n);

	bool isSorted(int reverse, int a[], int n);
	void shuffle(int a[], int n);
	void BogoSort(int reverse, int a[], int n);


	int MaxOfArray(int* array, int size);
	void Timer(float speed);
	void Controller();
	void Draw();

public:
	SortSimulation(int* array, int size, float speed, Sprite sprite, RenderWindow* window, int WIDTH, int HEIGHT);
	void update();
};