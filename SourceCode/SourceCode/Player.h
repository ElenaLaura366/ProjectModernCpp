#pragma once
#include <string>
#include <cstdint>

class Player
{
public:
	Player();
	Player(std::string username);
	int16_t getScore();
	std::string getName();
	bool getIsDrawing();
	bool getGuessed();
	void setUsername(std::string username);
	void setIsDrawing(bool isDrawing);
	void setGuessed(bool guessed);
	//void updateScore(uint16_t score);
private:
	std::string m_username;
	int16_t m_score;
	bool m_isDrawing;
	bool m_guessed;
};

