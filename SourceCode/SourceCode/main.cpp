import <iostream>;
import <format>;
import igame;

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
	//This is only for one turn
	//We get a sentence that describes a word and we should guess it, max 10 mistakes
	//
	int16_t contor = 10;

	IGamePtr game = IGame::Factory();
	game->addPlayer("Ioana");
	game->start();

	//currentTurn->displaySentence()

	while (game->isRunning())
	{
		//game.getWord(); 
		if (contor == 5) 
		{
			//currentTurn->displayHint(), this should display the hint for the given word
		}

		std::cout << "Word: ";
		std::string word;
		std::cin >> word;

		if (game->verifyGuess(word))
		{
			std::cout << "\nYou win! Good job!\n";
			game->stop();
		}
		else
		{	
			contor--;
			std::cout << std::format("\nWrong! Try again!\nRemaining chances: {}\n\n", contor);
		}
		if (contor == 0)
		{
			std::cout << "\nYou lose! :( Next time mate!\n";
			game->stop();
		}
		
	}

	// how to use new methods of wordHandler from main
	// in order to implement the methods from main there should be defined in game class getWord() and probably a similar methos in turn too
	//WordHandler wh("wordsFile.txt");
	//std::cout << getWordPattern(wh.getWord().length()) << "\n";
	//std::cout << getHint(wh.getWord().length(), wh.getHint());

	return 0;
}