#include "Tile_Generator.h"
#include <random>
#include <iostream>


Tile_Generator::Tile_Generator(int width, int height, int NumSeeds)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> RandNumX(width, width*2 -1);
	uniform_int_distribution<> RandNumY(height, height*2 -1);

	node* test = new node;
	
	map.resize(width * 3, vector<node*>(height * 3));
	for (int x = 0; x < width * 3 - 1; x++)
	{
		for (int y = 0; y < height * 3 - 1; y++)
		{
			map[x][y] = new node;
			map[x][y]->x = x;
			map[x][y]->y = y;

		}
	}
	this->width = width;
	this->height = height;

	vector<int> vec;
	vec.push_back(1);
	for (int i = 97; i < NumSeeds+97; i++)
	{
		int x = RandNumX(gen);
		int y = RandNumY(gen);
		seed* test = new seed(x,y);
		char id = char(i);
		//id = 'F';
		test->id = id;
		seeds.push_back(test);

		cout << endl <<"ID IS: " << id << endl;

		//initialize around seed
		// map[x + 1][y + 1]->id = id;
		// map[x + 1][y]->id = id;
		// map[x + 1][y - 1]->id = id;
		// map[x - 1][y + 1]->id = id;
		// map[x - 1][y]->id = id;
		// map[x - 1][y -1]->id = id;
		// map[x][y + 1]->id = id;
		// map[x][y - 1]->id = id;

		map[x][y]->id = id;

		
	}
	bool is_finished_propagating = false;
	int counter = 1;
	while(!is_finished_propagating && counter < width-1)
	{
		is_finished_propagating = Seed_Propagate_v2(counter);
		counter++;
		cout << endl;
	}
	Show_Result();

	

	
	

	
}

