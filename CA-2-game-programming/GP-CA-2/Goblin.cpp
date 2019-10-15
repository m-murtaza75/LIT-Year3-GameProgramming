/**
*	@Creator		Muhammad Murtaza
*	@StudentID		[K00223470]
*	@CreationDate	20/11/2018
*
**/

#include "Goblin.h"

void Goblin::update(Level &level)
{
	if (movingRight != true)
	{
		nextTile = level.getTile(m_x - 1, m_y);

		switch (nextTile)
		{
		case '.':
			level.setTile(m_x, m_y, '.');
			m_x = m_x - 1;
			level.setTile(m_x, m_y, 'G');
			break;

		case '#':
			movingRight = true;
			break;
		case 'P':
			level.setTile(m_x, m_y, '.');
			m_x = m_x - 1;
			break;
		}

	}
	else
	{
		nextTile = level.getTile(m_x + 1, m_y);

		switch (nextTile)
		{
		case '.':
			level.setTile(m_x, m_y, '.');
			m_x = m_x + 1;
			level.setTile(m_x, m_y, 'G');
			break;

		case '#':
			movingRight = false;
			break;
		case 'P':
			level.setTile(m_x, m_y, '.');
			m_x = m_x + 1;
			break;
		}


	}
}

