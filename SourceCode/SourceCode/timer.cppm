module;
export module timer;

import <thread>;
import <chrono>;
import <atomic>;
import <mutex>;

namespace skribbl
{
	export class Timer
	{
	public:
		using TimeConfig = std::chrono::milliseconds;

	public:
		Timer();

		Timer(const Timer& other) = delete;
		Timer& operator=(const Timer& other) = delete;

		~Timer() = default;

		void start();
		void pause();
		void restart();
		void stop();

		uint8_t getElapsedTime() const;

	private:
		std::thread m_timerThread;
		std::condition_variable m_condition;
		std::mutex m_mutex;

		std::atomic<bool> m_isRunning;
		std::atomic<TimeConfig> m_duration;
		std::atomic<TimeConfig> m_elapsedTime;


	};
}