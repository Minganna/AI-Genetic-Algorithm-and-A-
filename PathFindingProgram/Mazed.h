#pragma once
#include <glm/glm.hpp>
#include <string>
#include <vector>

class Mazed
{
public:
	Mazed(std::string maze);
	~Mazed();
	glm::vec2 getMapsize();
	int getMapValue(int x, int y);
	glm::vec2 getstart();
	glm::vec2 getfinish();
	int GetNumbofmoveneeded();
private:
	glm::vec2 mapSize;
	std::vector<std::vector<int>> MazeArray;
	int xA, yA, xB, yB;
	int NumbofMoveNeeded;
	glm::vec2 start;
	glm::vec2 finish;
	
};