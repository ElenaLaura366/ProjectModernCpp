module;
export module wordhandler;

import <vector>;
import <string>;
import <memory>;
import uniquerandom;

namespace skribbl
{
	export class WordHandler
	{
	public:
		using WordHandlerPtr = std::unique_ptr<WordHandler>;

	public:
		WordHandler() = default;
		~WordHandler() = default; 
		WordHandler(const WordHandler& wg)=delete; 
		WordHandler& operator=(const WordHandler&) = delete;
		WordHandler(WordHandler&& wg)noexcept = default;
		WordHandler& operator=(WordHandler&&)noexcept = default;

		
		std::string GetWord() const;
		//std::string getWordPattern() const; // displays only the number of characters the word has
		std::vector<std::pair<int, char>> GetHint(); // displays the number of characters and several characters from the word
		//std::vector<int> getWordPattern() const;

	private:
		std::string m_currentWord;
		UniqueRandom<int>::UniqueRandomPtr m_ur;
	};
}