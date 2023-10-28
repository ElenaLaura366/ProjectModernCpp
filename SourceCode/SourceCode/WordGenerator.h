#pragma once
#include <fstream>
#include <vector>

class WordGenerator
{
private:
	void ReadFromFile() ;
	int RandomIndex(int size) const;

public:
	WordGenerator(const std::string& fileName);
	void UpdateWordGenerator();
	std::string GetWord() const; 
	char GetLetter(); // it will return one char
	bool AvailableLetters();

private:
	std::vector<std::string> m_words;
	std::string m_currentWord;
	std::string m_fileName;
	std::vector<char> m_availableChars; // we'll see what container we'll use
};

