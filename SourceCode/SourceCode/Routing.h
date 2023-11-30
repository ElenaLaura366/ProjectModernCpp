#pragma once
#include <crow.h>
import igame;

namespace skribbl
{
	class Routing
	{
	public:
		void run(IGame::IGamePtr& game);

	private:
		crow::SimpleApp m_app;
	};
}
