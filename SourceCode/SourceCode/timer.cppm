module;
export module timer;

export import <chrono>;
import <thread>;
import <atomic>;
import <mutex>;

using namespace std::chrono;
using namespace std::chrono_literals;

namespace skribbl
{
	export class Timer
	{
	public:
		using TimeConfig = milliseconds;

	public:
		Timer();

		Timer(const Timer& other) = delete;
		Timer& operator=(const Timer& other) = delete;

		~Timer();

		void start();
		void pause();
		void restart();
		void stop();

		milliseconds getElapsedTime() const;
		milliseconds getRemainingTime() const;

		bool isTimeUp() const;

	private:
		std::thread m_timerThread;
		std::condition_variable m_condition;
		std::mutex m_mutex;

		std::atomic<bool> m_isRunning, m_isPaused;
		std::atomic<TimeConfig> m_duration;
		std::atomic<TimeConfig> m_elapsedTime, m_remainingTime;

	};
}