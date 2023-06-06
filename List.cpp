#include <iostream>
#include <conio.h>
#include <ctime>
#include <string>
#include <fstream>
#include "List.h"
#include <string>
#include <chrono>

using namespace std;

List::List() {
    List::head = nullptr;
    List::tail = nullptr;
    List::count = 0;
}

List::~List() {
    Node* temp = head;
    while (temp) {
        temp = head->next;
        delete head;
        head = temp;
    }
}

void List::addValue(int index, int number) {
    //Sprawdzenie czy indeks mieœci siê w przedziale [0, size]
    if (index > count || index < 0) {
        cout << "index out of range";
    }
    //Przypadek kiedy lista jest pusta
    else if (head == nullptr) {
        Node* newNode = new Node;
        newNode->nodeVal = number;
        head = newNode;
        tail = newNode;

        count++;
    }
    else {
        //Dodanie elementu na pocz¹tek listy
        if (index == 0) {
            //Stworzenie nowego elementu, do którego zostanie przypisana podana na wejœciu wartoœæ 
            Node* newNode = new Node;
            newNode->nodeVal = number;

            newNode->next = head; //przypisanie nastêpnika nowego elementu na aktualnie pierwszy element
            head->prev = newNode; //ustawienie poprzednika aktualnego pierwszego elementu jako nowy element
            head = newNode; //ustawienie pierwszego elementu jako nowy element

            count++;

        }
        //Dodanie elementu na koniec listy
        else if (index == count) {
            Node* newNode = new Node;
            newNode->nodeVal = number;

            newNode->prev = tail; //ustawienie poprzednika nowego elementu na aktualnie ostatni element
            tail->next = newNode; //ustawienie nastêpnika aktualnie ostatniego elementu na nowy element
            tail = newNode; //ustawienie ostatniego elementu jako nowy element

            count++;
        }

        else {
            if (count > 0) {
                Node* newNode = new Node;
                newNode->nodeVal = number;

                Node* leftNodeNeigh = head;

                int i = 0;
                while (leftNodeNeigh) {
                    if (i + 1 == index) {
                        break;
                    }
                    leftNodeNeigh = leftNodeNeigh->next;
                    i++;
                }

                Node* rightNodeNeigh = leftNodeNeigh->next;

                newNode->prev = leftNodeNeigh;
                newNode->next = rightNodeNeigh;

                leftNodeNeigh->next = newNode;
                rightNodeNeigh->prev = newNode;

                count++;
            }
        }
    }
}

void List::deleteFromList(int number) {
    if (head != nullptr) {
        Node* tempNode = head;

        while (tempNode) {
            if (tempNode->nodeVal == number) {
                break;
            }
            tempNode = tempNode->next;
        }

        if (tempNode != nullptr) {
            if (tempNode == head) {
                head = tempNode->next;
            }
            if (tempNode == tail) {
                tail = tempNode->prev;
            }
            if (tempNode->prev != nullptr) {
                //zmiana wskaŸnika nastêpuj¹cego po poprzednim elemencie na nastêpnik elementu usuwanego
                tempNode->prev->next = tempNode->next;
            }
            if (tempNode->next != nullptr) {
                //zmiana wskaŸnika poprzedzaj¹cego nastêpny element na poprzednik elementu usuwanego
                tempNode->next->prev = tempNode->prev;
            }

            delete tempNode;
            count--;
        }
    }
}

void List::generateList(int size, int minValue, int maxValue) {
    srand(time(NULL));

    count = size;

    for (int i = 0; i < size; i++) {
        Node* newNode = new Node;

        newNode->nodeVal = rand() % (maxValue - minValue + 1) + minValue; //przypisanie losowej wartoœci do nowego elementu listy
        newNode->prev = tail;	//poprzednik nowego elementu jest dotychczasowym ostatnim elementem listy
        newNode->next = nullptr; //nastêpnik nowego elementu listy nie istnieje wiêc jest nullptr

        if (tail) { //je¿eli lista nie jest pusta to nastêpnik dotychczasowego ostatniego elementu listy to nowy element listy
            tail->next = newNode;
        }
        else { //w przeciwnym wypadku (lista jest pusta) nowy element staje siê pierwszym elementem listy
            head = newNode;
        }
        //ustawienie ostatniego elementu (ogona) listy jako nowy element
        tail = newNode;
    }
}

