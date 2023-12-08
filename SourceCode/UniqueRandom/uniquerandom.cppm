module;
export module uniquerandom;
import <random>;
import <set>;

export class __declspec(dllexport) UniqueRandom
{
public:
	UniqueRandom();
	UniqueRandom(int number);
	int getValue();
	void reset();

private:
	std::random_device m_rand;
	std::uniform_int_distribution<int> m_dist;
	std::set<size_t> m_usedNumber;
	size_t m_currentValue = 0;

};

UniqueRandom::UniqueRandom()
{
}
