#include <iostream>
#include <string>
#include <ctime>
#include "Heap.h"
#include <conio.h>
#include <fstream>
#include <chrono>


using namespace std;

Heap::Heap() {
    Heap::size = 120000;
    Heap::tab = new int[size];
    Heap::count = 0;
}

Heap::~Heap() {
    if (tab != nullptr) {
        delete[] tab;
    }
}

int Heap::loadFromFile(string FileName) {
    ifstream userDataFile;
    int number;
    int counter = 0;

    userDataFile.open(FileName);

    if (userDataFile.fail()) {
        cout << endl << "Couldn't open the file" << endl;
        return 0;
    }

    if (!(userDataFile >> count)) { //warto�� w 1 wierszu w pliku okre�la liczb� element�w
        cout << "Couldn't read the numbers of variable properly" << endl;
        return 0;
    }

    else if (userDataFile.good()) {

        while (userDataFile >> number) {
            tab[counter] = number;
            heapifyUp(counter);
            counter++;

            if (counter == count) {
                break;
            }
        }
    }
    userDataFile.close();
    return 0;
}


void Heap::heapifyUp(int index) {
    if (index <= 0) {
        return;             //przerwanie rekurencji po doj�ciu do korzenia
    }
    int parent = (index - 1) / 2;
    if (tab[index] > tab[parent]) {

        int temp = tab[index];      //
        tab[index] = tab[parent];   //zamiana potomka z rodzicem
        tab[parent] = temp;         //

        heapifyUp(parent); //wywo�anie rekurencyjne
    }
}


void Heap::heapifyDown(int index) {
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    int maximum = index;            //pocz�tkowa inicjalizacja najwi�kszego w�z�a jako rodzica

    if (leftChild < count && tab[leftChild] > tab[maximum]) {  //por�wnanie lewego potomka z rodzicem
        maximum = leftChild;
    }

    if (rightChild < count && tab[rightChild] > tab[maximum]) { //por�wnanie prawego potomka z rodzicem lub lewym dzieckiem (w zale�no�ci czy poprzedni warunek
        maximum = rightChild;                                                                                                               //zosta� spe�niony
    }

    if (maximum != index) {            //przypadek podstawowy gdy dany w�ze� jest na poprawnej pozycji w kopcu
        int temp = tab[index];         //
        tab[index] = tab[maximum];     //zamiana najwi�kszego w�z�a (potomka) z rodzicem
        tab[maximum] = temp;           //
        heapifyDown(maximum);          //wywo�anie rekurencyjne
    }
}

bool Heap::isValueInHeap(int val) {
    for (int i = 0; i < count; i++) {
        if (tab[i] == val) {
            return true;
        }
    }
    return false;
}

void Heap::addValue(int value) {
    tab[count] = value;
    count++;
    heapifyUp(count - 1);
}

void Heap::deleteFromHeap(int value) {
    int index = -1;
    for (int i = 0; i < count; i++) {
        if (tab[i] == value) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        return;
    }
    if (index == count - 1) { //usuwanie ostatniego li�cia
        count--;
        return;
    }

    int temp = tab[index];          //
    tab[index] = tab[count - 1];    //zamiana usuwanego elementu z ostatnim li�ciem
    tab[count - 1] = temp;          //
    count--;

    int parentIndex = (index - 1) / 2;

    if (index == 0 || tab[index] < tab[parentIndex]) {
        heapifyDown(index);
    }
    else {
        heapifyUp(index);
    }
}

void Heap::generateHeap(int sizeParam, int minValue, int maxValue) {
    srand((unsigned int)time(NULL));

    count = sizeParam;

    for (int i = 0; i < count; i++) {
        tab[i] = rand() % (maxValue - minValue + 1) + minValue;
        heapifyUp(i);
    }
}

void Heap::display() {
    cout << '\n';
    for (int i = 0; i < count; i++) {
        cout << tab[i] << " ";
    }
    cout << '\n';
}
////////////////////////////////////////////Wy�wietlanie graficzne kopca///////////////////////////////////////////////////
// Prezentacja drzewa binarnego
// Data: 03.02.2013
// (C)2013 mgr Jerzy Wa�aszek
//------------------------------
// Typ w�z��w drzewa
struct BTNode
{
    BTNode* left;      // lewy syn
    BTNode* right;     // prawy syn
    int data;           // dane w�z�a
};

// Zmienne globalne

int n;                // liczba w�z��w
BTNode* root;        // wskazanie korzenia drzewa
string cr, cl, cp;    // �a�cuchy do ramek

