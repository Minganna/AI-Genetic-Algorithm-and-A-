/*
This is the Genetic algorithm,
The "main" function called GeneticAlgorithm(Mazed maze) is called in recipe-577457-1.cpp
The Genetic algorithm read a maze generated in Mazed to and after it generate 6 different
Chromosome made by a number of 'gene' (it starts from 8) and use them to get directions on
how to move in the maze. Then the program will register the fitness for each chromosome and
recreate new population using the originals.
*/

#include <iostream>
#include <fstream>
#include "Mazed.h"
#include <random>
#include <time.h>
#include <Windows.h>
#include <stdlib.h>
#include <vector>

//Function used to create the 6 Chromosome
std::vector<int> chromosome(std::vector<int> path, int size);
//Function used only to display on screen the direction assinged to each gene
void GetIndications(std::vector<int> Chromosome);
bool traversemap(std::vector<std::vector<int>> &Generation, int xA, int yA, std::vector<std::vector<int>> &map, int sizeY, int sizeX, int xB, int yB, std::vector<float> &fitness);
float FindFitness(int Ycurrent_Position, int Xcurrent_Position, int xB, int yB);
int SpinningTheArrow(std::vector<float> &individual, float x, int parent);
std::vector<std::vector<int>> Crossover(std::vector<std::vector<int>> &Generation, int parent1, int parent2);

enum directions
{
	Up,
	Right,
	Down,
	Left
};
//The "main" function of the Genetic algorithm
int GeneticAlgorithm(Mazed maze)
{
	int n;//this integer store the x value of the map
	int m;//this integer store the y value of the map
	
	std::vector<std::vector<int>> map;


	int numberofmove = maze.GetNumbofmoveneeded();
	std::vector <int> path;
	path.resize(numberofmove);

	int numbofcromosome = 12;

	std::vector<std::vector<int>> Generation;
	Generation.resize(numbofcromosome, std::vector<int>(numberofmove));
	std::vector<float> fitness;
	fitness.resize(numbofcromosome);

	std::vector<float> individual;
	individual.resize(numbofcromosome);

	float TotalFitness = 0, TotalFitness2 = 0;
	int parent1, parent2;

	std::random_device generator;
	std::uniform_real_distribution<float> distribution(0, 1);

	for (int i = 0; i < numbofcromosome; i++)
	{
		Generation[i] = chromosome(path, numberofmove);
		GetIndications(Generation[i]);
	}
	glm::vec2 Geneticmap = maze.getMapsize();// vec2 that store the mapsize received by the the maze class
	n = Geneticmap.x;
	m = Geneticmap.y;
	map.resize(n, std::vector<int>(m));

	int xA = 0, yA = 0, xB = 0, yB = 0;
	glm::vec2 startV = maze.getstart();
	xA = startV.x;
	yA = startV.y;
	glm::vec2 finishV = maze.getfinish();
	xB = finishV.x;
	yB = finishV.y;

	for (int h = 0; h < m; h++)
	{
		for (int w = 0; w < n; w++)
		{
			map[w][h] = maze.getMapValue(w, h);
		}
	}

	std::cout << "Map Size (X,Y): " << n << "," << m << std::endl;
	std::cout << "Start: " << xA << "," << yA << std::endl;
	std::cout << "Finish: " << xB << "," << yB << std::endl;

	bool generationEnd = false, geneticFinish = false;
	int itr = 0, breedCounter = 100;
	while (!generationEnd)
	{
		geneticFinish = traversemap(Generation, xA, yA, map, n, m, xB, yB, fitness);
		TotalFitness = 0;

		itr++;
		if (itr >= breedCounter * Generation.size() || geneticFinish)
		{
			generationEnd = true;
		}
		else
		{
			for (int i = 0; i < numbofcromosome; i++)
			{
				TotalFitness += fitness[i];
			}
				for (int i = 0; i < numbofcromosome; i++)
				{
					individual[i] = fitness[i] / TotalFitness;
					individual[i] = individual[i] * 100;
				}

				float x = distribution(generator);
				x = x * 100;
				parent1 = SpinningTheArrow(individual, x, -1);
				TotalFitness2 = TotalFitness - fitness[parent1];
				for (int j = 0; j < numbofcromosome; j++)
				{
					if (j != parent1)
					{
						individual[j] = fitness[j] / TotalFitness2;
						individual[j] = individual[j] * 100;
					}
				}
				parent2 = SpinningTheArrow(individual, x, parent1);


			Generation=Crossover(Generation, parent1, parent2);

		}
	}

	system("PAUSE");
	system("CLS");
	return 0;
}


