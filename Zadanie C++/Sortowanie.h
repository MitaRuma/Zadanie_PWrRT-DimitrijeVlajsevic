#ifndef SORTOWANIE_H
#define SORTOWANIE_H

#pragma once

/*
Funkcje sortowania zbiorow punktow:
- rosnaco wg X
- rosnaco wg Y
- antyzegarowo wzgledem poczatku ukladu wspolrzednych (po to, zeby sie upewnic ze wyjscie z zadania 1 mozna latwo uzyc jako wejscie do zadania 2)
.
Tutaj jeszcze funkcja ladnego drukowania punktow (bo czemu nie)
*/

#include <vector>
#include "Punkt.h"
using namespace std;

void punktySortX(vector<Punkt>&punkty);
void punktySortY(vector<Punkt>&punkty);
void punktySortAntyzegarowo(vector<Punkt>& punkty);
void printf(vector<Punkt> punkty);

#endif