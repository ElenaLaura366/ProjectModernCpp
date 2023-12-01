#pragma once
#include <crow.h>
import igame;
import <vector>;
import <random>;

namespace skribbl
{
	class Routing
	{
	public:
		void run();

		static const uint16_t kMinLobbyCode = 10000;
		static const uint16_t kMaxLobbyCode = 65535;

	private:
		crow::SimpleApp m_app;
	};
}
