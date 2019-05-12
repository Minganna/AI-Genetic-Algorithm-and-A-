#include "Mazed.h"
#include <iostream>
#include <vector>
#include <fstream>

void splitStringWhitespace(std::string& input, std::vector<std::string>& output)
{
	std::string curr;

	output.clear();

	for (size_t i = 0; i < input.length(); i++)
	{
		if (input.at(i) == ' ')
		{
			if (curr.length() > 0)
			{
				output.push_back(curr);
				curr = "";
			}
		}
		else
		{
			curr += input.at(i);
		}
	}

	if (curr.length() > 0)
	{
		output.push_back(curr);
	}
}

Mazed::Mazed(std::string maze)
{
	std::string line;
	std::vector<std::string> splitLine;
	std::ifstream mazed(maze);

	getline(mazed, line);
	splitStringWhitespace(line, splitLine);

	mapSize.x = atoi(splitLine.at(0).c_str());
	mapSize.y = atoi(splitLine.at(1).c_str());

	std::cout << mapSize.x << std::endl;
	std::cout << mapSize.y << std::endl;
	splitLine.erase(splitLine.begin(), splitLine.begin() + 2);

	MazeArray.resize(mapSize.y,std::vector<int>(mapSize.x));

	for (int h = 0; h < mapSize.y; h++)
	{
		for (int w = 0; w < mapSize.x; w++)
		{
			int index = h * mapSize.x + w;
			MazeArray[h][w]= atoi(splitLine.at(index).c_str());

			if (MazeArray[h][w] == 0)
			{
				NumbofMoveNeeded += 1;
			}

			if (MazeArray[h][w]==2)
			{
				xA = w;
				yA = h;
			}
			if (MazeArray[h][w] == 3)
			{
				xB = w;
				yB = h;
			}
			std::cout << MazeArray[h][w];
		}

	}

}


Mazed::~Mazed()
{
}

glm::vec2 Mazed::getMapsize()
{
	return mapSize;
}

int Mazed::getMapValue(int x, int y)
{
	return MazeArray[y][x];
}

glm::vec2 Mazed::getstart()
{
	start = glm::vec2(xA, yA);
	return start;
}

glm::vec2 Mazed::getfinish()
{
	finish = glm::vec2(xB, yB);
	return finish;
}

int Mazed::GetNumbofmoveneeded()
{
	return NumbofMoveNeeded;
}
