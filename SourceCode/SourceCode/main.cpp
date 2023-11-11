import <iostream>;
import <format>;
import igame;

using namespace skribbl;

int main() {
	//This is only for one turn
	//We get a sentence that describes a word and we should guess it, max 10 mistakes
	
	int16_t contor = 10;

	IGamePtr game = IGame::Factory();
	game->addPlayer("Ioana");
	game->start();

	//currentTurn->displaySentence()

	while (game->isRunning())
	{
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

	return 0;
}