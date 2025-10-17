#ifndef MATMA_H
#define MATMA_H

#pragma once
/*
Wszytkie matematyczne narzedzia/wzory potrzebne do zadan:
- iloczyn wektorowy 3 punktow (w zaleznosci od jego wartosci mozna sie dowiedziec czy punkt C jest na prostej AB, i jesli nie to po ktorej stronie)
- wszystkie punkty po lewej stronie odcinka (patrzac od A do B, w oparciu o iloczyn wektorowy)
- odleglosc odcinka AB do punktu C
- odleglosc punktu A do punktu B
- znalezienie punktu, ktory jest najbardziej oddalony od odcinka AB
- funkcja identyczna do poprzedniej, zwraca odleglosc zamiast punktu
*/
#include <vector>
#include "Punkt.h"

using namespace std;

double iloczynWektorowy(Punkt& A, Punkt& B, Punkt& C);
vector<Punkt> punktyPoLewej(vector<Punkt>&punkty, Punkt& A, Punkt& B);
double dPunktuOdOdcinka(Punkt& A, Punkt& B, Punkt& C);
double dDwochPunktow(Punkt& A, Punkt& B);
Punkt najdalszyOdOdcinka(vector<Punkt>punkty, Punkt& A, Punkt& B);
double dNajdalszegoPunktuOdOdcinka(vector<Punkt>&punkty, Punkt& A, Punkt& B);

#endif