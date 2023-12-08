module;
export module turn;

import wordhandler;
import player;
import timer;
import <vector>;

namespace skribbl
{
	export class Turn
	{
	public:
		static const uint8_t kMaxScore = 100;

	public:
		Turn();
		Turn(const std::shared_ptr<Player> player);
		Turn(const Turn& other) = delete;
		Turn& operator=(const Turn& other) = delete;
		Turn(Turn&& other) noexcept;
		Turn& operator=(Turn&& other) noexcept;
		~Turn() = default;

		void setPlayerDrawing(const std::shared_ptr<Player> player);
		void setAllGuessed(bool value);

		void reset(std::shared_ptr<Player> player);
		int8_t scoreGuessingPlayer();
		int8_t scoreDrawingPlayer();
		bool verifyGuess(const std::string& guess);
		uint8_t avrageAnswerTime();
		bool isTurnOver() const;

	private:
		std::shared_ptr<Player> m_playerDrawing;
		std::shared_ptr<WordHandler> m_wordHandler;
		Timer m_timer;
		std::vector<uint8_t> m_answerTimestamps;
		bool m_allGuessed;
	};
}