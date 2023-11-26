module timer;

using namespace skribbl;

static const milliseconds kRefreshingRate{ 10 };
static const seconds kDuration{ 60 };

Timer::Timer()
	: m_isRunning{ false },
	m_duration{ kDuration },
	m_elapsedTime{ 0s }
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

				if (isTimeUp() & !m_isPaused)
				{
					m_isPaused = true;
					m_condition.notify_one();
					// notify game of end turn;
				}

				milliseconds timePassed = duration_cast<milliseconds>(endLock - startLock);
				m_elapsedTime.store(m_elapsedTime.load() + timePassed);
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

void Timer::restart()
{
	m_elapsedTime.store(0s);
	m_isPaused = false;
	m_condition.notify_all();
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

milliseconds Timer::getElapsedTime() const
{
	return m_elapsedTime.load();
}

milliseconds Timer::getRemainingTime() const
{
	return m_duration.load() - m_elapsedTime.load();
}

bool Timer::isTimeUp() const
{
	return m_elapsedTime.load().count() >= m_duration.load().count();
}
