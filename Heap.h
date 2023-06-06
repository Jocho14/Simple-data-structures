#pragma once

using namespace std;

class Heap {

public:
	//wskaŸnik na pocz¹tek tablicy dynamicznej an której jest zbudowany kopiec
	int* tab;

	//zmienna zawieraj¹ca rozmiar kopca
	int size;

	//zmienna zawieraj¹ca liczbe elementów kopca
	int count;

	//konstruktor kopca
	Heap();

	//destruktor kopca
	~Heap();

	//Metoda naprawiaj¹ca w³asnoœæ kopca do góry od pewnego indeksu
	void heapifyUp(int index);

	//Metoda naprawiaj¹ca w³aœnoœc kopca w dó³ od pewnego indeksu
	void heapifyDown(int index);

	//Metoda dodaj¹ca element do kopca
	void addValue(int value);

	//metoda usuwaj¹ca element z kopca
	void deleteFromHeap(int value);

	//Metoda sprawdzaj¹ca czy istnieje dany element w kopcu
	bool isValueInHeap(int value);

	//Metoda generuj¹ca kopiec o zadanej liczbie elementów
	void generateHeap(int size, int minValue, int maxValue);

	//Wczytywanie danych z pliku
	int loadFromFile(string FileName);

	//Metoda wyœwietlaj¹ca zawartoœæ kopca (graficznie)
	void showHeap();

	//Metoda wyœwietlaj¹ca zawartoœæ kopca jako tablicê
	void display();

	//Metoda wyœwietlaj¹ca menu kopca
	void menu_heap();

	//Testowanie kopca
	void testHeap(int testSize);

	//metoda usuwaj¹ca element z kopca po indexie (metoda u¿ywana przy testowaniu)
	void deleteFromHeapByIndex(int index);
};