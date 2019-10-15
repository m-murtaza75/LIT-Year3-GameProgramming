/**
*	@Creator		Muhammad Murtaza
*	@StudentID		[K00223470]
*	@CreationDate	20/11/2018
*
**/

#include "jumpyMonster.h"

void JumpyMonster::update(Level &level)
{
	if (hasJumped != true)
	{
		level.setTile(m_x, m_y, '.');
		m_y--;
		level.setTile(m_x, m_y, 'M');

		hasJumped = true;
	}
	else
	{
		level.setTile(m_x, m_y, '.');
		m_y++;
		level.setTile(m_x, m_y, 'M');
		hasJumped = false;
	}
}
