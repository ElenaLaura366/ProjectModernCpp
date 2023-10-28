#pragma once
#include "Player.h"
#include "WordGenerator.h"

class Turn
{
public:
	Turn();

	Turn(const Player& player);

	void reset(const Player& player);

	uint16_t score();

	bool verifyGuess(const std::string& guess);

private:
	Player* m_playerDrawing;
	WordGenerator* m_wordGenerator;
	// TO DO Timer m_timer;
};


