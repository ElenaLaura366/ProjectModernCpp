#include <iostream>
#include "WordGenerator.h"


int main() {

	WordGenerator wg("Words.txt");
	for (int i = 0; i < 4; i++)
	{
		std::cout << wg.GetWord() <<": ";
		while (wg.AvailableLetters())
		{
			std::cout << wg.GetLetter() << " ";
		}
		std::cout << "\n";
		wg.UpdateWordGenerator();
	}


	return 0;
}