int List::loadFromFile(string FileName) {
    ifstream userDataFile;
    int number;
    bool isFirstLine = true;

    userDataFile.open(FileName);

    if (userDataFile.fail()) {
        cout << endl << "Couldn't open the file" << endl;
    }


    if (!(userDataFile >> count)) { //wartoœæ w 1 wierszu w pliku okreœla liczbê elementów
        cout << "Couldn't read the numbers of variable properly" << endl;
        return 0;
    }

    else if (userDataFile.good()) {

        while (userDataFile >> number) {
            Node* newNode = new Node;

            newNode->nodeVal = number; //przypisanie losowej wartoœci do nowego elementu listy
            newNode->prev = tail;	//poprzednik nowego elementu jest dotychczasowym ostatnim elementem listy
            newNode->next = nullptr; //nastêpnik nowego elementu listy nie istnieje wiêc jest nullptr

            if (tail) { //je¿eli lista nie jest pusta to nastêpnik dotychczasowego ostatniego elementu listy to nowy element listy
                tail->next = newNode;
            }
            else { //w przeciwnym wypadku (lista jest pusta) nowy element staje siê pierwszym elementem listy
                head = newNode;
            }
            //ustawienie ostatniego elementu (ogona) listy jako nowy element
            tail = newNode;
        }

    }
    userDataFile.close();
    return 0;
}

bool List::IsValueInList(int val) {
    Node* tempNode = head;
    while (tempNode) {
        if (tempNode->nodeVal == val) {
            return true;
        }
        tempNode = tempNode->next;
    }
    return false;
}



void List::display() {

    cout << endl;
    Node* temp = head;

    cout << "Od przodu: ";
    while (temp) {
        cout << temp->nodeVal << " ";
        temp = temp->next;
    }
    cout << endl;
    temp = tail;

    cout << "Od tylu: ";
    while (temp) {
        cout << temp->nodeVal << " ";
        temp = temp->prev;
    }
}