bool Tile_Generator::Seed_Propagate(int counter)
{
	bool finished;
	if(seeds.empty())
	{
		return true;
	}
	for (int i = 0; i < seeds.size(); i++)
	{
		finished = true;
		char id = seeds[i]->id;
		for (int x = seeds[i]->x - counter + 1; x < seeds[i]->x + counter; x++)
		{
			//TOP
			if (map[x][seeds[i]->y + counter]->id == id)
			{
				map[x][seeds[i]->y + counter]->id = 'X';
				map[x][seeds[i]->y + counter + 1]->id = id;
				finished = false;
			}
			else if (map[x][seeds[i]->y + counter]->id != 'O' && map[x][seeds[i]->y + counter]->id != 'X')
			{
				map[x][seeds[i]->y + counter]->id = 'I';
			}
			//BOTTOM
			if (map[x][seeds[i]->y - counter]->id == id)
			{
				map[x][seeds[i]->y - counter]->id = 'X';
				map[x][seeds[i]->y - counter - 1]->id = id;
				finished = false;

			}
			else if (map[x][seeds[i]->y - counter]->id != 'O' && map[x][seeds[i]->y - counter]->id != 'X')
			{
				map[x][seeds[i]->y - counter]->id = 'I';
			}
		}
		for (int x = seeds[i]->y - counter + 1; x < seeds[i]->y + counter; x++)
		{

			//RIGHT
			if (map[seeds[i]->x + counter][x]->id == id)
			{
				map[seeds[i]->x + counter][x]->id = 'X';
				map[seeds[i]->x + counter + 1][x]->id = id;
				finished = false;

			}
			else if(map[seeds[i]->x + counter][x]->id != 'O' && map[seeds[i]->x + counter][x]->id != 'X')
			{
				map[seeds[i]->x + counter][x]->id = 'I';
			}

			//LEFT
			if (map[seeds[i]->x - counter][x]->id == id)
			{
				map[seeds[i]->x - counter][x]->id = 'X';
				map[seeds[i]->x - counter - 1][x]->id = id;
				finished = false;

			}
			else if (map[seeds[i]->x - counter][x]->id != 'O' && map[seeds[i]->x - counter][x]->id != 'X')
			{
				map[seeds[i]->x - counter][x]->id = 'I';
			}
		}
			

	
		//TOP RIGHT CORNER
		if (map[seeds[i]->x + counter][seeds[i]->y + counter]->id == id)
		{
			map[seeds[i]->x + counter][seeds[i]->y + counter]->id = 'X';
			map[seeds[i]->x + counter +1][seeds[i]->y + counter]->id = id;
			map[seeds[i]->x + counter][seeds[i]->y + counter+1]->id = id;
			map[seeds[i]->x + counter +1][seeds[i]->y + counter+1]->id = id;
			finished = false;

		}
		else if (map[seeds[i]->x + counter][seeds[i]->y + counter]->id != 'O' && map[seeds[i]->x + counter][seeds[i]->y + counter]->id != 'X')
		{
			map[seeds[i]->x + counter][seeds[i]->y + counter]->id = 'I';
		}
		//TOP LEFT CORNER
		if (map[seeds[i]->x - counter][seeds[i]->y + counter]->id == id)
		{
			map[seeds[i]->x - counter][seeds[i]->y + counter]->id = 'X';
			map[seeds[i]->x - counter - 1][seeds[i]->y + counter]->id = id;
			map[seeds[i]->x - counter][seeds[i]->y + counter + 1]->id = id;
			map[seeds[i]->x - counter - 1][seeds[i]->y + counter + 1]->id = id;
			finished = false;

		}
		else if (map[seeds[i]->x - counter][seeds[i]->y + counter]->id != 'O' && map[seeds[i]->x - counter][seeds[i]->y + counter]->id != 'X')
		{
			map[seeds[i]->x - counter][seeds[i]->y + counter]->id = 'I';
		}
		//BOTTOM RIGHT CORNER
		if (map[seeds[i]->x + counter][seeds[i]->y - counter]->id == id)
		{
			map[seeds[i]->x + counter][seeds[i]->y - counter]->id = 'X';
			map[seeds[i]->x + counter + 1][seeds[i]->y - counter]->id = id;
			map[seeds[i]->x + counter][seeds[i]->y - counter - 1]->id = id;
			map[seeds[i]->x + counter + 1][seeds[i]->y - counter - 1]->id = id;
			finished = false;

		}
		else if (map[seeds[i]->x + counter][seeds[i]->y - counter]->id != 'O' && map[seeds[i]->x + counter][seeds[i]->y - counter]->id != 'X')
		{
			map[seeds[i]->y + counter][seeds[i]->y - counter]->id = 'I';
		}
		//BOTTOM LEFT CORNER
		if (map[seeds[i]->x - counter][seeds[i]->y - counter]->id == id)
		{
			map[seeds[i]->x - counter][seeds[i]->y - counter]->id = 'X';
			map[seeds[i]->x - counter - 1][seeds[i]->y - counter]->id = id;
			map[seeds[i]->x - counter][seeds[i]->y - counter - 1]->id = id;
			map[seeds[i]->x - counter - 1][seeds[i]->y - counter - 1]->id = id;
			finished = false;

		}
		else if (map[seeds[i]->x - counter][seeds[i]->y - counter]->id != 'O' && map[seeds[i]->x - counter][seeds[i]->y - counter]->id != 'X')
		{
			map[seeds[i]->x - counter][seeds[i]->y - counter]->id = 'I';
		}

		
		



		


		if(finished)
		{
			cout << "erased seed of id: " << seeds[i]->id << endl;

			seeds.erase(seeds.begin() + i);
		}
		
	}
	return false;
}

bool Tile_Generator::Seed_Propagate_v2(int counter)
{
	bool finished;
	if (seeds.empty())
	{
		return true;
	}
	for (int i = 0; i < seeds.size(); i++)
	{
		finished = true;
		char id = seeds[i]->id;
		int seedX = seeds[i]->x;
		int seedY = seeds[i]->y;
		for (int x = seedX - counter; x < seedX + counter+1; x++)
		{
			if(Check_Location(id, x,seedY + counter))
			{
				map[x][seedY + counter]->id = id;
				finished = false;

			}
			if (Check_Location(id, x, seedY - counter))
			{
				map[x][seedY - counter]->id = id;
				finished = false;

			}
		}
		for (int y = seedY - counter + 1; y < seedY + counter; y++)
		{
			if (Check_Location(id, seedX + counter, y))
			{
				map[seedX + counter][y]->id = id;
				finished = false;
			}
			if (Check_Location(id, seedX - counter, y))
			{
				map[seedX - counter][y]->id = id;
				finished = false;
			}
		}









		if (finished)
		{
			cout << "erased seed of id: " << seeds[i]->id << endl;

			seeds.erase(seeds.begin() + i);
		}

	}
	return false;
}

