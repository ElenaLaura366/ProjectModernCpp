#pragma once
#include <crow.h>
#include <random>
#include <vector>
#include <unordered_map>
#include "IGame.h"

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
		static const uint16_t kmaxGamesSupported = 8;

	private:
		crow::SimpleApp m_app;
	};
}
