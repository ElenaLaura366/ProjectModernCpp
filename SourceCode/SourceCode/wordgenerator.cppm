module;
export module wordgenerator;

import <vector>;
import <fstream>;
import <exception>;
import <ctime>;
import <random>;
export import <iostream>;

namespace skribbl
{
	export class WordGenerator
	{
	private:
		void readFromFile();
		int randomIndex(int size) const;

	public:
		WordGenerator(const std::string& fileName);
		void updateWordGenerator();
		std::string getWord() const;
		char getLetter(); // it will return one char
		bool availableLetters();

	private:
		std::vector<std::string> m_words;
		std::string m_currentWord;
		std::string m_fileName;
		std::vector<char> m_availableChars; // we'll see what container we'll use
	};

}