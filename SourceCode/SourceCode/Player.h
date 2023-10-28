#pragma once
#include <string>
#include <cstdint>

class Player
{
public:
	Player();
	Player(std::string username);
	uint16_t getScore() const;
	std::string getName();
	bool getIsDrawing();
	bool getGuessed();
	void setUsername(std::string username);
	void setIsDrawing(bool isDrawing);
	void setGuessed(bool guessed);
	void updateScore(int score);
private:
	std::string m_username;
	uint16_t m_score;
	bool m_isDrawing;
	bool m_guessed;
};

