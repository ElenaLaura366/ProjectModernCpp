#include "Turn.h"

Turn::Turn(const Player& player)
{
	m_playerDrawing = new Player(player);
	m_wordGenerator = new WordGenerator("WordsFile.txt");
	// TO DO timer init
}

void Turn::reset(const Player& player)
{
	m_playerDrawing = new Player(player);
	m_wordGenerator->UpdateWordGenerator();
	// TO DO reset timer
}

uint16_t Turn::score()
{
	return 0;
}

bool Turn::verifyGuess(const std::string& guess)
{
	return guess == m_wordGenerator->GetWord();
}
