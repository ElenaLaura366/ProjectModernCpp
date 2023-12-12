module;
export module player;

export import <string>;
export import <cstdint>;
export import <memory>;


namespace skribbl
{
	export class Player
	{
	public:
		using PlayerPtr = std::unique_ptr<Player>;

	public:
		Player();
		Player(const std::string& username);
		Player(const Player& player);
		Player& operator=(const Player& other);
		Player(Player&& player) noexcept = default;
		Player& operator=(Player&& player) noexcept = default;

		int16_t GetScore() const;
		std::string GetName() const;
		bool GetGuessed() const;
		void SetUsername(const std::string& username);
		void SetGuessed();
		void UpdateScore(int8_t score);

	private:
		std::string m_username;
		int16_t m_score;
		bool m_guessed;
	};
}