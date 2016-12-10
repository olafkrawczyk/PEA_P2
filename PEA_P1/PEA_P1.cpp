// PEA_P1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TSP.h"
#include <ctime>

LARGE_INTEGER startTimer();
LARGE_INTEGER endTimer();

void print_top() {
	std::cout << "############### SA TSP PEA OK 218164 2016 ###############" << std::endl;
}
void print_bottom() {
	std::cout << "#########################################################" << std::endl;
}
void menu_glowne() {
	system("cls");
	
	print_top();
	std::cout << "1. Wczytaj dane z pliku (tsp)" << std::endl;
	std::cout << "2. Wczytaj dane z pliku (atsp)" << std::endl;
	std::cout << "3. Wyswietl parametry" << std::endl;
	std::cout << "4. Zmien parametry" << std::endl;
	std::cout << "5. Uruchom algorytm" << std::endl;
	std::cout << "6. Test algorytmu" << std::endl;
	std::cout << "7. Koniec" << std::endl;
	print_bottom();

}
void wczytaj_dane(TSP* problem, double & T_MAX) {
	system("cls");
	std::string nazwa;

	print_top();
	std::cout << "Dostepne pliki: gr17, gr48, gr120, pa561" << std::endl;
	std::cout << "Podaj nazwe pliku: ";
	std::cin >> nazwa;
	problem->wczytaj_z_pliku(nazwa + ".txt");
	T_MAX = problem->generuj_temp();
	print_bottom();
}
void wczytaj_asym_dane(TSP* problem, double & T_MAX) {
	system("cls");
	std::string nazwa;

	print_top();
	std::cout << "Dostepne pliki: br17, ftv70, ftv170" << std::endl;
	std::cout << "Podaj nazwe pliku: ";
	std::cin >> nazwa;
	problem->wczytaj_asym_z_pliku(nazwa + ".txt");
	T_MAX = problem->generuj_temp();
	print_bottom();
}
void wypisz_parametery(double & T_MAX, double & T_MIN, double & alfa) {
	system("cls");
	print_top();
	std::cout << "Temperatura poczatkowa: " << T_MAX << std::endl;
	std::cout << "Temperatura koncowa: " << T_MIN << std::endl;
	std::cout << "Wsp schladzania: " << alfa << std::endl;
	print_bottom();
}
void zmien_parametery(double & T_MAX, double & T_MIN, double & alfa) {
	system("cls");
	print_top();
	std::cout << "Temperatura poczatkowa(" << T_MAX << "): ";
	std::cin >> T_MAX;
	std::cout << "Temperatura koncowa(" << T_MIN << "): ";
	std::cin >> T_MIN;
	std::cout << "Wsp schladzania(" << alfa << "): ";
	std::cin >> alfa;
	print_bottom();
}
void uruchom_algorytm(TSP * problem, double & T_MAX, double & T_MIN, double & alfa) {
	LARGE_INTEGER performanceCountStart, performanceCountEnd, freq;
	QueryPerformanceFrequency(&freq);
	performanceCountStart = startTimer();
	problem->simulated_annealing(T_MAX, T_MIN, alfa);
	performanceCountEnd = endTimer();					 //zapamiêtujemy koniec czasu
	double tm = (double)(performanceCountEnd.QuadPart - performanceCountStart.QuadPart);
	problem->wypisz_wynik();
	std::cout << "Czas wykonania algorytmu : " << (tm / freq.QuadPart * 100) * 10 << " ms" << std::endl;
}

