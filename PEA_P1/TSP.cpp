#include "stdafx.h"
#include "TSP.h"
#include <omp.h>


double TSP::get_route_val()
{
	return best_route_val;
}

TSP::TSP()
{
}


TSP::~TSP()
{
}

void TSP::wczytaj_z_pliku(std::string nazwa_pliku) {
	std::ifstream plik(nazwa_pliku, std::ios::in);
	plik >> liczba_miast;
	plik >> optimal;
	std::cout << "Wczytano: " << nazwa_pliku << std::endl;
	std::cout << "Liczba miast: " << liczba_miast << std::endl;
	std::cout << "Najlepsze znane: " << optimal << std::endl;
	solution = new Trasa(liczba_miast);

	miasta = new int*[liczba_miast];
	
	for (int i = 0; i < liczba_miast; i++)
	{
		miasta[i] = new int[liczba_miast];
		for (int k = 0; k < liczba_miast; k++)
		{
			plik >> miasta[i][k];
			if (miasta[i][k] == 0)
				break;
			miasta[k][i] = miasta[i][k];
		}
	}
	plik.close();
}

void TSP::wczytaj_asym_z_pliku(std::string nazwa)
{
	std::ifstream plik(nazwa, std::ios::in);
	plik >> liczba_miast;
	plik >> optimal;
	std::cout << "Wczytano: " << nazwa << std::endl;
	std::cout << "Liczba miast: " << liczba_miast << std::endl;
	std::cout << "Najlepsze znane: " << optimal << std::endl;
	solution = new Trasa(liczba_miast);

	miasta = new int*[liczba_miast];

	for (int i = 0; i < liczba_miast; i++)
	{
		miasta[i] = new int[liczba_miast];
		for (int k = 0; k < liczba_miast; k++)
		{
			plik >> miasta[i][k];
		}
	}
	plik.close();
}

/*void TSP::brute_force(int v[], int k, int len) {
	if (k == 0) {
		int curr_route = dl_trasy(v);
		if (curr_route < best_route_val) {
			best_route_val = curr_route;
			std::copy(v, v+len, stdext::checked_array_iterator<int*>(best_route, len));
		}
	}
	else {
		for (int i = 0; i < k; i++)
		{
			swap(v, i, k - 1);
			brute_force(v, k - 1, len);
			swap(v, i, k - 1);
		}
	}
}*/

double TSP::dl_trasy(int trasa[])
{
	double curr_route = 0;
	for (int i = 0; i < liczba_miast-1; i++)
	{
		curr_route += miasta[trasa[i]][trasa[i + 1]];
	}
	curr_route += miasta[trasa[0]][trasa[liczba_miast - 1]];
	return curr_route;
}

void TSP::print_best_route()
{
	
	std::cout << "koszt: " << dl_trasy(solution->get_route()) << std::endl;

}

void TSP::simulated_annealing(double T_MAX, double T_MIN, double alfa)
{
	double new_val;
	double curr_val;
	double T = T_MAX;
	Trasa* best_temp = new Trasa(liczba_miast);
	best_temp->losuj_permutacje();
	solution->set_route(best_temp);
	double solution_val = dl_trasy(solution->get_route());

	do {
		for (int i = 0; i < liczba_miast; i++)
		{
			Trasa *new_route = new Trasa(liczba_miast);
			new_route->wybierz_w_otoczeniu(best_temp);

			new_val = dl_trasy(new_route->get_route());
			curr_val = dl_trasy(best_temp->get_route());
			solution_val = dl_trasy(solution->get_route());

			if (new_val < solution_val) {
				solution->set_route(new_route);
			}
		
			if (new_val < curr_val){
				best_temp->set_route(new_route);
			}
			else if (accept_worse(new_val, curr_val, T)) {
				best_temp->set_route(new_route);
			}
			delete new_route;
		}

		T *= alfa;

		
	} while (T > T_MIN);

	best_route_val = dl_trasy(solution->get_route());
	blad = (best_route_val - optimal)*100 / optimal;
}

Trasa* TSP::getBestNearestSolution(Trasa * trasa_)
{	
	Trasa * local_best = new Trasa(liczba_miast);
	local_best->set_route(trasa_);
	Trasa * local_tmp = new Trasa(liczba_miast);
	local_best->set_route(trasa_);

	for (int i = 0; i < liczba_miast-2; i++)
	{
		for (int k = i; k < liczba_miast; k++)
		{
			local_tmp->swap(i, k);
			if (dl_trasy(local_tmp->get_route()) < dl_trasy(local_best->get_route()))
			{
				local_best->set_route(local_tmp);
			}
			local_tmp->swap(i, k);
		}
	}
	return local_best;
}

void TSP::tabu_search(int MAX_TRIES)
{
	Trasa *best = new Trasa(liczba_miast);
	Trasa *tmp;
	for (int i = 0; i < MAX_TRIES; i++)
	{
		tmp = getBestNearestSolution(best);
		if (dl_trasy(tmp->get_route()) < dl_trasy(best->get_route())) {
			delete best;
			best = tmp;
		}
	}

	best_route_val = dl_trasy(best->get_route());
	blad = (best_route_val - optimal) * 100 / optimal;
	wypisz_wynik();
}

double TSP::generuj_temp() {
	double delta;
	double max_route;
	double min_route;
	Trasa* best_temp = new Trasa(liczba_miast);
	best_temp->losuj_permutacje();
	solution->wybierz_w_otoczeniu(best_temp);

	int liczba_iteracji = (int)pow(liczba_miast, 2);

	max_route = dl_trasy(solution->get_route());
	min_route = dl_trasy(solution->get_route());

	for (int i = 0; i < liczba_iteracji; i++)
	{
		Trasa *new_route = new Trasa(liczba_miast);
		new_route->wybierz_w_otoczeniu(solution);
		double new_val = dl_trasy(new_route->get_route());
		
		if (new_val > max_route)
			max_route = new_val;
		if (new_val < min_route)
			min_route = new_val;

		delete solution;
		solution = new_route;
	}

	delta = max_route - min_route;
	double t_0 = -delta*log(0.9) * 10;
	
	std::cout << "T_0 = " << t_0 << std::endl;

	return t_0;
}

void TSP::wypisz_wynik()
{
	std::cout << "Najlepsze: " << optimal << std::endl;
	std::cout << "Wynik: " << best_route_val << std::endl;
	std::cout << "Blad: " << blad << "%" << std::endl;
}

double TSP::get_error()
{
	return blad;
}

bool TSP::accept_worse(double new_val, double old_val, double temperature)
{
	double e = 2.7182818284;
	double power = (-1*(new_val - old_val)) / temperature;
	double accept = pow(e, power);
	double random = (double)rand() / (double)((unsigned)RAND_MAX + 1);

	return random < accept;
}
