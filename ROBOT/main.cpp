#include <iostream>
#include <algorithm>
#include <cstdlib>
#include "map_class.h"
#include "robot.h"

using namespace std;

void testUnit();
void sortArray(Robot array[], int n);

int main()
{
    srand(time(0));
    testUnit();
    Map map_1;
    const int populationSize = 200;
    int totalBatteriesCollected = 0;
    Robot robotArray[200];

    // Simulation for 200 robots for a number of generations
    for (int i = 1; i < 200; i++)
    {
        cout << "Running generation: " << i << endl;
        // Simulation for each robot
        for (int j = 0; j < populationSize; j++)
        {
            int initialBatteryValue = robotArray[j].getCollectedBatteries();
            
            while (robotArray[j].getEnergy() > 0)
            {
                robotArray[j].readSensors(map_1);

                // Updating batteries if it's higher than the starting value
                if (robotArray[j].getCollectedBatteries() > initialBatteryValue)
                {
                    totalBatteriesCollected += (robotArray[j].getCollectedBatteries() - initialBatteryValue);
                    initialBatteryValue = robotArray[j].getCollectedBatteries();
                }
            }
            // New map for each robot
            map_1.resetMap();
        }

        cout << "Generation " << i << "'s total batteries collected were: " << totalBatteriesCollected << endl;
        cout << "Average number of batteries collected per robot: " << static_cast<double>(totalBatteriesCollected) / populationSize << endl;

        // Sorting robots in descending order
        sortArray(robotArray, populationSize);

        cout << "The highest amount of batteries collected by a robot : " << robotArray[199].getCollectedBatteries() << endl;
        cout << "The lowest amount of batteries collected by a robot: " << robotArray[0].getCollectedBatteries() << endl << endl << endl;

        cout << "Swapping genes now" << endl;
        // Swapping genes for the top 100 robots to the last 100 robots
        for (int j = 0; j < 10; j++)
        {
            int parent1 = 199 - j;
            int parent2 = 198 - j;

            if (parent1 >= 0 && parent1 < 200 && parent2 >= 0 && parent2 < 200)
            {
                for (int k = 0; k < 8; k++)
                {
                    for (int l = 0; l < 5; l++)
                    {
                        robotArray[j].gene[k][l] = robotArray[parent1].gene[k][l];
                    }
                }

                for (int k = 8; k < 16; k++)
                {
                    for (int l = 0; l < 5; l++)
                    {
                        robotArray[j].gene[k][l] = robotArray[parent2].gene[k][l];
                    }
                }
            }
            else
            {
                cout << "Invalid parent indices for robot " << j << ": parent1 = " << parent1 << ", parent2 = " << parent2 << endl;
            }
            
        }

        cout << "Resetting stats" << endl;
        for (int j = 0; j < populationSize; j++)
        {
            robotArray[j].resetStats();
        }

        totalBatteriesCollected = 0;
    }

    cout << "Finished all generations." << endl;
}

void testUnit()
{
    Robot robotTest;
    Map mapTest;
    mapTest.printMap();
    int testCounter = mapTest.batteryCount();
    cout << testCounter << endl;

    robotTest.readSensors(mapTest);
    cout << "Sensor Data (N S W E): \n";
    robotTest.printSensors();
    cout << endl;

    int energyLevel = robotTest.getEnergy();
    cout << energyLevel << endl;
    robotTest.resetStats();
    energyLevel = robotTest.getEnergy();
    cout << energyLevel << endl;
    robotTest.getEnergy();
}

void sortArray(Robot array[], int size)
{
    int temp;
    bool madeAswap;
    do
    {
        madeAswap = false;
        for (int i = 0; i < (size - 1); i++)
        {
            if (array[i].getCollectedBatteries() > array[i + 1].getCollectedBatteries())
            {
                temp = array[i].getCollectedBatteries();
                array[i].setCollectedBatteries(array[i + 1].getCollectedBatteries());
                array[i + 1].setCollectedBatteries(temp);
                madeAswap = true;
            }
        }
    } while (madeAswap);

}