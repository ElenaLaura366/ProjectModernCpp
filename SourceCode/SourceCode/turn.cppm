module;
export module turn;

import timer;
import <vector>;
import <memory>;
import <numeric>;
import <functional>;

namespace skribbl
{
	export class Turn
	{
	public:
		using TurnPtr = std::unique_ptr<Turn>;

		static constexpr uint8_t kMaxScore = 100;

	public:
		Turn(const std::function<void()>& callback);
		Turn(const Turn& other) = delete;
		Turn& operator=(const Turn& other) = delete;
		Turn(Turn&& other) noexcept;
		Turn& operator=(Turn&& other) noexcept;
		~Turn() = default;

		void Start();
		void Reset();
		void SetAllPlayersGuessed();
		
		bool VerifyGuess(const std::string& guess);
		int8_t ScoreGuessingPlayer() const;
		int8_t GetMinimGuessingScore() const;
		int8_t ScoreDrawingPlayer() const;
		uint8_t AvrageAnswerTime() const;
		bool IsOver() const;
		uint8_t GetRemainingTime() const;
		void SetCurrentWord(const std::string& word);

	private:
		std::unique_ptr<Timer> m_timer;
		std::vector<uint8_t> m_answerTimestamps;
		bool m_allPlayersGuessed;
		std::string m_currentWord;
	};
}