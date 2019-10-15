#include "Player.h"

#define MAX 15
#define MIN 1
#define HEALTH_REDUCER m_speed * 2


void Player::update()
{

	int x_moved;
	int y_moved;

	int directionPicker;
	bool wrong;



	cout << "\nPlayer you are require to specify the x-y coordinates.\n";
	

	do
	{
		cout << "Please enter x coordinate (1 - 15): ";
		cin >> m_x;

		cout << "\nPlease enter y coordinate (1 - 15): ";
		cin >> m_y;

		if ((m_x >= 1) && (m_x <= 15) && (m_y >= 1) && (m_y <= 15))
		{

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

			Directions player_Direction;

			srand(static_cast<unsigned int>(time(0)));  // seed random number generator based on current time

			directionPicker = EAST + rand() % (SOUTH_EAST + 1 - EAST); // gets a number within the range EAST used as min value and SOUTH_EAST as max value


			switch (directionPicker)
			{
			case EAST:
				player_Direction = EAST;
				m_x += m_speed;
				break;

			case WEST:
				player_Direction = WEST;
				m_x -= m_speed;
				break;

			case NORTH:
				player_Direction = NORTH;
				m_y -= m_speed;
				break;

			case SOUTH:
				player_Direction = SOUTH;
				m_y += m_speed;
				break;

			case NORTH_EAST:
				player_Direction = NORTH_EAST;
				m_x += m_speed;
				m_y -= m_speed;
				break;

			case SOUTH_WEST:
				player_Direction = SOUTH_WEST;
				m_x -= m_speed;
				m_y += m_speed;
				break;

			case NORTH_WEST:
				player_Direction = NORTH_WEST;
				m_x -= m_speed;
				m_y -= m_speed;
				break;

			case SOUTH_EAST:
				player_Direction = SOUTH_EAST;
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


			//Deducting Health
			m_health -= HEALTH_REDUCER;

			wrong = false;

		}
		else
		{
			cout << "\nInvalid selection.\n";
			wrong = true;

		}
	}while(wrong == true);



}
