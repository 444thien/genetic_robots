#include <iostream>
#include <algorithm>
#include <cstdlib>
#ifndef MAP_CLASS_H
#define MAP_CLASS_H
using namespace std;

class Map {
private:
    int sizeMap = 11;
    int batteries = 40;

public:
    int map[11][11];
    Map()
    {
        for (int i = 0; i < sizeMap; i++)
        {
            for (int j = 0; j < sizeMap; j++)
            {
                map[i][j] = 0;
            }
        }

        for (int i = 0; i < sizeMap; i++)
        {
            map[i][0] = map[i][sizeMap - 1] = map[0][i] = map[sizeMap - 1][i] = 1;
        }

        int batteryCounter = 40;
        while (batteryCounter > 0)
        {
            int x = rand() % (sizeMap - 2) + 1;
            int y = rand() % (sizeMap - 2) + 1;

            if (map[x][y] != 2)
            {
                map[x][y] = 2;
                batteryCounter--;
            }
        }
    }

    void printMap()
    {
      for (int i = 0; i < sizeMap; ++i) {
          for (int j = 0; j < sizeMap; ++j) {
              cout << map[i][j] << " ";
          }
          cout << "\n";
      }
    }

      // Used to randomized map each after each robot (Repeating the same as initializing)
    void resetMap()
    {
      for (int i = 1; i < sizeMap - 1; ++i) {
          for (int j = 1; j < sizeMap - 1; ++j) {
              map[i][j] = 0;
          }
      }

      int batteryCounter = 40;
      while (batteryCounter > 0) {
          int x = rand() % (sizeMap - 2) + 1;
          int y = rand() % (sizeMap - 2) + 1;

          if (map[x][y] != 2) {
              map[x][y] = 2;
              batteryCounter--;
          }
      }
    }

    int batteryCount()
    {
        int counter = 0;
        for (int i = 0; i < sizeMap; i++)
        {
            for (int j = 0; j < sizeMap; j++)
            {
                if (map[i][j] == 2) counter++;
            }
        }

        return counter;
    }

    int sizeofMap()
    {
        return sizeMap;
    }
};

#endif