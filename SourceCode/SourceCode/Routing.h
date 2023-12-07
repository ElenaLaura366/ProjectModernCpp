#pragma once
#include <crow.h>
import igame;
import <vector>;
import <random>;
import <unordered_map>;

namespace skribbl
{
	class Routing
	{
	public:
		Routing() = default;
		~Routing() = default;
		Routing(const Routing& other) = delete;
		Routing& operator=(const Routing& other) = delete;
		Routing(Routing&& other) noexcept = delete;
		Routing& operator=(Routing&& other) noexcept = delete;
		
		void run();

		static const uint16_t kMinLobbyCode = 10000;
		static const uint16_t kMaxLobbyCode = 65535;

	private:
		crow::SimpleApp m_app;
	};
}
