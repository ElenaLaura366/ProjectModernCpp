#include "crow.h"
import <iostream>;
import <format>;
import igame;
import wordhandler;

#include "Routing.h"
#include "Login.h"
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

std::optional<std::string> getWord(WordsTable& storage, int index) {
	int wordCount = storage.count<Word>();

	if (wordCount <= index) {
		return std::nullopt; // Index is out of bounds.
	}

	auto word = storage.get<Word>(index);

	return word.name;
}

void openWordDatabase() {
	const std::string db_filew = "database-words.sqlite";
	WordsTable dbw = createWord(db_filew);
	dbw.sync_schema();
	auto count = dbw.count<Word>();
	if (count == 0) {
		populateWords(dbw);
	}
	std::optional<std::string> result = getWord(dbw, 1);

	if (result.has_value()) {
		std::cout << "Word: " << result.value() << std::endl;
	}
	else {
		std::cout << "Word not found." << std::endl;
	}
}

int main() {

	WordHandler wh("wordsFile.txt");

	std::cout << getWordPattern(wh.getWord().length()) << "\n";
	//std::cout << getHint(wh.getWord().length(), wh.getHint());

	openWordDatabase();

	const std::string db_file = "database.sqlite";
	UserTable db = createUser(db_file);
	db.sync_schema();
	int option;
	std::cout<< "1. Register\n2. Login\n";
	std::cin >> option;
	while (option != 1 && option != 2) {
		std::cout << "Invalid option!\n";
		std::cin >> option;
	}

	if (option == 1)
	{
		std::cout<<"Username: ";
		std::string username;
		std::cin >> username;
		std::cout<<"Password: ";
		std::string password;
		std::cin >> password;
		Register reg(db);
		if (reg.checkUserExists(username))
		{
			std::cout<<"User already exists!\n";
		}
		else
		{
			reg.createNewUser(username, password);
			std::cout<<"User created!\n";
		}
	}
	else {
		std::cout << "Username: ";
		std::string username;
		std::cin >> username;
		std::cout << "Password: ";
		std::string password;
		std::cin >> password;
		Login log(db);
		if (log.authenticateUser(username, password).has_value())
		{
			std::cout << "User authenticated!\n";
		}
		else
		{
			std::cout << "User not found!\n";
		}
	}
	
	Routing r;
	r.run();



	// how to use new methods of wordHandler from main
	// in order to implement the methods from main there should be defined in game class getWord() and probably a similar methos in turn too


	return 0;
}