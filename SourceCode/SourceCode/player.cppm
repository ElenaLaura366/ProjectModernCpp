module;
export module player;

export import <string>;
export import <cstdint>;

namespace skribbl
{
	export class Player
	{
	public:
		Player();
		Player(Player* player);
		Player(const std::string& username);
		int16_t getScore() const;
		std::string getName() const;
		bool getIsDrawing() const;
		bool getGuessed() const;
		void setUsername(const std::string& username);
		void setIsDrawing(bool isDrawing);
		void setGuessed(bool guessed);
		void setScore(int16_t score);
	private:
		std::string m_username;
		int16_t m_score;
		bool m_isDrawing;
		bool m_guessed;
	};
}