#include "stdafx.h"
#include "TabuList.h"


TabuList::TabuList()
{
}

TabuList::TabuList(int size)
{
	this->size = size;
	begin = 0;
	tabu_list = new Move[size];
}

void TabuList::Add(Move m)
{
	tabu_list[begin++] = m;
	if (begin == size)
		begin = 0;
}

bool TabuList::onTabu(Move m)
{
	for (int i = 0; i < size; i++)
	{
		if (m == tabu_list[i])
			return true;
	}
	return false;
}

void TabuList::clearTabu()
{
	for (int i = 0; i < size; i++)
	{
		tabu_list[i].from = -1;
		tabu_list[i].to = -1;

	}
}


TabuList::~TabuList()
{
	delete[] tabu_list;
}
