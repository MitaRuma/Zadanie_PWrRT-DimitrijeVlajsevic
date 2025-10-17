#include "Sortowanie.h"

#include <iostream>
#include <algorithm>

using namespace std;

//sort rosnaco wg X
void punktySortX(vector<Punkt>& punkty) {
	sort(punkty.begin(), punkty.end(), [](Punkt& a, Punkt& b) {return a.x < b.x; });
	return;
}

//sort rosnaco wg Y
void punktySortY(vector<Punkt>& punkty) {
	sort(punkty.begin(), punkty.end(), [](Punkt& a, Punkt& b) {return a.y < b.y; });
	return;
}

//sort otoczke po kolei
void punktySortAntyzegarowo(vector<Punkt>& punkty) {

	double x = 0, y = 0;
	for (int i = 0; i < punkty.size(); i++) {
		x += punkty[i].x;
		y += punkty[i].y;
	}
	x /= punkty.size();
	y /= punkty.size();

	sort(punkty.begin(), punkty.end(), [x, y](Punkt& A, Punkt& B) {

		double katA = atan2(A.y - y, A.x - x);
		double katB = atan2(B.y - y, B.x - x);
		return katA < katB;
	});
}

//drukowanie
void printf(vector<Punkt> punkty) {
	for (int i = 0; i < punkty.size(); i++) {
		cout << "(" << punkty[i].x << ", " << punkty[i].y << ") ";
	}
}