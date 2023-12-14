module timer;

using namespace skribbl;

using namespace std::chrono;
using namespace std::chrono_literals;

static const milliseconds kRefreshingRate{ 10 };
static const seconds kDuration{ 60 };

Timer::Timer()
	: m_isRunning{ false }
	, m_duration{ kDuration }
	, m_elapsedTime{ 0s }
{
	// empty
}

Timer::~Timer()
{
	Stop();
}

void Timer::Start()
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

				if (IsTimeUp() & !m_isPaused)
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

void Timer::Pause()
{
	if (m_isRunning && !m_isPaused)
	{
		m_isPaused = true;
		m_condition.notify_all();
	}
}

void Timer::Restart()
{
	m_elapsedTime.store(0s);
	m_isPaused = false;
	m_condition.notify_all();
}

void Timer::Stop()
{
	if (!m_isRunning)
		return; // exception?

	m_isRunning = false;
	m_condition.notify_one();
	if (m_timerThread.joinable())
		m_timerThread.join();
}

milliseconds Timer::GetElapsedTime() const
{
	return m_elapsedTime.load();
}

milliseconds Timer::GetRemainingTime() const
{
	return m_duration.load() - m_elapsedTime.load();
}

bool Timer::IsTimeUp() const
{
	return m_elapsedTime.load().count() >= m_duration.load().count();
}
