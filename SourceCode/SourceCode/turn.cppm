module;
export module turn;

export import player;
export import wordgenerator;

namespace skribbl
{
	export class Turn
	{
	public:
		Turn();
		Turn(Player* const player);
		Turn(const Turn& other);
		Turn& operator=(const Turn& other);
		Turn(Turn&& other) noexcept;
		Turn& operator=(Turn&& other) noexcept;
		~Turn();

		void reset(Player* player);
		int8_t scoreGuessingPlayer();
		int8_t scoreDrawingPlayer();
		bool verifyGuess(const std::string& guess);
		bool isTurnOver();

	private:
		Player* m_playerDrawing;
		WordGenerator* m_wordGenerator;
		// TO DO Timer m_timer;
		uint8_t m_avrageAnswerTime;
		const uint8_t k_maxScore = 100;
	};
}