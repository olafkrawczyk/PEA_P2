#include "stdafx.h"
#include "Trasa.h"

Trasa::Trasa(int in_dlugosc) {
	trasa = new int[in_dlugosc];
	dlugosc = in_dlugosc;
	for (size_t i = 0; i < in_dlugosc; i++)
	{
		trasa[i] = i;
	}
}

Trasa::Trasa(int *in_trasa, int in_dlugosc)
{
	dlugosc = in_dlugosc;
	trasa = in_trasa;
}

void Trasa::set_route(Trasa * in_trasa)
{
	int *copy_route = in_trasa->get_route();
	for (int i = 0; i < dlugosc; i++)
	{
		trasa[i] = copy_route[i];
	}
}


Trasa::~Trasa()
{
	delete[] trasa;
}

void Trasa::wybierz_w_otoczeniu(Trasa* in_route)
{
	int* route = in_route->get_route();

	int a = rand() % dlugosc;
	int b = rand() % dlugosc;
	while (a == b) {
		b = rand() % dlugosc;
	}

	int * swapped = new int[dlugosc];
	for (int i = 0; i < dlugosc; i++)
	{
		swapped[i] = route[i];
	}

	int temp = swapped[a];
	swapped[a] = swapped[b];
	swapped[b] = temp;
	
	delete[] trasa;
	trasa = swapped;
}



void Trasa::losuj_permutacje()
{
	int r_index = 0;
	for (int i = 0; i < dlugosc; i++)
	{
		trasa[i] = i;
	}
	for (int i = 0; i < dlugosc; i++)
	{
		r_index = rand() % dlugosc;
		swap(i, r_index);
	}
}

int * Trasa::get_route()
{
	return trasa;
}

void Trasa::swap(int a, int b) {
	int temp = trasa[a];
	trasa[a] = trasa[b];
	trasa[b] = temp;
}