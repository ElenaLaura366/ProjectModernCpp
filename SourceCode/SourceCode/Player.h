#pragma once
#include <string>
#include <cstdint>

class Player
{
public:
	Player();
	Player(std::string userName);
	uint16_t getScore();
	std::string getName();
	bool getIsDrawing();
	bool getGuesed();
	void setUserName(std::string userName);
	void setIsDrawing(bool isDrawing);
	void setGuesed(bool guesed);
	void updateScore(int score);
private:
	std::string m_username;
	uint16_t m_score;
	bool m_isDrawing;
	bool m_guesed;
};

