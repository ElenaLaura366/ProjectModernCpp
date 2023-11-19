#include "crow.h"
import <iostream>;
import <format>;
import igame;

#include "Register.h"
#include <sqlite_orm/sqlite_orm.h>

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

// We'll where we'll put the following code


struct Word {
	int id;
	std::string name;
};

inline auto createWord(const std::string& filename) {
	return sql::make_storage(
		filename,
		sql::make_table(
			"Words",
			sql::make_column("id", &Word::id, sql::primary_key().autoincrement()),
			sql::make_column("word", &Word::name)
		)
	);
}

using WordsTable = decltype(createWord(""));

void populateWords(WordsTable& storage) {
	std::vector<Word> words{
		{-1, "elephant"},
		{-1, "apple"},
		{-1, "mirror"},
		{-1, "mouse"},
		{-1, "onion"}
	};
	storage.insert_range(words.begin(), words.end());
}

int main() {

	const std::string db_file = "database.sqlite";
	const std::string db_filew = "database-words.sqlite";
	UserTable db = createUser(db_file);
	WordsTable dbw = createWord(db_filew);
	db.sync_schema();
	dbw.sync_schema();


	IGame::IGamePtr game = IGame::Factory();
	
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
	//
	//std::cout << getWordPattern(wh.getWord().length()) << "\n";
	//std::cout << getHint(wh.getWord().length(), wh.getHint());

	return 0;
}