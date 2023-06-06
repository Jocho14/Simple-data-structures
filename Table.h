#pragma once

using namespace std;

class Table {

public:
	//WskaŸnik na pocz¹tek dynamicznie alokowanej tablicy
	int* tab;

	//Zmienna ca³kowitoliczbowa przechowuj¹ca rozmiar tablicy
	int size;

	//Konstruktor
	Table();

	//Destruktor
	~Table();

	//Dodawanie elementu do tablicy na wyznaczon¹ pozycjê
	void addValue(int index, int number);

	//Usuwanie elementu z tablicy
	void deleteFromTable(int index);

	//Wyœwietlanie zawartoœci tablicy
	void display();

	//Tworzenie tablicy
	void generateTable(int size, int minValue, int maxValue);

	//Wczytywanie danych z pliku
	int loadFromFile(string FileName);

	//Sprawdzenie czy dana wartoœæ znajduje siê w tablicy
	bool IsValueInTable(int val);

	//Wyœwietlenie menu tablicy
	void menu_table();

	//Testowanie tablicy
	void testTable(int testSize);
};