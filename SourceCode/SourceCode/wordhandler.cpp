#include "WordHandler.h"

using skribbl::WordHandler;

WordHandler::WordHandler(skribbl::Database& db) : m_db{ db }, m_currentWord { "Not_Initialized" }, m_customWordPos { 0 }
{
	m_ur = std::make_unique<UniqueRandom<int>>(m_db.GetNumberOfWords());
}

void WordHandler::Reset()
{
	if (m_customWordPos < m_customWords.size())
	{
		m_currentWord = m_customWords[m_customWordPos++];
	}
	else
	{
		do
		{
			int wordPos = 1 + m_ur->GetValue();
			m_currentWord = m_db.GetWord(wordPos);
		} while(std::ranges::find(m_customWords, m_currentWord) != m_customWords.end());
	}
	m_hint.clear();
}

void WordHandler::ResetToInitialState()
{
	m_ur->ResetToInitialState();
	m_currentWord = "Not_Initialized";
	m_customWordPos = 0;
	m_customWords.clear();
	m_hint.clear();
}

void WordHandler::AddCustomWord(const std::string& word)
{
	m_customWords.push_back(word);
}

void WordHandler::AddCustomWordToDatabase()
{
	m_db.AddCustomWordToDatabase(m_customWords[m_customWordPos]);
}

bool WordHandler::AreCustomWordsLeft() const
{
	return m_customWordPos <= m_customWords.size();
}

const std::string& WordHandler::GetWord()
{
	return m_currentWord;
}

const std::vector<uint8_t>& WordHandler::GenerateHint()
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

uint8_t WordHandler::GetCustomWordsCount() const
{
	return m_customWords.size();
}