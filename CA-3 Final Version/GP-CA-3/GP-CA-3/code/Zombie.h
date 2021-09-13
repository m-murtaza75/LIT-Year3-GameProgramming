#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Zombie
{
protected:
	// How fast is each zombie type?
	const float CHASER_SPEED = 80;
	const float CRAWLER_SPEED = 20;
	const float DODGER_SPEED = 50;
	const float BLOATER_SPEED = 40;
	const float SPITTER_SPEED = 60;

	// How tough is each zombie type
	const float CHASER_HEALTH = 1;
	const float SPITTER_HEALTH = 2;
	const float CRAWLER_HEALTH = 3;
	const float DODGER_HEALTH  = 4;
	const float BLOATER_HEALTH = 5;
	
	
	

	// Make each zombie vary its speed slightly
	const int MAX_VARRIANCE = 30;
	const int OFFSET = 101 - MAX_VARRIANCE;


	// min & max x are used for the dodger zombie type 
	// So it doesn't go out of the level  
	int minX;
	int maxX;
	int xCounter = 1;

	// Clock for zombie's movements 
	sf::Clock movementTimer;

	// Clock for zombie's firing
	sf::Clock fireTimer;

	// Where is this zombie?
	Vector2f m_Position;

	// A sprite for the zombie
	Sprite m_Sprite;

	// How fast can this one run/crawl?
	float m_Speed;

	// How much health has it got?
	float m_Health;

	// Is it still alive?
	bool m_Alive;

	// Zombie Abilities
	bool m_dodgeAbility = false;
	bool m_FireAbility = false;

	// Public prototypes go here	
public:

	// Handle when a bullet hits a zombie
	bool hit();

	// Find out if the zombie is alive
	bool isAlive();

	// Check if zombie is firing
	bool isFiring();

	// Reset fireTimer
	void resetFireTimer();

	// Spawn a new zombie
	void spawn(float startX, float startY, int type, int seed, IntRect arena);

	// Return a rectangle that is the position in the world
	FloatRect getPosition();

	// Return fireTimer value
	long getFireTimer();

	// Where is the center of the zombie
	Vector2f getCenter();

	// Get a copy of the sprite to draw
	Sprite getSprite();

	// Update the zombie each frame
	void update(float elapsedTime, Vector2f playerLocation);
};