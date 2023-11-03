module;
export module turn;

export import player;
import "WordGenerator.h";

namespace skribbl
{
	export class Turn
	{
	public:
		Turn();
		Turn(Player* const player);

		void reset(Player* player);
		uint16_t score();
		bool verifyGuess(const std::string& guess);

	private:
		Player* m_playerDrawing;
		WordGenerator* m_wordGenerator;
		// TO DO Timer m_timer;
	};
}