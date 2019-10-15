/**
*	@Creator		Muhammad Murtaza
*	@StudentID		[K00223470]
*	@CreationDate	20/11/2018
*
**/

#include "Player.h"



void Player::update(Level &level)
{
	char input;
	char nextTile;



	cout << "\nEnter a move command (w/s/a/d) or press q to quit: ";
	cout << "\n";
	input = _getwch();

	switch (input)
	{
	case 'w':
	case 'W':
		nextTile = level.getTile(m_x, m_y - 1);
		switch (nextTile)
		{
		case '#':
			cout << "You ran into a wall.\n";
			break;
		case '.':
			level.setTile(m_x, m_y, '.');
			m_y = m_y - 1;
			level.setTile(m_x, m_y, 'P');
			break;
		default:
			level.setTile(m_x, m_y, '.');
			m_y--;
			level.setTile(m_x, m_y, 'P');
			break;
		
		}
		//responseToMove(level, m_x, m_y - 1);
		break;
	case 's':
	case 'S':
		nextTile = level.getTile(m_x, m_y + 1);
		switch (nextTile)
		{
		case '#':
			cout << "\nYou ran into a wall.\n";
			break;
		case '.':
			level.setTile(m_x, m_y, '.');
			m_y = m_y + 1;
			level.setTile(m_x, m_y, 'P');
			break;
		default:
			level.setTile(m_x, m_y, '.');
			m_y++;
			level.setTile(m_x, m_y, 'P');
			break;

		}
		//responseToMove(level, m_x, m_y + 1);
		break;
	case 'a':
	case 'A':
		nextTile = level.getTile(m_x - 1, m_y);
		switch (nextTile)
		{
		case '#':
			cout << "\nYou ran into a wall.\n";
			break;
		case '.':
			level.setTile(m_x, m_y, '.');
			m_x = m_x - 1;
			level.setTile(m_x, m_y, 'P');
			break;
		default:
			level.setTile(m_x, m_y, '.');
			m_x--;
			level.setTile(m_x, m_y, 'P');
			break;

		}
		//responseToMove(level, m_x - 1, m_y);
		break;
	case 'd':
	case 'D':
		nextTile = level.getTile(m_x + 1, m_y);
		switch (nextTile)
		{
		case '#':
			cout << "\nYou ran into a wall.\n";
			break;
		case '.':
			level.setTile(m_x, m_y, '.');
			m_x = m_x + 1;
			level.setTile(m_x, m_y, 'P');
			break;
		default:
			level.setTile(m_x, m_y, '.');
			m_x++;
			level.setTile(m_x, m_y, 'P');
			break;

		}
		//responseToMove(level, m_x + 1, m_y);
		break;
	case 'q':
	case 'Q':
		cout << "\nThank you for playing\n";
		system("PAUSE");
		exit(1);
		break;
	default:
		cout << "INVALID INPUT!!!\n";
		break;
	}

}

void Player::gainExperience()
{
	m_experience = m_experience + 30;
}

void Player::gainLuck()
{
	m_luck = m_luck + 4;
}


