#include "WordGenerator.h"

void WordGenerator::readFromFile()
{
	std::ifstream fin(m_fileName);
	if (!fin.is_open()) {
		std::exception("File with unable to be oppened");
	}
	std::string word;
	while (fin >> word)
		m_words.push_back(word);
}

int WordGenerator::randomIndex(int size) const
{
	return (rand() % (size));
}

WordGenerator::WordGenerator(const std::string& fileName) : m_fileName(fileName)
{
	srand(time(0));
	readFromFile();
	updateWordGenerator();
}

void WordGenerator::updateWordGenerator()
{
	if (m_words.size() == 0)
		std::exception("There are no words left");
	m_words.erase(std::remove(m_words.begin(), m_words.end(), m_currentWord), m_words.end());
	m_currentWord = m_words[randomIndex(m_words.size())];
	m_availableChars = std::vector<char>(m_currentWord.begin(), m_currentWord.end());
}

std::string WordGenerator::getWord() const
{
	return m_currentWord;
}

char WordGenerator::getLetter()
{
	if (!availableLetters())
		std::exception("No available letters");
	uint8_t index = randomIndex(m_availableChars.size());
	char currrent = m_availableChars[index];
	m_availableChars.erase(m_availableChars.begin() + index); // nu e asa okay ca am o prelucrare de date in interiorul unui getter

	return currrent;
}

bool WordGenerator::availableLetters()
{
	return (m_availableChars.size() > 0);
}
