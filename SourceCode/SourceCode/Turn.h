#pragma once
#include "Player.h"
#include "WordGenerator.h"

class Turn
{
public:
	Turn(const Player& player);

	void reset(const Player& player);

private:
	Player* m_player;
	WordGenerator* wordGenerator;
	// TO DO Timer m_timer;
};


