#include "Matma.h"

#include <cmath>

using namespace std;

double iloczynWektorowy(Punkt&A, Punkt&B, Punkt&C) {

	double wynik = (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
	return wynik;
}

//okreslenie czy punkt C jest po lewej odcinka AB na podstawie iloczynu wektorowego tych 3 punktow
vector<Punkt> punktyPoLewej(vector<Punkt>&punkty, Punkt& A, Punkt& B) {
	
	vector<Punkt>poLewej = {};

	for (int i = 0; i < punkty.size(); i++) {
		if (iloczynWektorowy(A, B, punkty[i]) > 0){
			poLewej.push_back(punkty[i]);
		}
	}
	return poLewej;
}

//d punktu C od odcinka AB
double dPunktuOdOdcinka(Punkt& A, Punkt& B, Punkt& C){

	double d = abs((B.x - A.x) * (A.y - C.y) - (A.x - C.x) * (B.y - A.y)) / sqrt( pow((B.x - A.x),2) + pow((B.y - A.y),2) );
	return d;
}

double dDwochPunktow(Punkt& A, Punkt& B){

	double d = sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));
	return d;
}

//punkt w "punkty" najdalszy od AB
Punkt najdalszyOdOdcinka(vector<Punkt>punkty, Punkt& A, Punkt& B) {
	
	Punkt najdalszy = A;
	double dMax = -1;

	for (int i = 0; i < punkty.size(); i++) {
		double d = dPunktuOdOdcinka(A, B, punkty[i]);
		if (d > dMax) {
			dMax = d;
			najdalszy = punkty[i];
		}
	}

	return najdalszy;
}

//d punktu w "punkty" najdalszego od AB
double dNajdalszegoPunktuOdOdcinka(vector<Punkt>&punkty, Punkt& A, Punkt& B) {

	Punkt najdalszy = najdalszyOdOdcinka(punkty, A, B);
	double d = dPunktuOdOdcinka(A, B, najdalszy);
	return d;

}