void List::testList(int testSize) {
    cout << "Test dla " << testSize << " danych\n";
    long averageTimeAddToEnd = 0;				//zmienna przechowuj¹ca œredni czas dodawania na koniec dla 100 powtórzeñ dla ró¿nych danych
    long averageTimeAddAtStart = 0;				//zmienna przechowuj¹ca œredni czas dodawania na pocz¹tek dla 100 powtórzeñ dla ró¿nych danych
    long averageTimeAddAtRandom = 0;			//zmienna przechowuj¹ca œredni czas dodawania w losowe miejsce dla 100 powtórzeñ dla ró¿nych danych

    long averageTimeDeleteFromEnd = 0;		//zmienna przechowuj¹ca œredni czas usuwania z koñca dla 100 powtórzeñ dla ró¿nych danych
    long averageTimeDeleteFromStart = 0;		//zmienna przechowuj¹ca œredni czas usuwania z pocz¹tku dla 100 powtórzeñ dla ró¿nych danych
    long averageTimeDeleteFromRandom = 0;	//zmienna przechowuj¹ca œredni czas usuwania z losowego miejsca dla 100 powtórzeñ dla ró¿nych danych

    long averageTimeFindValue = 0;

    int testAmount = 100;               //zmienna przechowuj¹ca liczbê powtórzeñ testu

    int k = testSize / 20;

    srand((unsigned int)time(NULL));
    for (int j = 0; j < testAmount; j++) {
        generateList(testSize, -testSize, testSize);

        long averageAddToEndforKNumbers = 0;
        long averageAddToStartforKNumbers = 0;
        long averageAddToRandomforKNumbers = 0;

        long averageDeleteFromEndforKNumbers = 0;
        long averageDeleteFromStartforKNumbers = 0;
        long averageDeleteFromRandomforKNumbers = 0;


        //Dodawanie na koniec listy
        for (int i = 0; i < k; i++) {
            auto TimeStart = chrono::high_resolution_clock::now();
            addValue(count, rand() % (2 * testSize + 1) - testSize);
            auto TimeEnd = chrono::high_resolution_clock::now();
            averageAddToStartforKNumbers += chrono::duration_cast<chrono::nanoseconds>(TimeEnd - TimeStart).count();
        }
        //Przywrócenie wielkoœci listy
        for (int i = 0; i < k; i++) {
            deleteFromList(0);
        }

        //Dodawanie na pocz¹tek listy
        for (int i = 0; i < k; i++) {
            auto TimeStart = chrono::high_resolution_clock::now();
            addValue(0, rand() % (2 * testSize + 1) - testSize);
            auto TimeEnd = chrono::high_resolution_clock::now();
            averageAddToEndforKNumbers += chrono::duration_cast<chrono::nanoseconds>(TimeEnd - TimeStart).count();

        }

        //Przywrócenie wielkoœci listy
        for (int i = 0; i < k; i++) {
            deleteFromList(0);
        }

        //Dodawanie w losowym w liœcie
        for (int i = 0; i < k; i++) {
            auto TimeStart = chrono::high_resolution_clock::now();
            addValue(rand() % testSize, rand() % (2 * testSize + 1) - testSize);
            auto TimeEnd = chrono::high_resolution_clock::now();
            averageAddToRandomforKNumbers += chrono::duration_cast<chrono::nanoseconds>(TimeEnd - TimeStart).count();
        }

        //Przywrócenie wielkoœci  listy
        for (int i = 0; i < k; i++) {
            deleteFromListByIndex(0);
        }

        //Usuwanie z pocz¹tku listy
        for (int i = 0; i < k; i++) {
            auto TimeStart = chrono::high_resolution_clock::now();
            deleteFromListByIndex(0);
            auto TimeEnd = chrono::high_resolution_clock::now();
            averageDeleteFromStartforKNumbers += chrono::duration_cast<chrono::nanoseconds>(TimeEnd - TimeStart).count();
        }

        //Przywrócenie wielkoœci listy
        for (int i = 0; i < k; i++) {
            addValue(0, rand() % (2 * testSize + 1) - testSize);
        }

        //Usuwanie z koñca listy
        for (int i = 0; i < k; i++) {
            auto TimeStart = chrono::high_resolution_clock::now();
            deleteFromListByIndex(count - 1);
            auto TimeEnd = chrono::high_resolution_clock::now();
            averageDeleteFromEndforKNumbers += chrono::duration_cast<chrono::nanoseconds>(TimeEnd - TimeStart).count();
        }

        //Przywrócenie wielkoœci listy
        for (int i = 0; i < k; i++) {
            addValue(count, rand() % (2 * testSize + 1) - testSize);
        }

        //Usuwanie z losowego miejsca w liœcie
        for (int i = 0; i < k; i++) {
            auto TimeStart = chrono::high_resolution_clock::now();
            deleteFromListByIndex(rand() % count);
            auto TimeEnd = chrono::high_resolution_clock::now();
            averageDeleteFromRandomforKNumbers += chrono::duration_cast<chrono::nanoseconds>(TimeEnd - TimeStart).count();

        }

        //Przywrócenie wielkoœci listy
        for (int i = 0; i < k; i++) {
            addValue(count, rand() % (2 * testSize + 1) - testSize);
        }

        //Szukanie wartoœci w liœcie
        auto TimeStart = chrono::high_resolution_clock::now();
        IsValueInList(rand() % (2 * testSize + 1) - testSize);
        auto TimeEnd = chrono::high_resolution_clock::now();
        averageTimeFindValue += chrono::duration_cast<chrono::nanoseconds>(TimeEnd - TimeStart).count();


        averageAddToEndforKNumbers /= k;
        averageAddToStartforKNumbers /= k;
        averageAddToRandomforKNumbers /= k;

        averageDeleteFromEndforKNumbers /= k;
        averageDeleteFromStartforKNumbers /= k;
        averageDeleteFromRandomforKNumbers /= k;



        averageTimeAddToEnd += averageAddToEndforKNumbers;
        averageTimeAddAtStart += averageAddToStartforKNumbers;
        averageTimeAddAtRandom += averageAddToRandomforKNumbers;

        averageTimeDeleteFromEnd += averageDeleteFromEndforKNumbers;
        averageTimeDeleteFromStart += averageDeleteFromStartforKNumbers;
        averageTimeDeleteFromRandom += averageDeleteFromRandomforKNumbers;

    }

    averageTimeAddToEnd /= testAmount;
    averageTimeAddAtStart /= testAmount;
    averageTimeAddAtRandom /= testAmount;

    averageTimeDeleteFromEnd /= testAmount;
    averageTimeDeleteFromStart /= testAmount;
    averageTimeDeleteFromRandom /= testAmount;

    averageTimeFindValue /= testAmount;


    string filePathWithResult = "./Lista_czas_" + to_string(testSize) + ".txt";
    ofstream outputFile;

    outputFile.open(filePathWithResult);
    if (!outputFile.is_open()) {
        cout << "couldn't open the file\n";
        return;
    }

    outputFile << "Œredni czas dodawania na koniec listy: " + to_string(averageTimeAddToEnd) + "ns\n";
    outputFile << "Œredni czas dodawania na pocz¹tek listy: " + to_string(averageTimeAddAtStart) + "ns\n";
    outputFile << "Œredni czas dodawania w losowe miejsce w liœcie: " + to_string(averageTimeAddAtRandom) + "ns\n";

    outputFile << "Œredni czas usuwania z koñca listy: " + to_string(averageTimeDeleteFromEnd) + "ns\n";
    outputFile << "Œredni czas usuwania z pocz¹tku listy: " + to_string(averageTimeDeleteFromStart) + "ns\n";
    outputFile << "Œredni czas usuwania z losowego miejsca w liœcie: " + to_string(averageTimeDeleteFromRandom) + "ns\n";

    outputFile << "Œredni czas wyszukiwania: " + to_string(averageTimeFindValue) + "ns\n";
    outputFile.close();
}

