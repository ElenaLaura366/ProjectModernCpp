module;
export module wordhandler;

export import <fstream>;
export import <vector>;
export import <string>;
import <chrono>;
import <format>;

namespace skribbl
{
	export class WordHandler
	{
	private:
		void readFromFile();
		int randomIndex(int size) const;
		uint8_t getLetter(); // it will return one char

	public:
		WordHandler(const std::string& fileName);
		~WordHandler() = default; 
		WordHandler(const WordHandler& wg)=delete; 
		WordHandler& operator=(const WordHandler&)=delete; 
		WordHandler(WordHandler&& wg) =default;  
		WordHandler& operator=(WordHandler&&) = default; 

		void update();
		std::string getWord() const;
		bool availableLetters();
		std::string getWordPattern() const; // displays only the number of characters the word has
		std::string getHint(); // displays the number of characters and several characters from the word

	private:
		std::vector<std::string> m_words;
		std::string m_currentWord;
		std::string m_fileName;
		std::vector<char> m_availableChars; 
	};
}