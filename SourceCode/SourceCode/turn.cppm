module;
export module turn;

import wordhandler;
import timer;
import <vector>;
import <memory>;
import <numeric>;

namespace skribbl
{
	export class Turn
	{
	public:
		using TurnPtr = std::unique_ptr<Turn>;

		static constexpr uint8_t kMaxScore = 100;

	public:
		Turn();
		Turn(const Turn& other) = delete;
		Turn& operator=(const Turn& other) = delete;
		Turn(Turn&& other) noexcept;
		Turn& operator=(Turn&& other) noexcept;
		~Turn() = default;

		void Reset();
		void SetAllPlayersGuessed();
		
		bool VerifyGuess(const std::string& guess);
		int8_t ScoreGuessingPlayer() const;
		int8_t ScoreDrawingPlayer() const;
		uint8_t AvrageAnswerTime() const;
		bool IsOver() const;
		uint8_t GetRemainingTime() const;
		std::string GetHint() const;
		std::string GetWord() const;

	private:
		WordHandler::WordHandlerPtr m_wordHandler;
		Timer m_timer;
		std::vector<uint8_t> m_answerTimestamps;
		bool m_allPlayersGuessed;
	};
}