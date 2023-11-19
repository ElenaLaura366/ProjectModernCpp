module timer;

using namespace skribbl;
using namespace std::chrono_literals;

Timer::Timer()
	: m_isRunning{false},
	m_duration{60s}
{
	// empty
}

uint8_t Timer::getTime() const
{
	return m_duration.load().count();
}
