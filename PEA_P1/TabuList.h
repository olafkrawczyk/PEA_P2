#pragma once

class TabuList
{
private:
	struct Move {
		int cadence = 0;
		int usages_cnt = 0;
	};
	int size;
	Move **tabu_list;
	int max_cadence;
	int horizon;
public:
	
	TabuList();
	TabuList(int size, int max_cadence, int horizon);
	void addMove(int start, int end);
	void decrementCadence();
	void checkHorizon();
	bool moveIsAvailable(int start, int end);
	int getCadecny(int, int);
	void resetTabuList();
	~TabuList();
};