bool Tile_Generator::Check_Location(char id, int x, int y)
{
	bool IsSafe = true;
	if (map[x + 1][y]->id != 'O' && map[x + 1][y]->id != id)
	{
		IsSafe = false;
	}
	if (map[x - 1][y]->id != 'O' && map[x - 1][y]->id != id)
	{
		IsSafe = false;
	}
	if (map[x][y + 1]->id != 'O' && map[x][y + 1]->id != id)
	{
		IsSafe = false;
	}
	if (map[x][y - 1]->id != 'O' && map[x][y - 1]->id != id)
	{
		IsSafe = false;
	}
	if (map[x + 1][y + 1]->id != 'O' && map[x + 1][y + 1]->id != id)
	{
		IsSafe = false;
	}
	if (map[x + 1][y - 1]->id != 'O' && map[x + 1][y - 1]->id != id)
	{
		IsSafe = false;
	}
	if (map[x - 1][y + 1]->id != 'O' && map[x - 1][y + 1]->id != id)
	{
		IsSafe = false;
	}
	if (map[x - 1][y - 1]->id != 'O' && map[x - 1][y - 1]->id != id)
	{
 		IsSafe = false;
	}
	return IsSafe;
}

void Tile_Generator::Show_Result()
{
	for (int x = width; x < width*2-1; x++)
	{
		for (int y = height; y < height*2-1; y++)
		{
			if(map[x][y]->id == 'O')
			{
				cout << char(219);
			}
			else
			{
				cout << '0';
			}
			//cout << map[x][y]->id;
		}
		cout << endl;

	}

	return;

	
}

void Tile_Generator::Clean_Pathways()
{
	for (int x = width; x < width * 2 - 1; x++)
	{
		for (int y = height; y < height * 2 - 1; y++)
		{
			if (map[x][y]->id == 'I')
			{
				int NumAdj = 0;
				if(map[x + 1][y]->id == 'I')
				{
					NumAdj++;
				}
				if (map[x - 1][y]->id == 'I')
				{
					NumAdj++;
				}
				if (map[x][y + 1]->id == 'I')
				{
					NumAdj++;
				}
				if (map[x][y - 1]->id == 'I')
				{
					NumAdj++;
				}
				if (NumAdj < 2 && map[x + 1][y + 1]->id == 'I')
				{
					map[x][y + 1]->id = 'I';
					NumAdj++;
				}
				if (NumAdj < 2 && map[x + 1][y - 1]->id == 'I')
				{
					map[x + 1][y]->id = 'I';
					NumAdj++;
				}
				if (NumAdj < 2 && map[x - 1][y + 1]->id == 'I')
				{
					map[x][y - 1]->id = 'I';
					NumAdj++;
				}
				if (NumAdj < 2 && map[x - 1][y - 1]->id == 'I')
				{
					map[x - 1][y]->id = 'I';
					NumAdj++;
				}
				if (NumAdj < 2)
				{
					
				}
				
				
			}
		}
	}
	
	
	
	


	//map[x][y]->id = 'X';
}

void Tile_Generator::Classify_Tile(int x, int y)
{
	

	
	
	
}

void Tile_Generator::DFS_Classify()
{
	int x = width;
	int y = height;
	while (true)
	{
		if (map[x][y]->id == 'O')
		{
			break;
		}
		x++;
	}
	vector<node*> DFSStack;
	DFSStack.push_back(map[x][y]);
	
	seeds.clear();
	int NumAdj, Numvert, NumHorz;
	while(!DFSStack.empty())
	{
		//checking for surrounding info
		NumAdj, Numvert, NumHorz = 0;
		if (map[x + 1][y]->id == 'O')
		{
			NumHorz++;
			NumAdj++;
		}
		if (map[x - 1][y]->id == 'O')
		{
			NumHorz++;
			NumAdj++;
		}
		if (map[x][y + 1]->id == 'O')
		{
			Numvert++;
			NumAdj++;
		}
		if (map[x][y - 1]->id == 'O')
		{
			Numvert++;
			NumAdj++;
		}
		if (map[x + 1][y + 1]->id == 'O')
		{
			NumAdj++;
		}
		if (map[x + 1][y - 1]->id == 'O')
		{
			NumAdj++;
		}
		if (map[x - 1][y + 1]->id == 'O')
		{
			NumAdj++;
		}
		if (map[x - 1][y - 1]->id == 'O')
		{
			NumAdj++;
		}
		// classifying shape of tile
		if(NumAdj == 2 && Numvert == 2)
		{
			map[x][y]->shape = TileShape::VerticalHall;
		}
		else if(NumAdj == 2 && NumHorz == 2)
		{
			map[x][y]->shape = TileShape::HorizontalHall;

		}
		else if (NumAdj == 2 && NumHorz == 2)
		{

		}
		else if ()
		{

		}
		else if ()
		{

		}
		else if ()
		{

		}

		
	}
	


	
}