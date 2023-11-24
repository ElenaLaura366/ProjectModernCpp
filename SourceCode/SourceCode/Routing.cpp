#include "Routing.h"

using namespace skribbl;

void skribbl::Routing::run()
{
	/*
	we need route for login/register
	-route for creating the url for the game with game lobby code
	-route for chat getting the words from users
	-route for drowing
	-route for displaying leaderboard in lest of every player and players username with it to display
	them in gui


	*/
	CROW_ROUTE(m_app, "/login")(
		[/*get's database for users*/]()
		{


		}
		);


	m_app.port(18080).multithreaded().run();
}
