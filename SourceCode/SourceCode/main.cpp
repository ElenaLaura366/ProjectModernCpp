#include "crow.h"
import <iostream>;
import <format>;
import igame;

#include "Register.h"

using namespace skribbl;

std::string getWordPattern(int size) {
	std::string pattern(size, '_');
	return pattern;
}

std::string getHint(int size, const std::vector<std::pair<int, char>> hints) {
	std::string pattern(size, '_');
	for (auto& el : hints) {
		pattern[el.first] = el.second;
	}
	return pattern;
}

int main() {

	const std::string db_file = "database.sqlite";
	UserTable db = createUser(db_file);
	db.sync_schema();

	IGamePtr game = IGame::Factory();
	
	/*crow::SimpleApp app;

	CROW_ROUTE(app, "/<string>").methods("PUT"_method)(
		[&game](const std::string& name)
		{
			game->addPlayer(name);
			return "Adaugat!";
		}
	);
	
	app.port(18080).multithreaded().run();*/

	game->start();




	// how to use new methods of wordHandler from main
	// in order to implement the methods from main there should be defined in game class getWord() and probably a similar methos in turn too
	//WordHandler wh("wordsFile.txt");
	//std::cout << getWordPattern(wh.getWord().length()) << "\n";
	//std::cout << getHint(wh.getWord().length(), wh.getHint());

	return 0;
}