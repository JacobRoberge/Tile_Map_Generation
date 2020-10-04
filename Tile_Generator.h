#pragma once
#include <vector>

using namespace std;
class Tile_Generator
{
private:
	enum NodeState {white,grey, black};
	enum TileShape
	{
		VerticalHall, HorizontalHall, BotLeftCorner, BotRightCorner,
		TopLeftCorner, TopRightCorner, VertTopT, VertBotT,
		HorzLeftT, HorzRightT, TopWall, BotWall, LeftWall, RightWall
	};
	enum directions{north,east,south,west,northeast,southeast,southwest,northwest,none};
	enum TileType
	{
		Caverns
	};
	struct seed
	{
		seed(int x,int y)
		{
			this->x = x;
			this->y = y;
		}
		int x, y;
		char id;
	};
	struct node
	{
		int x, y;
		char id = 'O';
		bool classified = false;
		bool inStack = false;
		bool isCorner = false;
		TileShape shape;
		TileType type;
		
		//bool 
	};
	vector<vector<node*>> map;
	vector<seed*> seeds;
	vector<int> tester;
	int width, height;
	
	
public:
	Tile_Generator(int width, int height, int NumSeeds);
	bool Seed_Propagate(int counter);
	bool Seed_Propagate_v2(int counter);
	bool Check_Location(char id, int x, int y);
	void Show_Result();
	void Clean_Pathways();
	void Classify_Tile(int x, int y);
	void DFS_Classify();
	
	
	
	
};

