#pragma once


class TabuList
{
private:
	struct Move {
		int from;
		int to;

		bool operator== (const Move &c1) {
			return (from == c1.from && to == c1.to);
		}
	};
	int size;
	int begin;
	Move* tabu_list;
	
public:
	
	TabuList();
	TabuList(int size);
	void Add(Move);
	bool onTabu(Move);
	~TabuList();
};

