/*#include "UniqueRandom.h"


UniqueRandom::UniqueRandom(int number) : m_rand(),  m_dist(0, static_cast<int>(number)-1)
{
	//m_dist = std::uniform_int_distribution<int>(0, number-1);
	reset();
}

void UniqueRandom::reset()
{
	do
	{
		m_currentValue = m_dist(m_rand);
	} while (m_usedNumber.find(m_currentValue) != m_usedNumber.end());

	m_usedNumber.emplace(m_currentValue);

}

int UniqueRandom::getValue()
{
	int current = m_currentValue;
	reset();
	return current;
}*/

//size_t UniqueRandom::generateUniqueNumber()
//{
//	do
//	{
//		m_currentValue = m_dist(m_rand);
//	} while (m_usedNumber.find(m_currentValue) != m_usedNumber.end());
//
//	m_usedNumber.insert(m_currentValue);
//
//	return m_currentValue;
//}
