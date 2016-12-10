#pragma once
class Trasa
{
	int *trasa;
	float koszt;
	int dlugosc;

public:
	int* get_route();
	void swap(int a, int b);
	void losuj_permutacje();
	void wybierz_w_otoczeniu(Trasa*);
	Trasa(int in_dlugosc);
	Trasa(int *in_trasa, int dlugosc);
	void set_route(Trasa*);
	~Trasa();

};

