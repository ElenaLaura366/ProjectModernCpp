module;
export module wordgenerator;
import <fstream>;
import <vector>;
import <chrono>;
import <string>;

namespace skribbl
{
	export class WordGenerator
	{
	private:
		void readFromFile();
		int randomIndex(int size) const;

	public:
		WordGenerator(const std::string& fileName);
		void update();
		std::string getWord() const;
		char getLetter(); // it will return one char
		bool availableLetters();

	private:
		std::vector<std::string> m_words;
		std::string m_currentWord;
		std::string m_fileName;
		std::vector<char> m_availableChars; // we'll see what container we'll use
		std::ifstream m_fin;
	};

}