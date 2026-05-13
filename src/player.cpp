#include "player.h"

void Player::useArrow()
{
	if (m_arrows > 0)
		--m_arrows;
}
