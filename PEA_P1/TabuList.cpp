#include "stdafx.h"
#include "TabuList.h"


TabuList::TabuList()
{
}

TabuList::TabuList(int size, int max_cadence, int horizon)
{
	this->size = size;
	this->horizon = horizon;
	this->max_cadence = max_cadence;

	tabu_list = new Move*[size];
	for (int i = 0; i < size; i++)
	{
		tabu_list[i] = new Move[size];
		for (int k = 0; k < size; k++)
		{
			tabu_list[i][k].cadence = 0;
			tabu_list[i][k].usages_cnt = 0;
		}
	}
}

void TabuList::addMove(int start, int end)
{
	tabu_list[start][end].usages_cnt++;
	tabu_list[end][start].usages_cnt++;
	tabu_list[start][end].cadence = max_cadence;
	tabu_list[end][start].cadence = max_cadence;
}

void TabuList::decrementCadence()
{
	for (int i = 0; i < size; i++)
	{
		for (int k = 0; k < size; k++)
		{
			if (tabu_list[i][k].cadence != 0) {
				tabu_list[i][k].cadence--;
			}
		}
	}
}



void TabuList::checkHorizon()
{
	for (int i = 0; i < size; i++)
	{
		for (int k = 0; k < size; k++)
		{
			if (tabu_list[i][k].usages_cnt >= horizon) {
				tabu_list[i][k].usages_cnt = 0;
			}
		}
	}
}

bool TabuList::moveIsAvailable(int start, int end)
{
	return tabu_list[start][end].cadence != 0;
}

int TabuList::getCadecny(int i, int k)
{
	int cad = tabu_list[i][k].cadence;
	return cad;
}


void TabuList::resetTabuList()
{
	for (int i = 0; i < size; i++)
	{
		for (int k = 0; k < size; k++)
		{
				tabu_list[i][k].cadence = 0;
				tabu_list[i][k].usages_cnt = 0;
		}
	}
}

TabuList::~TabuList()
{
	for (int i = 0; i < size; i++)
	{
		delete[] tabu_list[i];
	}
	delete tabu_list;
}