void generuj_dane(TSP* problem, double alfa, int ilosc_pomiarow, std::string nazwa_pliku) {
	std::fstream plik;
	LARGE_INTEGER performanceCountStart, performanceCountEnd, freq;
	QueryPerformanceFrequency(&freq);
	double tm;
	double** wyniki = new double* [ilosc_pomiarow];

	problem->wczytaj_z_pliku(nazwa_pliku+".txt");
	double T_MAX = problem->generuj_temp();
	double T_MIN = 0.0001;
	
	for (int i = 0; i < ilosc_pomiarow; i++) {
		wyniki[i] = new double[3];
		performanceCountStart = startTimer();
		problem->simulated_annealing(T_MAX, T_MIN, alfa);
		performanceCountEnd = endTimer();
		tm = (double)(performanceCountEnd.QuadPart - performanceCountStart.QuadPart);
		wyniki[i][0] = problem->get_route_val();
		wyniki[i][1] = problem->get_error();
		wyniki[i][2] = (tm / freq.QuadPart * 100) * 10;
	}

	std::string out_name = "wyniki/" + nazwa_pliku + "_" + std::to_string(alfa) + ".csv";
	plik.open(out_name, std::ios::out);

	for (int i = 0; i < ilosc_pomiarow; i++) {
		plik << wyniki[i][0] << ";";
		plik << wyniki[i][1] << ";";
		plik << wyniki[i][2] << ";";
		plik << std::endl;
	}

	plik.close();

}
void generuj_dane_atsp(TSP* problem, double alfa, int ilosc_pomiarow, std::string nazwa_pliku) {
	std::fstream plik;
	LARGE_INTEGER performanceCountStart, performanceCountEnd, freq;
	QueryPerformanceFrequency(&freq);
	double tm;
	double** wyniki = new double*[ilosc_pomiarow];

	problem->wczytaj_asym_z_pliku(nazwa_pliku + ".txt");
	double T_MAX = problem->generuj_temp();
	double T_MIN = 0.0001;

	for (int i = 0; i < ilosc_pomiarow; i++) {
		wyniki[i] = new double[3];
		performanceCountStart = startTimer();
		problem->simulated_annealing(T_MAX, T_MIN, alfa);
		performanceCountEnd = endTimer();
		tm = (double)(performanceCountEnd.QuadPart - performanceCountStart.QuadPart);
		wyniki[i][0] = problem->get_route_val();
		wyniki[i][1] = problem->get_error();
		wyniki[i][2] = (tm / freq.QuadPart * 100) * 10;
	}

	std::string out_name = "wyniki/" + nazwa_pliku + "_" + std::to_string(alfa) + ".csv";
	plik.open(out_name, std::ios::out);

	for (int i = 0; i < ilosc_pomiarow; i++) {
		plik << wyniki[i][0] << ";";
		plik << wyniki[i][1] << ";";
		plik << wyniki[i][2] << ";";
		plik << std::endl;
	}

	plik.close();

}
void make_files(TSP * problem) {
	int ilosc_pomiarow = 30;
	double alfas[] = { 0.85, 0.9, 0.99, 0.999 };
	std::string tsp[] = { "gr17", "gr48", "gr120" };
	std::string atsp[] = { "br17", "ftv70", "ftv170" };

	for (int i = 0; i < 3; i++)
	{
		std::cout << "-------\n\
			plik: " << tsp[i] << std::endl;
		for (int k = 0; k < 4; k++)
		{
			std::cout << "\t\talfa: " << alfas[k] << std::endl << std::endl;
			generuj_dane(problem, alfas[k], ilosc_pomiarow, tsp[i]);
		}
	}

	for (int i = 0; i < 3; i++)
	{
		std::cout << "-------\n\
			plik: " << atsp[i] << std::endl;
		for (int k = 0; k < 4; k++)
		{
			std::cout << "\t\talfa: " << alfas[k] << std::endl << std::endl;
			generuj_dane_atsp(problem, alfas[k], ilosc_pomiarow, atsp[i]);
		}
	}
}

int main()
{
	srand(time(NULL));
	TSP *problem = new TSP();
	double T_MAX;
	double T_MIN = 0.0001;
	double alfa = 0.999;
	char k = 'z';

	while (k != '7')
	{
		switch (k)
		{
		case '1':
			wczytaj_dane(problem, T_MAX);
			system("pause");
			k = 'z';
			break;
		case '2':
			wczytaj_asym_dane(problem, T_MAX);
			system("pause");
			k = 'z';
			break;
		case '3':
			wypisz_parametery(T_MAX, T_MIN, alfa);
			system("pause");
			k = 'z';
			break;
		case '4':
			zmien_parametery(T_MAX, T_MIN, alfa);
			system("pause");
			k = 'z';
			break;
		case '5':
			uruchom_algorytm(problem, T_MAX, T_MIN, alfa);
			system("pause");
			k = 'z';
			break;
		case '6':
			int times;
			std::cout << "Ilosc powtorzen: ";
			std::cin >> times;
			for (int i = 0; i < times; i++)
			{
				std::cout << "##" << i << std::endl;
				uruchom_algorytm(problem, T_MAX, T_MIN, alfa);
				std::cout << std::endl;
			}
			system("pause");
			k = 'z';
			break;
		default:
			menu_glowne();
			std::cout << ">";
			k = getchar();
			break;
		}
	}
	/*
	menu_glowne();
	wczytaj_dane(problem, T_MAX);

	wypisz_parametery(T_MAX, T_MIN, alfa);
	for (int i = 0; i < 100; i++)
	{
		problem->simulated_annealing(T_MAX, T_MIN, alfa);
		problem->wypisz_wynik();
	}
	*/
	std::cout << std::endl;
	system("pause");
    return 0;
}

LARGE_INTEGER startTimer()											//funkcje mierzace czas
{
	LARGE_INTEGER start;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&start);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return start;
}

LARGE_INTEGER endTimer()
{
	LARGE_INTEGER stop;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&stop);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return stop;
}