#include "Enemy.h"


#define MIN 1
#define MAX 15
#define HEALTH_REDUCER m_speed * 3


void Enemy::update()
{
	int x_moved;
	int y_moved;


	int directionPicker;

	enum Directions
	{
		EAST,
		WEST,
		NORTH,
		SOUTH,
		NORTH_EAST,
		SOUTH_WEST,
		NORTH_WEST,
		SOUTH_EAST


	};

	Directions enemy_Direction;

	srand(static_cast<unsigned int>(time(0)));  // seed random number generator based on current time

	directionPicker = EAST + rand() % (SOUTH_EAST + 1 - EAST); // gets a number within the range EAST used as min value and SOUTH_EAST as max value

	//To check the value is not same everytime update function is called
	//cout << "Direction picker: " << directionPicker << endl;


	switch (directionPicker)
	{
	case EAST:
		enemy_Direction = EAST;
		m_x += m_speed;
		break;

	case WEST:
		enemy_Direction = WEST;
		m_x -= m_speed;
		break;

	case NORTH:
		enemy_Direction = NORTH;
		m_y -= m_speed;
		break;

	case SOUTH:
		enemy_Direction = SOUTH;
		m_y += m_speed;
		break;

	case NORTH_EAST:
		enemy_Direction = NORTH_EAST;
		m_x += m_speed;
		m_y -= m_speed;
		break;
	
	case SOUTH_WEST:
		enemy_Direction = SOUTH_WEST;
		m_x -= m_speed;
		m_y += m_speed;
		break;

	case NORTH_WEST:
		enemy_Direction = NORTH_WEST;
		m_x -= m_speed;
		m_y -= m_speed;
		break;

	case SOUTH_EAST:
		enemy_Direction = SOUTH_EAST;
		m_x += m_speed;
		m_y += m_speed;
		break;

	default:
		cout << "\nInvalid option";
	}


	//Checking if x coord voilating max/min range after updating  
	if (m_x > MAX)
	{
		x_moved = MAX - (m_x - m_speed);
		m_x = MAX - (m_speed - x_moved);
	}
	else if (m_x < MIN)
	{
		x_moved = (m_x + m_speed) - MIN;

		m_x = (m_speed - x_moved) + MIN;
	}


	//Checking if y coord voilating max/min range after updating
	if (m_y > MAX)
	{
		y_moved = MAX - (m_y - m_speed);
		m_y = MAX - (m_speed - y_moved);
	}
	else if (m_y < MIN)
	{
		y_moved = (m_y + m_speed) - MIN;

		m_y = (m_speed - y_moved) + MIN;
	}


	m_health -= HEALTH_REDUCER;

	//Sleep method used to give some gap in time so probability of same number occur reduces 
	Sleep((rand() % 50) + 25);


}