#pragma once

using namespace std;

class Node {
public:
	//konstruktor elementu listy
	Node();

	//wska�nik na poprzedni element listy
	Node* prev;

	//wska�nik na nast�pny element listy
	Node* next;

	//zmienna przechowuj�ca warto�� elementu listy
	int nodeVal;
};