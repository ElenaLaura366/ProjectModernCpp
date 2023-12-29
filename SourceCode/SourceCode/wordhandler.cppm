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

		void Reset();
		
		std::string GetWord();
		std::string GetHint() const; // displays the number of characters and several characters from the word

	private:
		std::string m_currentWord;
		UniqueRandom<int>::UniqueRandomPtr m_ur;
	};
}