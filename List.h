#pragma once

#include "Node.h"

using namespace std;
class List {
public:
	//Konstruktor listy
	List();

	//Destruktor listy
	~List();

	//Wska�nik na pierwszy element listy
	Node* head;

	//Wska�nik na ostatni element listy
	Node* tail;

	//Zmienna przechowuj�ca rozmiar listy
	int count;

	//Dodawanie elementu do listy na wyznaczon� pozycj�
	void addValue(int index, int number);

	//Usuwanie elementu (je�li istnieje) o podanej warto�ci na wej�cu z listy
	void deleteFromList(int number);

	//Wy�wietlanie zawarto�ci listy
	void display();

	//Tworzenie listy o podanym rozmiarze z losowo wygenerowanymi liczbami
	void generateList(int size, int minValue, int maxValue);

	//Wczytywanie danych z pliku
	int loadFromFile(string FileName);

	//Sprawdzenie czy dana warto�� znajduje si� w li�cie
	bool IsValueInList(int val);

	//Wy�wietlenie menu listy
	void menu_list();

	//Testowanie listy
	void testList(int testSize);

	//Usuwanie z listy po indexie
	void deleteFromListByIndex(int index);
};

