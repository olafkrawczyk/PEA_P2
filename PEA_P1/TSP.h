#pragma once
#include <fstream>
#include "Trasa.h"
#include "TabuList.h"

class TSP
{
private:
	
	int **miasta;
	double best_route_val = 0;
	Trasa* solution;
	double optimal;
	double blad;
public:
	int liczba_miast;
	void wczytaj_z_pliku(std::string nazwa);
	void wczytaj_asym_z_pliku(std::string nazwa);
	double dl_trasy(int trasa[]);
	void print_best_route();
	void simulated_annealing(double T_MAX, double T_MIN, double alfa);
	
	bool accept_worse(double, double, double);
	double generuj_temp();
	void wypisz_wynik();
	double get_error();
	double get_route_val();

	void tabu_search(int);
	Trasa* getBestNearestSolution(Trasa*);

	TSP();
	~TSP();
};

