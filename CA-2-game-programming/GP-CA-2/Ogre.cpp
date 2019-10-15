/**
*	@Creator		Muhammad Murtaza
*	@StudentID		[K00223470]
*	@CreationDate	20/11/2018
*
**/

#include "Ogre.h"


void Ogre::update(Level &level)
{

	switch (directionToMove)
	{
	case 1:
		nextTile = level.getTile(m_x, m_y - 1);

		switch (nextTile)
		{
		case '.':
			level.setTile(m_x, m_y, '.');
			m_y--;
			level.setTile(m_x, m_y, 'O');
			directionToMove++;
			break;
		case 'P':
			level.setTile(m_x, m_y, '.');
			m_y = m_y - 1;
			directionToMove++;
			break;
		}
		break;

	case 2:
		nextTile = level.getTile(m_x - 1, m_y);

		switch (nextTile)
		{
		case '.':
			level.setTile(m_x, m_y, '.');
			m_x--;
			level.setTile(m_x, m_y, 'O');
			directionToMove++;
			break;
		case 'P':
			level.setTile(m_x, m_y, '.');
			m_x--;
			directionToMove++;
			break;
		}
		break;

	case 3:
		nextTile = level.getTile(m_x, m_y + 1);

		switch (nextTile)
		{
		case '.':
			level.setTile(m_x, m_y, '.');
			m_y++;
			level.setTile(m_x, m_y, 'O');
			directionToMove++;
			break;
		case 'P':
			level.setTile(m_x, m_y, '.');
			m_y++;
			directionToMove++;
			break;
		}
		break;


	case 4:
		nextTile = level.getTile(m_x + 1, m_y);

		switch (nextTile)
		{
		case '.':
			level.setTile(m_x, m_y, '.');
			m_x++;
			level.setTile(m_x, m_y, 'O');
			directionToMove++;
			break;
		case 'P':
			level.setTile(m_x, m_y, '.');
			m_x++;
			directionToMove++;
			break;
		}
		break;

	default:
		directionToMove = 1;
		break;
	}

}