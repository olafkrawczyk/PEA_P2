#pragma once
struct Move {
	int from;
	int to;

	Move() {
		from = -1;
		to = -1;
	}
	Move(int i, int j) {
		from = i;
		to = j;
	}
	bool operator== (const Move &c1) {
		bool t1 = (from == c1.from && to == c1.to);
		bool t2 = (from == c1.to && to == c1.from);
		bool result = t1 || t2;
		return result;
	}
};

class TabuList
{
	
private:
	
	int size;
	int begin;
	Move* tabu_list;
	
public:
	
	TabuList();
	TabuList(int size);
	void Add(Move);
	bool onTabu(Move);
	void clearTabu();
	~TabuList();
};

