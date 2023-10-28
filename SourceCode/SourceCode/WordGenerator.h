#pragma once
#include <fstream>
#include <vector>

class WordGenerator
{
private:
	void ReadFromFile() ;
	int RandomIndex(int size) const;

public:
	WordGenerator(const std::string& path);
	void UpdateWordGenerator();
	std::string GetWord() const; 
	char GetLetter(); // se va returna un singur char
	bool AvailableLetters();

private:
	std::vector<std::string> m_words;
	std::string m_currentWord;
	std::string m_fileName;
	std::vector<char> m_availableChars; // de vazut ce fel de container vom folosi
};

