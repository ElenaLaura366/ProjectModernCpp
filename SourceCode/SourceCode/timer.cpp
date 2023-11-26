module timer;

using namespace skribbl;

using namespace std::chrono;
using namespace std::chrono_literals;

static const milliseconds kRefreshingRate{ 10 };

Timer::Timer()
	: m_isRunning{ false },
	m_duration{ 60s },
	m_elapsedTime{0s}
{
	// empty
}

Timer::~Timer()
{
	stop();
}

void Timer::start()
{
	if (m_isRunning)
		return;

	m_isRunning = true;
	m_condition.notify_one();
	m_timerThread = std::thread([this]
		{
			while (m_isRunning)
			{
				time_point<steady_clock> startLock = steady_clock::now();
				std::unique_lock<std::mutex> lock(m_mutex);
				m_condition.wait_for(lock, kRefreshingRate, [&] {return !m_isRunning || m_isPaused; });
				time_point<steady_clock> endLock = steady_clock::now();

				if (!m_isRunning)
				{
					milliseconds timePassed = duration_cast<milliseconds>(endLock - startLock);
					m_elapsedTime.store(m_elapsedTime.load() + timePassed);
				}
			}
		});
}

void Timer::pause()
{
	if (m_isRunning && !m_isPaused)
	{
		m_isPaused = true;
		m_condition.notify_all();
	}
}

void skribbl::Timer::restart()
{
	m_elapsedTime.store(0s);
}

void Timer::stop()
{
	if (!m_isRunning)
		return; // exception?

	m_isRunning = false;
	m_condition.notify_one();
	if (m_timerThread.joinable())
		m_timerThread.join();
}

uint8_t Timer::getElapsedTime() const
{
	return m_elapsedTime.load().count();
}

bool Timer::isTimeUp() const
{
	return m_elapsedTime.load().count() >= m_duration.load().count();
}
