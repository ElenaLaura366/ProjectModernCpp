#pragma once

#include <crow.h>
#include <memory>
#include <vector>
#include <string>

import player;

namespace skribbl
{

	struct Answer {
		std::string playerName;
		std::string answer;
	};

	class IGame
	{
	public:

		using IGamePtr = std::unique_ptr<class IGame>;

		static IGamePtr Factory();

	public:
		virtual ~IGame() = default;

		virtual void Start() = 0;
		virtual void RemovePlayer(const std::string& name) = 0;
		virtual bool VerifyAnswer(const std::string& name, const std::string& answer) = 0;
		virtual bool AddPlayer(const std::string& name) = 0;
		virtual void AddAnswer(const std::string& name, const std::string& answer) = 0;
		virtual std::vector <Answer> GetAnswers() const = 0;
		virtual std::vector<std::pair<std::string, int16_t>> GetLeaderboard() const = 0;
		virtual std::string GetState() const = 0;
	};
}