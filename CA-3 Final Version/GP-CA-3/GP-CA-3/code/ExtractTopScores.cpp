/*
	STUDENT NAME: MUHAMMAD MURTAZA
	STUDENT ID: K00223470
	CA: 3
	SUBJECT: GAME PROGRAMMING

*/

#include "ZombieArena.h"
#include <fstream>

void extractTopScores(std::string &one, std::string &second, std::string &third)//, std::string third)
{
	int s;

	std::vector<int> fileScores;

	std::ifstream readFile("gameData/scores.txt");

	while (!readFile.eof())
	{
		readFile >> s;

		fileScores.push_back(s);

	}

	readFile.close();

	fileScores.pop_back();

	if (fileScores.size() == 1)
	{
		s = fileScores.size() - 1;

		one = std::to_string(fileScores[s]);

		second = "--";

		third = "--";
	}
	else if (fileScores.size() == 2)
	{
		/**
		first.setFont(font);
		first.setCharacterSize(80);
		first.setFillColor(Color::Red);
		first.setPosition(260, 210);
		**/

		s = fileScores.size() - 1;

		one = std::to_string(fileScores[s - 1]);

		second = std::to_string(fileScores[s]);

		third = "--";

	}

	else if (fileScores.size() > 2)
	{
		//fileScores.pop_back();

		std::sort(fileScores.begin(), fileScores.end());


		s = fileScores.size() - 1;

		one = std::to_string(fileScores[s]);

		second = std::to_string(fileScores[s - 1]);

		third = std::to_string(fileScores[s - 2]);
	}

}