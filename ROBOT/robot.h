#include <iostream>
#include <algorithm>
#include <cstdlib>
#include "map_class.h"

using namespace std;

class Robot
{
	private:
		Map map;
		int energy;
		int x_pos;
		int y_pos;
		int collected_batts;
		int sensors[4];
	public:
		int gene[16][5];

		Robot()
		{
			x_pos = rand() % (map.sizeofMap() - 2) + 1;
			y_pos = rand() % (map.sizeofMap() - 2) + 1;
			collected_batts = 0;
			energy = 5;

			for(int i = 0; i < 16; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					if (j != 4)
					{
						gene[i][j] = rand() % 4;
					}
					else
					{
						gene[i][j] = rand() % 5 + 5;
					}
				}
			}
		}

		void readSensors(Map& map)
		{
			// North
			sensors[0] = (y_pos < map.sizeofMap() - 1) ? map.map[x_pos][y_pos + 1] : -1;
			// South
			sensors[1] = (y_pos > 0) ? map.map[x_pos][y_pos - 1] : -1;
			// West
			sensors[2] = (x_pos > 0) ? map.map[x_pos - 1][y_pos] : -1;
			// East
			sensors[3] = (x_pos < map.sizeofMap() - 1) ? map.map[x_pos + 1][y_pos] : -1;


			bool foundMatch = false;
			int geneMatch = -1;
			int robotMove;

			for (int i = 0; i < 16; i++)
			{
				bool match = true;
				for (int j = 0; j < 5; j++)
				{
					if(sensors[j] != gene[i][j] && gene[i][j] != 3)
					{
						match = false;
						break;
					}
				}

				if (match == true)
				{
					robotMove = gene[i][4];
					moveRobot(map, robotMove);
					break;
				}
				else
				{
					robotMove = gene[15][4];
					moveRobot(map, robotMove);
					break;
				}
			}
		}

		void resetStats()
		{
			x_pos = rand() % (map.sizeofMap() - 2) + 1;
			y_pos = rand() % (map.sizeofMap() - 2) + 1;
			collected_batts = 0;
			energy = 5;
		}

		int getxPos() { return x_pos; }

		int getyPos() { return y_pos; }

		int getCollectedBatteries() { return collected_batts; }
		
		void setCollectedBatteries(int value) { collected_batts = value; }

		int getEnergy() { return energy; }

		void printSensors()
		{
			for (int i = 0; i < 4; i++)
			{
				cout << sensors[i] << " ";
			}
		}

		void batteryCollected(Map& map)
		{
			energy += 5;
			collected_batts++;
			map.map[x_pos][y_pos] = 0;
		}

		void moveRobot(Map& map, int move)
		{

			// North
			if (move == 6)
			{
				energy -= 1;
				if (y_pos > 0 && sensors[0] != 1)
				{
					y_pos += 1;
					if (map.map[x_pos][y_pos] == 2)
					{
						batteryCollected(map);
					}
				}
			}
			// South
			else if (move == 5)
			{
				energy -= 1;
				if (y_pos > 0 && sensors[1] != 1)
				{
					y_pos -= 1;
					if (map.map[x_pos][y_pos] == 2)
					{
						batteryCollected(map);
					}
				}
			}
			// West
			else if (move == 7)
			{
				energy -= 1;
				if (x_pos > 0 && sensors[2] != 1)
				{
					x_pos -= 1;
					if (map.map[x_pos][y_pos] == 2)
					{
						batteryCollected(map);
					}
				}
			}
			// East
			else if (move == 8)
			{
				energy -= 1;
				if (x_pos > 0 && sensors[3] != 1)
				{
					x_pos += 1;
					if (map.map[x_pos][y_pos] == 2)
					{
						batteryCollected(map);
					}
				}
			}
			else if (move == 9)
			{
				energy -= 1;
				int randomMove = rand() % 4 + 5;

				while (randomMove == 9)
				{
					randomMove = rand() % 4 + 5;
				}

				moveRobot(map, randomMove);
			}

		}
};

/*
		void moveRobot(Map& map, int move)
		{
			cout << "Initial Position: (" << x_pos << "," << y_pos << ")\n";
			cout << "Move: " << move << endl;

			// North
			if (move == 6)
			{
				energy -= 1;
				if (y_pos > 0 && sensors[0] != 1)
				{
					y_pos += 1;
					cout << "Moved North to (" << x_pos << "," << y_pos << ")\n";
					if (map.map[x_pos][y_pos] == 2)
					{
						batteryCollected(map);
					}
				}
			}
			// South
			else if (move == 5)
			{
				energy -= 1;
				if (y_pos > 0 && sensors[1] != 1)
				{
					y_pos -= 1;
					cout << "Moved South to (" << x_pos << "," << y_pos << ")\n";
					if (map.map[x_pos][y_pos] == 2)
					{
						batteryCollected(map);
					}
				}
			}
			// West
			else if (move == 7)
			{
				energy -= 1;
				cout << "Moved West to (" << x_pos << "," << y_pos << ")\n";
				if (x_pos > 0 && sensors[2] != 1)
				{
					x_pos -= 1;
					if (map.map[x_pos][y_pos] == 2)
					{
						batteryCollected(map);
					}
				}
			}
			// East
			else if (move == 8)
			{
				energy -= 1;
				cout << "Moved East to (" << x_pos << "," << y_pos << ")\n";
				if (x_pos > 0 && sensors[3] != 1)
				{
					x_pos += 1;
					if (map.map[x_pos][y_pos] == 2)
					{
						batteryCollected(map);
					}
				}
			}
			else if (move == 9)
			{
				energy -= 1;
				int randomMove = rand() % 4 + 5;

				while (randomMove == 9)
				{
					randomMove = rand() % 4 + 5;
				}

				moveRobot(map, randomMove);
			}

			cout << "New Position: (" << getxPos() << ", " << getyPos() << ")\n";
		}
*/