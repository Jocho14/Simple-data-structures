#pragma once

#include "Node.h"

using namespace std;
class List {
public:
	//Konstruktor listy
	List();

	//Destruktor listy
	~List();

	//WskaŸnik na pierwszy element listy
	Node* head;

	//WskaŸnik na ostatni element listy
	Node* tail;

	//Zmienna przechowuj¹ca rozmiar listy
	int count;

	//Dodawanie elementu do listy na wyznaczon¹ pozycjê
	void addValue(int index, int number);

	//Usuwanie elementu (jeœli istnieje) o podanej wartoœci na wejœcu z listy
	void deleteFromList(int number);

	//Wyœwietlanie zawartoœci listy
	void display();

	//Tworzenie listy o podanym rozmiarze z losowo wygenerowanymi liczbami
	void generateList(int size, int minValue, int maxValue);

	//Wczytywanie danych z pliku
	int loadFromFile(string FileName);

	//Sprawdzenie czy dana wartoœæ znajduje siê w liœcie
	bool IsValueInList(int val);

	//Wyœwietlenie menu listy
	void menu_list();

	//Testowanie listy
	void testList(int testSize);

	//Usuwanie z listy po indexie
	void deleteFromListByIndex(int index);
};

