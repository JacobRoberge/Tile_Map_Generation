#pragma once

#pragma once
#include <vector>

using namespace std;
class Tile_Generator_V2
{
private:
	enum NodeState { white, grey, black };
	struct seed
	{
		seed(int x, int y)
		{
			this->x = x;
			this->y = y;
		}
		int x, y;
		char id;
	};
	struct node
	{
		char id = 'O';
	};
	vector<vector<node*>> map;
	vector<seed*> seeds;
	vector<int> tester;
	int width, height;
public:
	Tile_Generator_V2(int width, int height, int NumSeeds);
	bool Seed_Propagate(int counter);
	void Show_Result();
	void Clean_Pathways();
	void Classify_Tiles();



};



