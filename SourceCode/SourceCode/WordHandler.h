#pragma once
#include <vector>
#include <string>
#include <memory>
#include <ranges>
#include "Database.h"

import uniquerandom;

namespace skribbl
{
	class WordHandler
	{
	public:
		using WordHandlerPtr = std::unique_ptr<WordHandler>;

	public:
		WordHandler(skribbl::Database& db);
		~WordHandler() = default; 
		WordHandler(const WordHandler& wg)=delete; 
		WordHandler& operator=(const WordHandler&) = delete;
		WordHandler(WordHandler&& wg)noexcept = default;
		WordHandler& operator=(WordHandler&&)noexcept = default;

		void Reset();
		void ResetToInitialState();
		
		void AddCustomWord(const std::string& word);
		void AddCustomWordToDatabase();

		bool AreCustomWordsLeft() const;
		const std::vector<uint8_t>& GenerateHint();
		const std::string& GetWord();

		uint8_t GetCustomWordsCount() const;


	private:
		skribbl::Database& m_db;
		std::vector<std::string> m_customWords;
		std::vector<uint8_t> m_hint;
		std::string m_currentWord;
		UniqueRandom<int>::UniqueRandomPtr m_ur;
		int m_customWordPos;
	};
}