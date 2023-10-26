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
	void setUserName(std::string userName);
	void setIsDrawing(bool isDrawing);
private:
	std::string m_username;
	uint16_t m_score;
	bool m_isDrawing;
};

