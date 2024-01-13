#include "WordHandler.h"

using skribbl::WordHandler;

skribbl::WordHandler::WordHandler(skribbl::Database& db) : m_db{ db }, m_currentWord { "Not_Initialized" }, m_customWordPos { 0 }
{
	m_ur = std::make_unique<UniqueRandom<int>>(m_db.GetNumberOfWords());
}

std::string WordHandler::GetWord()
{
	return m_currentWord;
}

std::vector<uint8_t> WordHandler::GenerateHint()
{

	UniqueRandom<int> randomPossitions(m_currentWord.size());

	if (m_hint.size() < m_currentWord.size() / 2 && m_currentWord.size() == 0) {
		int pos = randomPossitions.GetValue();
		if (std::find(m_hint.begin(), m_hint.end(), pos) == m_hint.end())
		{
			m_hint.emplace_back(pos);
		}
	}

	return m_hint;
}

void skribbl::WordHandler::AddCustomWord(const std::string& word)
{
	m_customWords.push_back(std::make_pair(word, 0));
}

void skribbl::WordHandler::UpdateCustomWordScore(int16_t score)
{
	m_customWords[m_customWordPos].second = score;
}

uint8_t skribbl::WordHandler::GetNumberCustomWord() const
{
	return m_customWords.size();
}

bool skribbl::WordHandler::AreCustomWordsLeft() const
{
	return m_customWordPos < m_customWords.size();
}

void skribbl::WordHandler::Reset()
{
	if (m_customWordPos < m_customWords.size())
	{
		m_currentWord = m_customWords[m_customWordPos++].first;
	}
	else
	{
		int wordPos = 1 + m_ur->GetValue();
		m_currentWord = m_db.GetWord(wordPos);
	}
	m_hint.clear();
}