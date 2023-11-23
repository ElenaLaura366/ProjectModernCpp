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
		Player(const std::string& username);
		Player(const Player& player);
		Player& operator=(const Player& other);
		/*
		
		Piece(Body body, Color color, Height height, Shape shape);
		Piece(const Piece& piece) = delete;
		Piece& operator=(const Piece& other) = delete;
		Piece(Piece&& piece) noexcept = default;
		Piece& operator=(Piece&& piece) noexcept = default;
		
		*/

		int16_t getScore() const;
		std::string getName() const;
		bool getGuessed() const;
		void setUsername(const std::string& username);
		void setGuessed();
		void setScore(int16_t score);

	private:
		std::string m_username;
		int16_t m_score;
		bool m_guessed;
	};
}