// Procedura inicjuje dane, odczytuje definicj� drzewa
// ze standardowego wej�cia i tworzy jego struktur� w
// pami�ci. Na wyj�ciu w zmiennej root zostaje umieszczony
// adres korzenia drzewa
//--------------------------------------------------------
void readBT(int* tab, int n)
{
    if (n < 1) {
        return;
    }
    BTNode** vp;          // tablica wska�nik�w
    int i, d, l, r;

    /*cin >> n;*/              // odczytujemy liczb� w�z��w drzewa binarnego

    vp = new BTNode * [n]; // tworzymy tablic� dynamiczn� wska�nik�w

    for (i = 0; i < n; i++)
        vp[i] = new BTNode; // tworzymy dynamicznie w�ze�

    for (i = 0; i < n; i++)
    {
        // odczytujemy dane w�z�a i numery syn�w
        d = tab[i];
        l = 2 * i + 1;
        r = 2 * i + 2;
        if (l > n - 1) {
            l = NULL;
        }
        if (r > n - 1) {
            r = NULL;
        }

        vp[i]->data = d;   // wprowadzamy do w�z�a dane

        if (l) vp[i]->left = vp[l]; // ustawiamy lewego syna
        else  vp[i]->left = NULL; // je�li istnieje

        if (r) vp[i]->right = vp[r]; // ustawiamy prawego syna
        else  vp[i]->right = NULL; // je�li istnieje
    }

    root = vp[0];         // zapami�tujemy korze� drzewa

    delete[] vp;           // usuwamy tablic� wska�nik�w

}

// Procedura DFS:postorder usuwaj�ca drzewo
//-----------------------------------------
void DFSRelease(BTNode* v)
{
    if (v)
    {
        DFSRelease(v->left);  // usuwamy lewe poddrzewo
        DFSRelease(v->right); // usuwamy prawe poddrzewo
        delete v;                // usuwamy sam w�ze�
    }
}

// Procedura wypisuje drzewo
//--------------------------
void printBT(string sp, string sn, BTNode* v)
{
    string s;

    if (v)
    {
        s = sp;
        if (sn == cr) s[s.length() - 2] = ' ';
        printBT(s + cp, cr, v->right);

        s = s.substr(0, sp.length() - 2);
        cout << s << sn << v->data << endl;

        s = sp;
        if (sn == cl) s[s.length() - 2] = ' ';
        printBT(s + cp, cl, v->left);
    }
}

// **********************
// *** PROGRAM G��WNY ***
// **********************
void Heap::showHeap() {
    if (count < 1) {
        return;
    }
    cr = cl = cp = "  ";
    cr[0] = 218; cr[1] = 196;
    cl[0] = 192; cl[1] = 196;
    cp[0] = 179;

    readBT(tab, count);            // odczytujemy drzewo
    printBT("", "", root); // wy�wietlamy drzewo
    DFSRelease(root);  // usuwamy drzewo z pami�ci
}
////////////////////////////////////////////Wy�wietlanie graficzne kopca///////////////////////////////////////////////////

void Heap::deleteFromHeapByIndex(int index) {
    if (index < 0 || index >= count) {
        return;
    }
    if (index == count - 1) { // usuwanie ostatniego li�cia
        count--;
        return;
    }

    int temp = tab[index];          //
    tab[index] = tab[count - 1];    // zamiana usuwanego elementu z ostatnim li�ciem
    tab[count - 1] = temp;          //
    count--;

    int parentIndex = (index - 1) / 2;

    if (index == 0 || tab[index] < tab[parentIndex]) {
        heapifyDown(index);
    }
    else {
        heapifyUp(index);
    }
}

