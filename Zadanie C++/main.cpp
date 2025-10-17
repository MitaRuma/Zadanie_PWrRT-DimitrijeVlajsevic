//DIMITRIJE VLAJSEVIĆ
//2025

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Matma.h"
#include "Sortowanie.h"
#include "Zadania.h"

using namespace std;

int main() {

    //otwarcie pliku z punktami
    string nazwaPliku = "";
    int N = 0;

    cout << "Podaj nazwe pliku wejsciowego (z .txt): ";
    cin >> nazwaPliku;
    ifstream plik(nazwaPliku);

    if (!plik.is_open()){
        cout << "\nBledna nazwa pliku!\n";
        return 0;
    }

    plik >> N;

    if (N < 2)
        /*
        potrzebujemy conajmniej 2 punkty zeby zrobic zadania:
        jesli punktow jest 0 to lipa
        jesli jest tylko 1: on sam jest otoczka, d = 0 (i prostych jest nieskonczenie wiele), nie ma drugiego najblizszego punktu
        jesli jakims cudem N<0 to dopiero bajzel jest
        */
        cout << "\nJest za malo punktow zeby zrobic zadania :(\n";
    else {

        //jesli sa conajmniej 2 punkty wczytaj reszte pliku
        vector<Punkt>punkty = {};
        punkty.resize(N);

        for (int i = 0; i < N; i++) {
            plik >> punkty[i].x >> punkty[i].y;
        }
        plik.close();

        //sortowanie od razu zeby ich nie sortowac pozniej w kazdej rekurencji
        punktySortX(punkty);
        vector<Punkt>posortowaneX = punkty;
        punktySortY(punkty);
        vector<Punkt>posortowaneY = punkty;

        //zadanie 1 - otoczka
        vector<Punkt>zad1 = znajdzOtoczke(posortowaneX);
        cout << "\nOtoczka: ";
        printf(zad1);

        //zadanie 2 - proste (bierzemy otoczke z zadania 1 jako zbior punktow do zadania 2, bo w otoczce sie zawiera kazdy inny punkt)
        cout << "\nProste: " << najblizszeProste(zad1);
        
        //zadanie 3 - najblizsze punkty
        vector<Punkt> zad3 = najblizszePunkty(posortowaneX, posortowaneY);
        cout << "\nNajblizsze punkty: ";
        printf(zad3);
        cout << ", d = " << dDwochPunktow(zad3[1], zad3[0]) << '\n';

    }

    return 0;

}
