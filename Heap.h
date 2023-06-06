#pragma once

using namespace std;

class Heap {

public:
	//wska�nik na pocz�tek tablicy dynamicznej an kt�rej jest zbudowany kopiec
	int* tab;

	//zmienna zawieraj�ca rozmiar kopca
	int size;

	//zmienna zawieraj�ca liczbe element�w kopca
	int count;

	//konstruktor kopca
	Heap();

	//destruktor kopca
	~Heap();

	//Metoda naprawiaj�ca w�asno�� kopca do g�ry od pewnego indeksu
	void heapifyUp(int index);

	//Metoda naprawiaj�ca w�a�no�c kopca w d� od pewnego indeksu
	void heapifyDown(int index);

	//Metoda dodaj�ca element do kopca
	void addValue(int value);

	//metoda usuwaj�ca element z kopca
	void deleteFromHeap(int value);

	//Metoda sprawdzaj�ca czy istnieje dany element w kopcu
	bool isValueInHeap(int value);

	//Metoda generuj�ca kopiec o zadanej liczbie element�w
	void generateHeap(int size, int minValue, int maxValue);

	//Wczytywanie danych z pliku
	int loadFromFile(string FileName);

	//Metoda wy�wietlaj�ca zawarto�� kopca (graficznie)
	void showHeap();

	//Metoda wy�wietlaj�ca zawarto�� kopca jako tablic�
	void display();

	//Metoda wy�wietlaj�ca menu kopca
	void menu_heap();

	//Testowanie kopca
	void testHeap(int testSize);

	//metoda usuwaj�ca element z kopca po indexie (metoda u�ywana przy testowaniu)
	void deleteFromHeapByIndex(int index);
};