void List::deleteFromListByIndex(int index) {
    if (head != nullptr) {
        Node* tempNode = head;

        if (index == count - 1) {
            tempNode = tail;
        }

        else if (index == 0) {
            tempNode = head;
        }

        else {
            for (int i = 0; i < index; i++) {
                tempNode = tempNode->next;
            }
        }

        if (tempNode != nullptr) {
            if (tempNode == head) {
                head = tempNode->next;
            }
            if (tempNode == tail) {
                tail = tempNode->prev;
            }
            if (tempNode->prev != nullptr) {
                //zmiana wskaŸnika nastêpuj¹cego po poprzednim elemencie na nastêpnik elementu usuwanego
                tempNode->prev->next = tempNode->next;
            }
            if (tempNode->next != nullptr) {
                //zmiana wskaŸnika poprzedzaj¹cego nastêpny element na poprzednik elementu usuwanego
                tempNode->next->prev = tempNode->prev;
            }

            delete tempNode;
            count--;
        }
    }
}


void displayMenuList(string info)
{
    cout << endl;
    cout << info << endl;
    cout << "1.Wczytaj z pliku" << endl;
    cout << "2.Usun" << endl;
    cout << "3.Dodaj" << endl;
    cout << "4.Znajdz" << endl;
    cout << "5.Utworz losowo" << endl;
    cout << "6.Wyswietl" << endl;
    cout << "7.Test (pomiary)" << endl;
    cout << "0.Powrot do menu" << endl;
    cout << "Podaj opcje: ";
}

void List::menu_list() {
    List* myList = new List();
    char opt;
    string fileName;
    int index, value;
    int minVal, maxVal;

    do {
        displayMenuList("--- LISTA ---");
        opt = _getche();
        cout << endl;
        switch (opt) {
        case '1': //tutaj wczytytwanie listy z pliku
            delete myList;
            myList = new List();

            cout << "Podaj nazwe zbioru: ";
            cin >> fileName;
            myList->loadFromFile(fileName);
            myList->display();
            cout << endl;
            break;

        case '2': //tutaj usuwanie elemenu z listy
            cout << "Podaj wartosc: ";
            cin >> index;
            myList->deleteFromList(index);
            myList->display();
            cout << endl;
            break;

        case '3': //tutaj dodawanie elemetu do listy
            cout << "Podaj index: ";
            cin >> index;
            cout << "Podaj wartosc: ";
            cin >> value;

            myList->addValue(index, value);
            myList->display();
            cout << endl;
            break;

        case '4': //tutaj znajdowanie elemetu w liœcie
            cout << "Podaj wartosc: ";
            cin >> value;
            if (myList->IsValueInList(value))
                cout << "Podana wartosc jest w liscie";
            else
                cout << "Podanej wartosci NIE ma w liscie";
            cout << endl;
            break;

        case '5':  //tutaj generowanie listy
            //Usuwanie dotychczasowej listy
            delete myList;

            myList = new List();

            cout << "Podaj ilosc elementow listy: ";
            cin >> value;
            cout << "Podaj minimalna liczbe: ";
            cin >> minVal;
            cout << "Podaj maksymalna liczbe: ";
            cin >> maxVal;
            myList->generateList(value, minVal, maxVal);
            myList->display();
            cout << endl;
            break;

        case '6':  //tutaj wyœwietlanie listy
            myList->display();
            cout << endl;
            break;

        case '7':
            myList->testList(5000);
            myList->testList(8000);
            myList->testList(10000);
            myList->testList(16000);
            myList->testList(20000);
            myList->testList(40000);
            myList->testList(60000);
            myList->testList(100000);
            break;
        }

    } while (opt != '0');
}



