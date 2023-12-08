#pragma once
#include <random>
#include <set>

class __declspec(dllexport) UniqueRandom
{
public:
	UniqueRandom(int number);
	int getValue();
	void reset();


private:
	std::random_device m_rand;
	std::uniform_int_distribution<int> m_dist;
	std::set<size_t> m_usedNumber;
	size_t m_currentValue=0;

};

