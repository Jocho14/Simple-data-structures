#pragma once

using namespace std;

class Node {
public:
	//konstruktor elementu listy
	Node();

	//wskaŸnik na poprzedni element listy
	Node* prev;

	//wskaŸnik na nastêpny element listy
	Node* next;

	//zmienna przechowuj¹ca wartoœæ elementu listy
	int nodeVal;
};