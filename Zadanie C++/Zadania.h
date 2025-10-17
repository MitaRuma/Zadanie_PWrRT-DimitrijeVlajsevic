#ifndef ZADANIA_H
#define ZADANIA_H

#pragma once
/*
Funkcje do zadan:
- Znalezienie otoczki [ZADANIE 1]
- Funcja pomocnicza to znalezienia otoczki
- Znalezienie najmniejszej odleglosci pomiedzy 2 prostymi zawierajacymi wszystkie punkty [ZADANIE 2]
- Znalezienie 2 najmniej oddalonych punktow [ZADANIE 3]
- F. pomocnicza do poprzedniej. Bruteforce znalezienia najblizszych punktow (gdy nie warto wchodzic w rekurencje bo punktow jest malo)
*/
#include <vector>
#include "Punkt.h"

using namespace std;

vector<Punkt> znajdzOtoczke(vector<Punkt>& punkty);
void rekurencjaOtoczka(vector<Punkt>& Otoczka, vector<Punkt>& punkty, Punkt& A, Punkt& B);
double najblizszeProste(vector<Punkt>& Otoczka);
vector<Punkt> najblizszePunkty(vector<Punkt>& punktyX, vector<Punkt>& punktyY);
vector<Punkt> najblizszePunktyBruteforce(vector<Punkt>& punkty);
#endif