//function used to create each chromosome in in the population
std::vector<int> chromosome(std::vector<int> path, int size)
{
	std::random_device generator;
	std::uniform_int_distribution<int> distribution(0, 3);

	for (int i = 0; i < size; i++)
	{

		path[i] = distribution(generator);

	}
	std::vector<int> Chromosome;
	Chromosome.resize(size);
	for (int temp = 0; temp < size; temp++)
	{

		Chromosome[temp] = path[temp];
		std::cout << Chromosome[temp];
	}

	return Chromosome;

}

//function only used to print the direction that each gene in each cromosome will have
void GetIndications(std::vector<int> Chromosome)
{
	std::cout << std::endl;
	for (int i = 0; i < Chromosome.size(); i++)
	{
		if (Chromosome[i] == 0)
		{
			std::cout << "Up\n";
		}
		else if (Chromosome[i] == 1)
		{
			std::cout << "Right\n";
		}
		else if (Chromosome[i] == 2)
		{
			std::cout << "Down\n";
		}
		else if (Chromosome[i] == 3)
		{
			std::cout << "Left\n";
		}
	}

	return;
	//	mapSize.x = atoi(splitLine.at(0).c_str());
//	mapSize.y = atoi(splitLine.at(1).c_str());

}

// function that is used to convert the direction in movements though the map and get his fitness, please note that the x and y are flipped.
bool traversemap(std::vector<std::vector<int>> &Generation, int xA, int yA, std::vector<std::vector<int>> &map, int SizeY, int SizeX, int xB, int yB, std::vector<float> &fitness)
{
	std::vector <int> Ycurrent_Position;
	Ycurrent_Position.resize(Generation.size());
	std::vector <int> Xcurrent_Position;
	Xcurrent_Position.resize(Generation.size());
	std::vector <int> Yold_Position;
	Yold_Position.resize(Generation.size());
	std::vector <int> Xold_Position;
	Xold_Position.resize(Generation.size());


	for (int i = 0; i < Generation.size(); i++)
	{
		Ycurrent_Position[i] = xA;
		Xcurrent_Position[i] = yA;

	}
	int cPosition = 0;
	int cN = Generation[0].size();
	directions Direction;

	std::cout << "\n\n";
	for (int h = 0; h < SizeX; h++)
	{
		for (int w = 0; w < SizeY; w++)
		{
			std::cout << map[w][h];
		}
		std::cout << "\n";
	}

	while (cPosition < cN)
	{


		for (int i = 0; i < Generation.size(); i++)
		{
			Yold_Position[i] = Ycurrent_Position[i];
			Xold_Position[i] = Xcurrent_Position[i];
		}
		for (int c = 0; c < Generation.size(); c++)
		{
			if ((Generation[c][cPosition]) == Left)
			{
				Ycurrent_Position[c] -= 1;

			}
			if ((Generation[c][cPosition]) == Right)
			{
				Ycurrent_Position[c] += 1;

			}
			if ((Ycurrent_Position[c] < 0) || (Xcurrent_Position[c] < 0) || (Ycurrent_Position[c] >= SizeY) || (Xcurrent_Position[c] >= SizeX))
			{
				Ycurrent_Position[c] = Yold_Position[c];
			}
			else
			{
				if (map[Ycurrent_Position[c]][Xcurrent_Position[c]] == 1)
				{
					Ycurrent_Position[c] = Yold_Position[c];
				}
				else
				{
					if (Ycurrent_Position[c] == xB && Xcurrent_Position[c] == yB)
					{
						std::cout << "\n";
						std::cout << "Done\n";
						std::cout << "\n\n";
						std::cout << "Results: \n\n";
						for (int h = 0; h < SizeX; h++)
						{
							for (int w = 0; w < SizeY; w++)
							{
								map[yA][xA] = 0;
								map[Ycurrent_Position[c]][Xcurrent_Position[c]] = 2;
								std::cout << map[w][h];
							}
							std::cout << "\n";
						}
						return true;
					}
				}
			}
			if ((Generation[c][cPosition]) == Up)
			{
				Xcurrent_Position[c] -= 1;

			}
			if ((Generation[c][cPosition]) == Down)
			{
				Xcurrent_Position[c] += 1;

			}
			if ((Ycurrent_Position[c] < 0) || (Xcurrent_Position[c] < 0) || (Ycurrent_Position[c] >= SizeY) || (Xcurrent_Position[c] >= SizeX))
			{
				Xcurrent_Position[c] = Xold_Position[c];
			}
			else
			{
				if (map[Ycurrent_Position[c]][Xcurrent_Position[c]] == 1)
				{
					Xcurrent_Position[c] = Xold_Position[c];
				}
				else
				{
					if (Xcurrent_Position[c] == yB && Ycurrent_Position[c] == xB)
					{
						std::cout << "\n";
						std::cout << "Done\n";
						std::cout << "\n\n";
						std::cout << "Results: \n";
						for (int h = 0; h < SizeX; h++)
						{
							for (int w = 0; w < SizeY; w++)
							{
								map[yA][xA] = 0;
								map[Ycurrent_Position[c]][Xcurrent_Position[c]] = 2;
								std::cout << map[w][h];
							}
							std::cout << "\n";
						}
						return true;
					}
				}
			}
		}

		cPosition += 1;
	}

	for (int i = 0; i < Generation.size(); i++)
	{
		std::cout << Ycurrent_Position[i] << Xcurrent_Position[i] << std::endl;
	}
	for (int i = 0; i < Generation.size(); i++)
	{
		fitness[i] = FindFitness(Ycurrent_Position[i], Xcurrent_Position[i], xB, yB);

	}

	return false;
}

