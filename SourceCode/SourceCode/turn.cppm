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
		Turn& operator=(const Turn& other);
		~Turn();

		void reset(Player* player);
		int8_t score();
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