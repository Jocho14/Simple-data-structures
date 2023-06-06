//main.cpp : Ten plik zawiera funkcjê „main”.W nim rozpoczyna siê i koñczy wykonywanie programu.
#include<iostream>
#include "Table.h"
#include "List.h"
#include "Heap.h"
#include <conio.h>

using namespace std;

int main(int argc, char* argv[])
{
	Table table;
	List list;
	Heap heap;
	char option;
	do {
		cout << endl;
		cout << "==== MENU GLOWNE ===" << endl;
		cout << "1.Tablica" << endl;
		cout << "2.Lista" << endl;
		cout << "3.Kopiec" << endl;
		cout << "0.Wyjscie" << endl;
		cout << "Podaj opcje:";
		option = _getche();
		cout << endl;

		switch (option) {
		case '1':
			table.menu_table();
			break;

		case '2':
			list.menu_list();
			break;

		case '3':
			heap.menu_heap();
			break;
		}

	} while (option != '0');

	return 0;
}