//function that calculate the fitness of each cromosome
float FindFitness(int Ycurrent_Position, int Xcurrent_Position, int xB, int yB)
{
	float dX, dY;
	float Fitness;

	dX = abs(Xcurrent_Position - xB);
	dY = abs(Ycurrent_Position - yB);

	Fitness = 1 / (dX + dY + 1);

	return Fitness;
}

// function used to choose the two parents that will be used to create the next generation
int SpinningTheArrow(std::vector<float> &individual, float x, int parent)
{
	int generationSize = individual.size();
	float randCounter = 0.0f;
	for (int i = 0; i < generationSize; i++)
	{
		if (i != parent)
		{
			if ((x > randCounter) && (x < (randCounter + individual[i])))
			{
				parent = i;
			}
			randCounter += individual[i];
		}
	}

	return parent;

}

//function that create the new generation mutating and fusing the 2 parents cromosome
std::vector<std::vector<int>> Crossover(std::vector<std::vector<int>> &Generation, int parent1, int parent2)
{
	float CrossoverRate = 0.7f;
	std::random_device generator;
	std::uniform_real_distribution<float> distribution(0, 1);
	std::uniform_int_distribution<int> mutationDistribution(0, 3);
	std::vector<std::vector<int>> CrossoverVector;
	CrossoverVector.resize(Generation.size(), std::vector<int> (Generation[0].size()));
	float MutationRate = 0.05;

	int rand;

	for (int j = 0; j < Generation.size(); j+=2)
	{
		float CrossoverChance = distribution(generator);
		for (int x = 0; x < Generation[0].size(); x++)
		{
			std::cout << Generation[j][x];
			if (CrossoverChance <= CrossoverRate)
			{
				for (int i = Generation[0].size()/2; i < Generation[0].size(); i++)
				{
				CrossoverVector[j][i] = Generation[parent2][i];
				}
				for (int i = 0; i < Generation[0].size()/ 2; i++)
				{
				CrossoverVector[j][i] = Generation[parent1][i];
				}
				for (int i = Generation[0].size() / 2; i < Generation[0].size(); i++)
				{
					CrossoverVector[j+1][i] = Generation[parent1][i];
				}
				for (int i = 0; i < Generation[0].size() / 2; i++)
				{
					CrossoverVector[j+1][i] = Generation[parent2][i];
				}
				 
			}
			else
			{

				CrossoverVector[j][x] = Generation[parent1][x];
				CrossoverVector[j+1][x] = Generation[parent2][x];
			}

		
		}
		std::cout << std::endl;
	}

	for (int j = 0; j < Generation.size(); j += 2)
	{
		for (int x = 0; x < Generation[0].size(); x++)
		{
			float Mutation = distribution(generator);
			if (Mutation <= MutationRate)
			{
				rand = mutationDistribution(generator);
				CrossoverVector[j][x] = rand;

			}
		}
	}
	for (int j = 0; j < Generation.size(); j ++)
	{
		for (int x = 0; x < Generation[0].size(); x++)
		{
			Generation[j][x] = CrossoverVector[j][x];
			std::cout << Generation[j][x];
		}
		std::cout << "Changed "<<std::endl;
	}

	return Generation;
}


