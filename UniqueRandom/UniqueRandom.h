#pragma once
#include <random>
#include <set>

class __declspec(dllexport) UniqueRandom
{
public:
	UniqueRandom(int number);
	size_t getValue();
	void reset();

private:
	size_t generateUniqueNumber();


private:
	std::random_device m_rd;
	std::uniform_int_distribution<int> m_dist;
	std::set<size_t> usedNumber;
	size_t currentValue;

};

