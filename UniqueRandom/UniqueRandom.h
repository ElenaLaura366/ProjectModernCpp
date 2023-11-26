#pragma once
#include <random>
#include <set>

class __declspec(dllexport) UniqueRandom
{
public:
	UniqueRandom(unsigned number);
	size_t getValue() const noexcept;

private:
	void reset();
	std::random_device m_rand;
	std::uniform_int_distribution<int> m_dist;
	std::set<size_t> m_usedNumber;
	size_t m_currentValue=0;

};

