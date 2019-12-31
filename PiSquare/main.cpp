#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

int getSize()
{
	int size;
	do
	{
		system("cls");
		cout << "Give the size of the pi-square: ";
		cin >> size;
		if (size < 1 || size > 31)
		{
			cout << "Please select a number between 1 and 31." << endl;
			system("pause");
		}
	} while (size < 1 || size > 31);
	return size;
}

int ** getPiSquare(int size)
{
	int ** piSquare = new int *[size];
	for (int i = 0; i < size; i++)
		piSquare[i] = new int[size];
	fstream piDigits;
	piDigits.open("pi.txt", ios::in);
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			char nextDigit;
			piDigits >> nextDigit;
			piSquare[i][j] = nextDigit - 48;
		}
	return piSquare;
}

void showPiSquare(int ** piSquare, int size)
{
	auto outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < size; i++)
	{
		for (int j = size - 1; j >= 0; j--)
		{
			SetConsoleTextAttribute(outputHandle, i + j + 1);
			cout << piSquare[i][size - 1 - j] << " ";
		}
		cout << endl;
	}
}

int * getDiagonalSums(int ** piSquare, int size)
{
	int * diagonalSums = new int[2 * size - 1];
	for (int i = 0; i < 2 * size - 1; i++)
		diagonalSums[i] = 0;

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			diagonalSums[(i + j)] += piSquare[i][size - 1 - j];
	return diagonalSums;
}

void showDiagonalSums(int * diagonalSums, int size)
{
	auto outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < 2 * size - 1; i++)
	{
		SetConsoleTextAttribute(outputHandle, i + 1);
		cout << diagonalSums[i] << " ";
	}
	cout << endl;
	SetConsoleTextAttribute(outputHandle, 7);
}

int main()
{
	int size = getSize();
	auto piSquare = getPiSquare(size);
	showPiSquare(piSquare, size);
	auto diagonalSums = getDiagonalSums(piSquare, size);
	showDiagonalSums(diagonalSums, size);
	system("pause");
	return 0;
}