#pragma once
#include <crow.h>
import igame;
import <vector>;

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
