/**
*	@Creator		Muhammad Murtaza
*	@StudentID		[K00223470]
*	@CreationDate	20/11/2018
*
**/

#include "Level.h"
#include <fstream>

/* Loading level from file specified */
void Level::load(string fileName)
{
	ifstream file;

	file.open(fileName);

	if (file.fail())
	{
		cout << "\nError check file name";

		exit(1);

	}

	//For Reading each line of file 
	string line;

	cout << "\n";
	while (getline(file, line))
	{
		_levelData.push_back(line);
	}

	cout << "\n";

	file.close();

}


/* Printing level data on the screen */
void Level::print()
{
	for (int i = 0; i < _levelData.size(); i++)
	{
		cout << _levelData[i] << endl;
	}

	cout << endl;
}

/* Returns Level data from the specified coordinates */
char Level::getTile(int x, int y)
{
	//y comes first because y is the row and x is the column
	return _levelData[y][x];

}

/* Set specified character representation on specified location within the level */
void Level::setTile(int x, int y, char tile)
{
	_levelData[y][x] = tile;
}