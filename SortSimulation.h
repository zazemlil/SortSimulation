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
	float sizeofheaderX, sizeofheaderY;
	RenderWindow* window;
	int WIDTH, HEIGHT;
	std::atomic<bool>* pause;
	int* control;
	Sprite sprite;
	int* sortNumber;
	Vector2i offset;

	int MaxOfArray(int* array, int size);
	void Timer(float speed);
	void Controller();
	void Pause();
	void Draw();
	bool RestartSort();

	void BubbleSort(int reverse);

	void ChoiceSort(int reverse);

	int partition(int reverse, int start, int pivot);
	void QuickSort(int reverse, int start, int end);

	int heapify(int reverse, int list[], int listLength, int root);
	void HeapSort(int reverse, int list[], int listLength);

	void merge(int reverse, int array[], int const left, int const mid, int const right);
	void MergeSort(int reverse, int array[], int const begin, int const end);

	void CocktailSort(int reverse, int a[], int n);

	bool isSorted(int reverse, int a[], int n);
	int shuffle(int a[], int n);
	void BogoSort(int reverse, int a[], int n);

public:
	SortSimulation(int* array, int size, float speed, Sprite sprite, RenderWindow* window, int WIDTH, int HEIGHT, std::atomic<bool>* pause, int* control, int* sortNumber);
	void update();
	void setSizeOfHeaderX(float X);
	void setSizeOfHeaderY(float Y);
	float getSizeOfHeaderX();
	float getSizeOfHeaderY();
	void setOffset(Vector2i offset);
	Vector2i getOffset();
};