#pragma once
#include <crow.h>

namespace skribbl
{
	class Routing
	{
	public:
		void run();

	private:
		crow::SimpleApp m_app;
	};
}
