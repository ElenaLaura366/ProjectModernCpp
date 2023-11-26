#include "UniqueRandom.h"


UniqueRandom::UniqueRandom(int number)
{
	if(number > 0)
		m_dist = std::uniform_int_distribution<int>(0, number-1);
	number = 0;
}

void UniqueRandom::reset()
{
	do
	{
		m_currentValue = m_dist(m_rand);
	} while (m_usedNumber.find(m_currentValue) != m_usedNumber.end());

	m_usedNumber.insert(m_currentValue);

}

size_t UniqueRandom::getValue() const noexcept
{
	return m_currentValue;
}

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
