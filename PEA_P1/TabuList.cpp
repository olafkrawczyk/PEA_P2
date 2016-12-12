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
	if (begin = size - 1)
		begin = 0;
	tabu_list[begin++] = m;
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



TabuList::~TabuList()
{
	delete[] tabu_list;
}
