#pragma once

using namespace std;

class Table {

public:
	//Wskaźnik na początek dynamicznie alokowanej tablicy
	int* tab;

	//Zmienna całkowitoliczbowa przechowująca rozmiar tablicy
	int size;

	//Konstruktor
	Table();

	//Destruktor
	~Table();

	//Dodawanie elementu do tablicy na wyznaczoną pozycję
	void addValue(int index, int number);

	//Usuwanie elementu z tablicy
	void deleteFromTable(int index);

	//Wyświetlanie zawartości tablicy
	void display();

	//Tworzenie tablicy
	void generateTable(int size, int minValue, int maxValue);

	//Wczytywanie danych z pliku
	int loadFromFile(string FileName);

	//Sprawdzenie czy dana wartość znajduje się w tablicy
	bool IsValueInTable(int val);

	//Wyświetlenie menu tablicy
	void menu_table();

	//Testowanie tablicy
	void testTable(int testSize);
};