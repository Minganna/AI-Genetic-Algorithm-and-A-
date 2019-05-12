#include "Menu.h"
#include "Mazed.h"
#include <iostream>

int GeneticAlgorithm(Mazed maze);
void AStar(Mazed maze);

int main(char *argv, int argc)
{
	bool exit=false;
	while (exit == false)
	{
		std::cout << "Welcome to this demonstration of a deterministic and a probabilistic Path-Finding algorithm" << std::endl;
		std::cout << "The choosed one are A* and Genetic Algorithm for this investigation" << std::endl;
		std::cout << "Please select 1 if you want to see the Genetic Algorithm works or 2 for the A* or 3 if you want to exit" << std::endl;

		int choose = 0;
		int chooseDifficulty = 0;

		while (choose != 1 && choose != 2&& choose != 3)
		{
			std::cin >> choose;
		}
		std::string Map;

		if (choose != 3)
		{

			std::cout << "Please the difficulty of the map desired:  " << std::endl;
			std::cout << "1: Easy,\n2: Medium,\n3: Difficult\n4: Worst Case Scenario " << std::endl;

			while (chooseDifficulty != 1 && chooseDifficulty != 2 && chooseDifficulty != 3 && chooseDifficulty != 4)
			{
				std::cin >> chooseDifficulty;
			}

			if (chooseDifficulty == 1)
			{
				Map = "../easy.txtt";
			}
			if (chooseDifficulty == 2)
			{
				Map = "../medium.txtt";
			}
			if (chooseDifficulty == 3)
			{
				Map = "../difficult.txt";
			}
			if (chooseDifficulty == 4)
			{
				Map = "../WorstCaseMap.txtt";
			}

			Mazed maze = Mazed(Map);




		if (choose == 1)
		{
			GeneticAlgorithm(maze);
		}

		if (choose == 2)
		{
			AStar(maze);
		}
		}
		if (choose == 3)
		{
			exit = true;
		}
	}
}