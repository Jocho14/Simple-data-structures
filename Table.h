#pragma once

using namespace std;

class Table {

public:
	//Wska�nik na pocz�tek dynamicznie alokowanej tablicy
	int* tab;

	//Zmienna ca�kowitoliczbowa przechowuj�ca rozmiar tablicy
	int size;

	//Konstruktor
	Table();

	//Destruktor
	~Table();

	//Dodawanie elementu do tablicy na wyznaczon� pozycj�
	void addValue(int index, int number);

	//Usuwanie elementu z tablicy
	void deleteFromTable(int index);

	//Wy�wietlanie zawarto�ci tablicy
	void display();

	//Tworzenie tablicy
	void generateTable(int size, int minValue, int maxValue);

	//Wczytywanie danych z pliku
	int loadFromFile(string FileName);

	//Sprawdzenie czy dana warto�� znajduje si� w tablicy
	bool IsValueInTable(int val);

	//Wy�wietlenie menu tablicy
	void menu_table();

	//Testowanie tablicy
	void testTable(int testSize);
};