import turn;
using skribbl::Turn;

Turn::Turn()
{
}

Turn::Turn(Player* const player)
{
	m_playerDrawing = player;
	m_wordGenerator = new WordGenerator("wordsFile.txt");
	// TO DO timer init
}

void Turn::reset(Player* player)
{
	m_playerDrawing = player;
	m_wordGenerator->update();
	// TO DO reset timer
}

uint16_t Turn::score()
{
	return 0;
}

bool Turn::verifyGuess(const std::string& guess)
{
	return guess == m_wordGenerator->getWord();
}
