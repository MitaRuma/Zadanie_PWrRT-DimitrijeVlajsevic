#include "Zadania.h"
#include "Matma.h"
#include "Sortowanie.h"

#include <vector>
#include <cfloat>
#include <cmath>


vector<Punkt> znajdzOtoczke(vector<Punkt>& punkty) {

	//jesli sa max 2 punkty to one same tworza otoczke, nie ma co dalej liczyc
	if (punkty.size() < 3)
		return punkty;

	vector<Punkt>Otoczka;

	Punkt A = punkty[0];
	Punkt B = punkty[punkty.size() - 1];

	//dzelenie punktow na te po prawej oraz po lewej odcinka AB
	vector<Punkt>obszarL = punktyPoLewej(punkty, A, B);
	vector<Punkt>obszarR = punktyPoLewej(punkty, B, A);

	Otoczka.push_back(A);	
	rekurencjaOtoczka(Otoczka, obszarL, A, B);
	Otoczka.push_back(B);
	rekurencjaOtoczka(Otoczka, obszarR, B, A);

	//na wszelki wypadek sortowanie punktow w otoczce (na potrzeby zadania 2)
	punktySortAntyzegarowo(Otoczka);

	return Otoczka;
}

void rekurencjaOtoczka(vector<Punkt>& Otoczka, vector<Punkt>& punkty, Punkt& A, Punkt& B) {

	//Divide&Conquer
	
	if (punkty.empty())
		return;

	Punkt C = najdalszyOdOdcinka(punkty, A, B); // ten punkt na pewno jest czescia otoczki

	//dzielimy punkty dalej
	vector<Punkt> lewo = punktyPoLewej(punkty, A, C);
	vector<Punkt> prawo = punktyPoLewej(punkty, C, B);

	//rekurencyjnie lecimy dalej
	rekurencjaOtoczka(Otoczka, lewo, A, C);
	Otoczka.push_back(C);
	rekurencjaOtoczka(Otoczka, prawo, C, B);

	return;
}

double najblizszeProste(vector<Punkt>& otoczka) {

	//jesli sa tylko 2 punkty, sa kolinearne wiec wystarczy 1 prosta do zawarcia wszystkich punktow => d=0
	if (otoczka.size() == 2)
		return 0;

	//patrzymy na kazda sasiadujaca pare w otoczce (dlatego wazne sortowanie cyklicznie), i sprawdzamy odleglosc do najdalszego punktu
	//najmniejsza taka odleglosc to rozwiazanie zadania
	double dMin = dNajdalszegoPunktuOdOdcinka(otoczka, otoczka[0], otoczka[otoczka.size() - 1]);
	double d;

	for (int i = 0; i < otoczka.size() - 1; i++) {
		d = dNajdalszegoPunktuOdOdcinka(otoczka, otoczka[i], otoczka[i + 1]);
		if (d < dMin)
			dMin = d;
	}

	return dMin;
}

vector<Punkt> najblizszePunktyBruteforce(vector<Punkt>& punkty) {

	//bruteforce najblizszych punktow w zbiorze
	vector<Punkt> min;

	//jesli w wektorze punkty jest 0 lub 1 punkt, nie da sie znalesc najmniejszej odleglosci, zwracany jest pusty wektor
	//taki przypadek dalej ogarniety w glownej funkcji
	if (punkty.size() <= 1)
		return min;

	double dMin = DBL_MAX;
	for (int i = 0; i < punkty.size(); i++)
		for (int j = i + 1; j < punkty.size(); j++)
			if (dDwochPunktow(punkty[i], punkty[j]) < dMin) {
				dMin = dDwochPunktow(punkty[i], punkty[j]);
				min = { punkty[i], punkty[j] };
			}
	return min;
}

vector<Punkt> najblizszePunkty(vector<Punkt>& punktyX, vector<Punkt>& punktyY) {

	//Divide&Conquer

	int n = punktyX.size(); // = punktyY.size()

	//jesli malo punktow to mozna brute force
	if (n <= 3)
		return najblizszePunktyBruteforce(punktyX);

	double srodekX = punktyX[n / 2].x; //srodkowy punkt w tablicy

	//dzielimy punkty na prawo i lewo od srodkowego
	vector<Punkt>punktyLewoX, punktyPrawoX;
	for (int i = 0; i < n; i++) {
		if (punktyX[i].x <= srodekX)
			punktyLewoX.push_back(punktyX[i]);
		else
			punktyPrawoX.push_back(punktyX[i]);
	}
	if (punktyLewoX.empty() || punktyPrawoX.empty()) //jesli funkcja bruteforce zwraca pusty wektor
		return najblizszePunktyBruteforce(punktyX);

	//sortowane podzielonych wektorow wg wartosci Y
	vector<Punkt>punktyLewoY = punktyLewoX;
	punktySortY(punktyLewoY);
	vector<Punkt>punktyPrawoY = punktyPrawoX;
	punktySortY(punktyPrawoY);

	//rekurencja
	vector<Punkt> Lewo = najblizszePunkty(punktyLewoX, punktyLewoY);
	vector<Punkt> Prawo = najblizszePunkty(punktyPrawoX, punktyPrawoY);

	//obliczenie minimalnych odleglosci w lewym i prawym przedziale
	double dL = (Lewo.size() >= 2) ? dDwochPunktow(Lewo[0], Lewo[1]) : DBL_MAX;
	double dR = (Prawo.size() >= 2) ? dDwochPunktow(Prawo[0], Prawo[1]) : DBL_MAX;

	//ktory jest mniejszy minimum? po lewej czy prawej?
	vector<Punkt> dMinPara = (dL < dR) ? Lewo : Prawo;
	double d = min(dL, dR);

	//=dMinPara gdyby w ostatecznym przedziale srodkowym nie bylo blizszej pary punktow (vector zostalby pusty)
	vector<Punkt>odpowiedz = dMinPara;
	double dKoncowe = d;

	//przedzial srodkowy, gdzie sa tylko punkty oddalone od srodka maksymalnie o obecna odleglosc minimalna
	vector<Punkt>przedzial;
	for (int i = 0; i < n; i++) {
		if (fabs(punktyY[i].x - srodekX) < d)
			przedzial.push_back(punktyY[i]);
	}

	//sprawdzanie tego ostatecznego przedzialu
	double dist = 0;
	for (int i = 0; i < przedzial.size(); i++) {
		//sprawdzamy tylko 7 najblizszych sasiadow tego punktu, bo te dalsze maja d>dMin na pewno
		for (int j = i + 1; j < przedzial.size() && j <= i + 7; j++) {

			dist = dDwochPunktow(przedzial[i], przedzial[j]);

			if (dist < dKoncowe) {
				odpowiedz = { przedzial[i], przedzial[j] };
				dKoncowe = dist;
			}

		}
	}

	return odpowiedz;
}