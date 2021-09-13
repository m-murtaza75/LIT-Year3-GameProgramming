#pragma once
#include "Zombie.h"

using namespace sf;

int createBackground(VertexArray& rVA, IntRect arena);
void extractTopScores(std::string &one, std::string &second, std::string &third);
Zombie* createHorde(int numZombies, IntRect arena);