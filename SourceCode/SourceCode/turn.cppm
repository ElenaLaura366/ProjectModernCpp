module;
export module turn;

export import player;
export import wordhandler;

namespace skribbl
{
	export class Turn
	{
	public:
		static const uint8_t kMaxScore = 100;

	public:
		Turn();
		Turn(Player* const player);
		Turn(const Turn& other) = delete;
		Turn& operator=(const Turn& other) = delete;
		Turn(Turn&& other) noexcept;
		Turn& operator=(Turn&& other) noexcept;
		~Turn();

		void setPlayerDrawing(Player* const player);
		void setAllGuessed(bool value);

		void reset(Player* player);
		int8_t scoreGuessingPlayer();
		int8_t scoreDrawingPlayer();
		bool verifyGuess(const std::string& guess);
		uint8_t avrageAnswerTime();
		bool isTurnOver() const;

	private:
		Player* m_playerDrawing;
		WordHandler* m_wordHandler;
		// TO DO Timer m_timer;
		std::vector<uint8_t> m_answerTimestamps;
		bool m_allGuessed;
	};
}