#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <conio.h>
#include <limits.h>
#include "Table.h"
#include <chrono>

using namespace std;

Table::Table() {
    Table::tab = nullptr;
    Table::size = 0;
}

Table::~Table() {
    if (tab != nullptr) {
        delete[] tab;
    }
}

int Table::loadFromFile(string FileName) {
    ifstream userDataFile;
    int number;
    int index = 0;

    userDataFile.open(FileName);

    if (userDataFile.fail()) {
        cout << "Couldn't open the file";
        return 0;
    }

    if (!(userDataFile >> size)) { //wartoœæ w 1 wierszu w pliku okreœla liczbê elementów
        cout << "Couldn't read the numbers of variable properly" << endl;
        return 0;
    }

    else if (userDataFile.good()) {
        tab = new int[size];
        while (userDataFile >> number) {
            tab[index] = number;
            index++;

            if (index == size) {
                break;
            }
        }

    }
    userDataFile.close();
    return 0;
}

bool Table::IsValueInTable(int val) {
    for (int i = 0; i < size; i++) {
        if (tab[i] == val) {
            return true;
        }
    }
    return false;
}

void Table::addValue(int index, int value) {
    //Sprawdzenie czy indeks mieœci siê w przedziale [0, size]

    if (index > size || index < 0) {
        return;
    }
    else if (size == 0) {
        tab = new int[1];
        tab[0] = value;
        size++;
    }
    else {
        //Dodanie elementu w dowolne miejsce w tablicy
        int* newTable = new int[size + 1];

        for (int i = 0; i < index; i++) {
            newTable[i] = tab[i];
        }

        newTable[index] = value;

        for (int i = index; i < size; i++) {
            newTable[i + 1] = tab[i];
        }

        delete[] tab;
        tab = newTable;
        newTable = nullptr;

        size++;
    }
}

void Table::deleteFromTable(int index) {
    //Sprawdzenie czy indeks mieœci siê w przedziale [0, size]
    if (index >= size || index < 0) {
        return;
    }
    else {
        //Usuniêcie elementu z dowolnego miejsca w tablicy
        if (size > 0) {
            int* newTable = new int[size - 1];

            int j = 0;
            for (int i = 0; i < size; i++) {
                if (i != index) {
                    newTable[j] = tab[i];
                    j++;
                }
            }

            delete[] tab;
            tab = newTable;
            newTable = nullptr;

            size--;
        }
    }
}

void Table::generateTable(int sizeParam, int minValue, int maxValue) {
    srand((unsigned int)time(NULL));

    size = sizeParam;

    tab = new int[size];

    for (int i = 0; i < size; i++) {
        tab[i] = rand() % (maxValue - minValue + 1) + minValue;
    }
}

void Table::display() {
    cout << '\n';
    for (int i = 0; i < size; i++) {
        cout << tab[i] << " ";
    }
    cout << '\n';
}

