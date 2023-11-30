#include "Routing.h"
using namespace skribbl;

void skribbl::Routing::run(IGame::IGamePtr& game)
{
	/*
	we need route for login/register
	-route for creating the url for the game with game lobby code
	-route for chat getting the words from users
	-route for drowing
	-route for displaying leaderboard in left of every player and players username with it to display 
	*/
	CROW_ROUTE(m_app, "/login")(
		[/*get's database for users*/]()
		{
			return crow::response(200);
		}
		);
	CROW_ROUTE(m_app, "/register")(
		[/*get's database for users*/]()
		{
			return crow::response(200);
		}
		);
	CROW_ROUTE(m_app, "/create_lobby")(
		[&game]()
		{
			int lobbyCode = 0; // here i get the lobbyCode from the json, 0 is just for now
			game->setLobbyUrl(lobbyCode);

			std::string name; //here i get the name from the json
			game->addPlayer(name);
			return crow::response(200);
		}
		);
	CROW_ROUTE(m_app, "/start")(
		[&game]()
		{
			/* when you press the start button the game will start*/
			game->start();
			return crow::response(200);
		}
		);




	m_app.port(18080).multithreaded().run();
}
