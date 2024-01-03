#include "WordHandler.h"

using skribbl::WordHandler;

skribbl::WordHandler::WordHandler(skribbl::Database& db) : m_db{ db }, m_currentWord { "" }
{
	m_ur = std::make_unique<UniqueRandom<int>>(m_db.GetNumberOfWords());
}

std::string WordHandler::GetWord()
{
	return m_currentWord;
}

std::string WordHandler::GetHint() const
{
	if (m_currentWord.size() == 0) {
		return {};
	}

	UniqueRandom<int> randomPossitions(m_currentWord.size());

	std::string m_hint;
	for (char chr : m_currentWord)
		m_hint += "_";

	for (int index = 0; index < m_currentWord.size()/2;) {
		int pos = randomPossitions.GetValue();
		char currentCharacter = m_currentWord[pos];
		if (currentCharacter != ' ')
		{
			m_hint[pos] = currentCharacter;
			index++;
		}
	}

	return m_hint;
}

void skribbl::WordHandler::Reset()
{
	int wordPos = 1 + m_ur->GetValue();
	m_currentWord = m_db.GetWord(wordPos);
}
