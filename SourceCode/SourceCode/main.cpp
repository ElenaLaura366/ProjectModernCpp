#include "Routing.h"
#include "Database.h"

int main()
{
	skribbl::Database db;
	db.Initialize("wordsFile.txt");

	skribbl::Routing r;
	r.Run();

	return 0;
}