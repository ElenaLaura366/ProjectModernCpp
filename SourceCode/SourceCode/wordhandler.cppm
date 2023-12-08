module;
export module wordhandler;

import <fstream>;
import <vector>;
import <string>;
import <chrono>;
import <format>;
import <memory>;

namespace skribbl
{
	export class WordHandler
	{
	private:
		void readFromFile();
		int randomIndex(int size) const;

	public:
		WordHandler();
		WordHandler(const std::string& fileName);
		~WordHandler() = default; 
		WordHandler(const WordHandler& wg)=delete; 
		WordHandler& operator=(const WordHandler&) = delete;
		WordHandler(WordHandler&& wg)noexcept = default;
		WordHandler& operator=(WordHandler&&)noexcept = default;

		void update();
		std::string getWord() const;
		//std::string getWordPattern() const; // displays only the number of characters the word has
		std::vector<std::pair<int, char>> getHint(); // displays the number of characters and several characters from the word
		//std::vector<int> getWordPattern() const;

	private:
		std::vector<std::string> m_words;
		std::string m_currentWord;
		std::string m_fileName;
	};
}