void Heap::testHeap(int testSize) {
    cout << "Test dla " << testSize << " danych\n";
    long averageTimeAdd = 0;				//zmienna przechowuj�ca �redni czas dodawania na koniec dla 100 powt�rze� dla r�nych danych
    long averageTimeDelete = 0;		//zmienna przechowuj�ca �redni czas usuwania z ko�ca dla 100 powt�rze� dla r�nych danych
    long averageTimeFindValue = 0;

    int testAmount = 100;               //zmienna przechowuj�ca liczb� powt�rze� testu

    int k = testSize / 20;

    srand((unsigned int)time(NULL));
    for (int j = 0; j < testAmount; j++) {
        generateHeap(testSize, -testSize, testSize);

        long averageAddforKNumbers = 0;
        long averageDeleteforKNumbers = 0;

        //Dodawanie do kopca
        for (int i = 0; i < k; i++) {
            auto TimeStart = chrono::high_resolution_clock::now();
            addValue(rand() % (2 * testSize + 1) - testSize);
            auto TimeEnd = chrono::high_resolution_clock::now();
            averageAddforKNumbers += chrono::duration_cast<chrono::nanoseconds>(TimeEnd - TimeStart).count();
        }
        //Przywr�cenie wielko�ci kopca
        for (int i = 0; i < k; i++) {
            deleteFromHeapByIndex(0);
        }

        //Usuwanie korzenia z kopca
        for (int i = 0; i < k; i++) {
            auto TimeStart = chrono::high_resolution_clock::now();
            deleteFromHeapByIndex(0);
            auto TimeEnd = chrono::high_resolution_clock::now();
            averageDeleteforKNumbers += chrono::duration_cast<chrono::nanoseconds>(TimeEnd - TimeStart).count();
        }

        //Przywr�cenie wielko�ci kopca
        for (int i = 0; i < k; i++) {
            addValue(rand() % (2 * testSize + 1) - testSize);
        }

        //Szukanie warto�ci w kopcu
        auto TimeStart = chrono::high_resolution_clock::now();
        isValueInHeap(rand() % (2 * testSize + 1) - testSize);
        auto TimeEnd = chrono::high_resolution_clock::now();
        averageTimeFindValue += chrono::duration_cast<chrono::nanoseconds>(TimeEnd - TimeStart).count();

        averageAddforKNumbers /= k;
        averageDeleteforKNumbers /= k;

        averageTimeAdd += averageAddforKNumbers;
        averageTimeDelete += averageDeleteforKNumbers;
    }

    averageTimeAdd /= testAmount;
    averageTimeDelete /= testAmount;
    averageTimeFindValue /= testAmount;


    string filePathWithResult = "./Kopiec_czas_" + to_string(testSize) + ".txt";
    ofstream outputFile;

    outputFile.open(filePathWithResult);
    if (!outputFile.is_open()) {
        cout << "couldn't open the file\n";
        return;
    }

    outputFile << "�redni czas dodawania do kopca: " + to_string(averageTimeAdd) + "ns\n";
    outputFile << "�redni czas usuwania z kopca: " + to_string(averageTimeDelete) + "ns\n";
    outputFile << "�redni czas wyszukiwania: " + to_string(averageTimeFindValue) + "ns\n";
    outputFile.close();
}



void displayMenuHeap(string info) {
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

void Heap::menu_heap() {
    Heap* myHeap = new Heap();
    char opt;
    string fileName;
    int value;
    int minVal, maxVal;

    do {
        displayMenuHeap("--- KOPIEC ---");
        opt = _getche();
        cout << endl;
        switch (opt) {
        case '1': //tutaj wczytytwanie kopca z pliku
            cout << "Podaj nazwe zbioru: ";
            cin >> fileName;
            myHeap->loadFromFile(fileName);
            myHeap->showHeap();
            cout << endl;
            myHeap->display();
            cout << endl;
            cout << endl;

            break;

        case '2': //tutaj usuwanie elemenu z kopca
            cout << "Podaj wartosc: ";
            cin >> value;
            myHeap->deleteFromHeap(value);
            myHeap->showHeap();
            cout << endl;
            myHeap->display();
            cout << endl;

            break;

        case '3': //tutaj dodawanie elemetu do kopca
            cout << "Podaj wartosc: ";
            cin >> value;

            myHeap->addValue(value);
            myHeap->showHeap();
            cout << endl;
            myHeap->display();
            cout << endl;

            break;

        case '4': //tutaj znajdowanie elemetu w kopcu
            cout << "Podaj wartosc: ";
            cin >> value;
            if (myHeap->isValueInHeap(value))
                cout << "Podana wartosc jest w kopcu";
            else
                cout << "Podanej wartosci NIE ma w kopcu";
            cout << endl;

            break;

        case '5':  //tutaj generowanie kopca
            cout << "Podaj ilosc elementow kopca: ";
            cin >> value;
            cout << "Podaj minimalna liczbe: ";
            cin >> minVal;
            cout << "Podaj maksymalna liczbe: ";
            cin >> maxVal;
            myHeap->generateHeap(value, minVal, maxVal);
            cout << endl;
            myHeap->showHeap();
            cout << endl;
            myHeap->display();
            cout << endl;

            break;

        case '6':  //tutaj wy�wietlanie kopca
            myHeap->showHeap();
            cout << endl;
            myHeap->display();

            break;

        case '7': //tutaj testowanie kopca
            myHeap->testHeap(5000);
            myHeap->testHeap(8000);
            myHeap->testHeap(10000);
            myHeap->testHeap(16000);
            myHeap->testHeap(20000);
            myHeap->testHeap(40000);
            myHeap->testHeap(60000);
            myHeap->testHeap(100000);

            break;
        }
    } while (opt != '0');
}