import <iostream>;
import <format>;
import igame;

#include "Login.h"

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

	auto storage = sql::make_storage("database.sqlite",
		skribbl::Login::getTableDefinition());
	storage.sync_schema();
	std::string username, password;

	std::cout<< "Username: ";
	std::cin >> username;
	std::cout<< "Password: ";
	std::cin>> password;

	skribbl::Login login1(username, password);
	storage.replace(login1);

	std::cout<<"Username: "<<login1.getUsername()<<"\n";

	IGamePtr game = IGame::Factory();
	
	game->start();

	// how to use new methods of wordHandler from main
	// in order to implement the methods from main there should be defined in game class getWord() and probably a similar methos in turn too
	//WordHandler wh("wordsFile.txt");
	//std::cout << getWordPattern(wh.getWord().length()) << "\n";
	//std::cout << getHint(wh.getWord().length(), wh.getHint());

	return 0;
}