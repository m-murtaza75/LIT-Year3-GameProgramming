/**
*	@Creator		Muhammad Murtaza
*	@StudentID		[K00223470]
*	@CreationDate	20/11/2018
*
**/

#pragma once
#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Level
{
public:
	void load(string fileName);
	void print();

	char getTile(int x, int y);

	void setTile(int x, int y, char tile);

public:
	vector <string> _levelData;
};


#endif // !LEVEL_H

