#include "UniqueRandom.h"


UniqueRandom::UniqueRandom(unsigned number)
{
	m_dist = std::uniform_int_distribution<int>(0, number-1);
	reset();
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