void Table::testTable(int testSize) {
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
        generateTable(testSize, -testSize, testSize);

        long averageAddToEndforKNumbers = 0;
        long averageAddToStartforKNumbers = 0;
        long averageAddToRandomforKNumbers = 0;

        long averageDeleteFromEndforKNumbers = 0;
        long averageDeleteFromStartforKNumbers = 0;
        long averageDeleteFromRandomforKNumbers = 0;


        //Dodawanie na koniec tablicy
        for (int i = 0; i < k; i++) {
            auto TimeStart = chrono::high_resolution_clock::now();
            addValue(size, rand() % (2 * testSize + 1) - testSize);
            auto TimeEnd = chrono::high_resolution_clock::now();
            averageAddToStartforKNumbers += chrono::duration_cast<chrono::nanoseconds>(TimeEnd - TimeStart).count();
        }
        //Przywrócenie wielkoœci tablicy
        for (int i = 0; i < k; i++) {
            deleteFromTable(0);
        }

        //Dodawanie na pocz¹tek tablicy
        for (int i = 0; i < k; i++) {
            auto TimeStart = chrono::high_resolution_clock::now();
            addValue(0, rand() % (2 * testSize + 1) - testSize);
            auto TimeEnd = chrono::high_resolution_clock::now();
            averageAddToEndforKNumbers += chrono::duration_cast<chrono::nanoseconds>(TimeEnd - TimeStart).count();

        }

        //Przywrócenie wielkoœci tablicy
        for (int i = 0; i < k; i++) {
            deleteFromTable(0);
        }

        //Dodawanie w losowym miejscu
        for (int i = 0; i < k; i++) {
            auto TimeStart = chrono::high_resolution_clock::now();
            addValue(rand() % testSize, rand() % (2 * testSize + 1) - testSize);
            auto TimeEnd = chrono::high_resolution_clock::now();
            averageAddToRandomforKNumbers += chrono::duration_cast<chrono::nanoseconds>(TimeEnd - TimeStart).count();
        }

        //Przywrócenie wielkoœci tablicy
        for (int i = 0; i < k; i++) {
            deleteFromTable(0);
        }

        //Usuwanie z pocz¹tku tablicy
        for (int i = 0; i < k; i++) {
            auto TimeStart = chrono::high_resolution_clock::now();
            deleteFromTable(0);
            auto TimeEnd = chrono::high_resolution_clock::now();
            averageDeleteFromStartforKNumbers += chrono::duration_cast<chrono::nanoseconds>(TimeEnd - TimeStart).count();
        }

        //Przywrócenie wielkoœci tablicy
        for (int i = 0; i < k; i++) {
            addValue(0, rand() % (2 * testSize + 1) - testSize);
        }

        //Usuwanie z koñca tablicy
        for (int i = 0; i < k; i++) {
            auto TimeStart = chrono::high_resolution_clock::now();
            deleteFromTable(size - 1);
            auto TimeEnd = chrono::high_resolution_clock::now();
            averageDeleteFromEndforKNumbers += chrono::duration_cast<chrono::nanoseconds>(TimeEnd - TimeStart).count();
        }

        //Przywrócenie wielkoœci tablicy
        for (int i = 0; i < k; i++) {
            addValue(size, rand() % (2 * testSize + 1) - testSize);
        }

        //Usuwanie z losowego miejsca w tablicy
        for (int i = 0; i < k; i++) {
            auto TimeStart = chrono::high_resolution_clock::now();
            deleteFromTable(rand() % size);
            auto TimeEnd = chrono::high_resolution_clock::now();
            averageDeleteFromRandomforKNumbers += chrono::duration_cast<chrono::nanoseconds>(TimeEnd - TimeStart).count();

        }

        //Przywrócenie wielkoœci tablicy
        for (int i = 0; i < k; i++) {
            addValue(size, rand() % (2 * testSize + 1) - testSize);
        }

        //Szukanie wartoœci w tablicy
        auto TimeStart = chrono::high_resolution_clock::now();
        IsValueInTable(rand() % (2 * testSize + 1) - testSize);
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


    string filePathWithResult = "./Tablica_czas_" + to_string(testSize) + ".txt";
    ofstream outputFile;

    outputFile.open(filePathWithResult);
    if (!outputFile.is_open()) {
        cout << "couldn't open the file\n";
        return;
    }

    outputFile << "Œredni czas dodawania na koniec tablicy: " + to_string(averageTimeAddToEnd) + "ns\n";
    outputFile << "Œredni czas dodawania na pocz¹tek tablicy: " + to_string(averageTimeAddAtStart) + "ns\n";
    outputFile << "Œredni czas dodawania w losowe miejsce w tablicy: " + to_string(averageTimeAddAtRandom) + "ns\n";

    outputFile << "Œredni czas usuwania z koñca tablicy: " + to_string(averageTimeDeleteFromEnd) + "ns\n";
    outputFile << "Œredni czas usuwania z pocz¹tku tablicy: " + to_string(averageTimeDeleteFromStart) + "ns\n";
    outputFile << "Œredni czas usuwania z losowego miejsca w tablicy: " + to_string(averageTimeDeleteFromRandom) + "ns\n";

    outputFile << "Œredni czas wyszukiwania: " + to_string(averageTimeFindValue) + "ns\n";
    outputFile.close();
}

void displayMenuTable(string info)
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

void Table::menu_table() {
    Table* myTab = new Table();
    char opt;
    string fileName;
    int index, value;
    int minVal, maxVal;

    do {
        displayMenuTable("--- TABLICA ---");
        opt = _getche();
        cout << endl;
        switch (opt) {
        case '1': //tutaj wczytytwanie  tablicy z pliku
            cout << "Podaj nazwe zbioru: ";
            cin >> fileName;
            myTab->loadFromFile(fileName);
            myTab->display();
            cout << endl;
            break;

        case '2': //tutaj usuwanie elemenu z tablicy
            cout << "Podaj index: ";
            cin >> index;
            myTab->deleteFromTable(index);
            myTab->display();
            cout << endl;
            break;

        case '3': //tutaj dodawanie elemetu do tablicy
            cout << "Podaj index: ";
            cin >> index;
            cout << "Podaj wartosc: ";
            cin >> value;

            myTab->addValue(index, value);
            myTab->display();
            cout << endl;
            break;

        case '4': //tutaj znajdowanie elemetu w tablicy
            cout << "Podaj wartosc: ";
            cin >> value;
            if (myTab->IsValueInTable(value))
                cout << "Podana wartosc jest w tablicy";
            else
                cout << "Podanej wartosci NIE ma w tablicy";
            cout << endl;
            break;

        case '5':  //tutaj generowanie  tablicy
            cout << "Podaj ilosc elementow tablicy: ";
            cin >> value;
            cout << "Podaj minimalna liczbê: ";
            cin >> minVal;
            cout << "Podaj maksymalna liczbe: ";
            cin >> maxVal;
            myTab->generateTable(value, minVal, maxVal);
            myTab->display();
            cout << endl;
            break;

        case '6':  //tutaj wyœwietlanie tablicy
            myTab->display();
            cout << endl;
            break;

        case '7':
            myTab->testTable(5000);
            myTab->testTable(8000);
            myTab->testTable(10000);
            myTab->testTable(16000);
            myTab->testTable(20000);
            myTab->testTable(40000);
            myTab->testTable(60000);
            myTab->testTable(100000);
            break;
        }
    } while (opt != '0');
}