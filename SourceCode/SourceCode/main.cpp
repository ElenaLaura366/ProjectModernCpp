#include "Routing.h"
#include "Database.h"

int main()
{
	skribbl::Database db;
	db.Initialize("wordsFile.txt");

	std::vector<int> words = db.GetIdWords();

	for(auto& word : words)
		std::cout << word << std::endl;

	skribbl::Routing r;
	r.Run();

	return 0;
}