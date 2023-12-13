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

		static const uint8_t kMaxScore = 100;

	public:
		Turn();
		Turn(const Turn& other) = delete;
		Turn& operator=(const Turn& other) = delete;
		Turn(Turn&& other) noexcept;
		Turn& operator=(Turn&& other) noexcept;
		~Turn() = default;

		void Reset();
		int8_t ScoreGuessingPlayer();
		int8_t ScoreDrawingPlayer();
		bool VerifyGuess(const std::string& guess);
		uint8_t AvrageAnswerTime();
		bool IsOver() const;
		void AllPlayersGuessed();

	private:
		WordHandler::WordHandlerPtr m_wordHandler;
		Timer m_timer;
		std::vector<uint8_t> m_answerTimestamps;
		bool m_allPlayersGuessed;
	};
}