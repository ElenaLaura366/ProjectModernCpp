#include "Routing.h"
#include "Database.h"

int main()
{
    skribbl::Database db;
    //std::shared_ptr<skribbl::Database> db = std::make_shared<skribbl::Database>();

    if (!db.Initialize("wordsFile.txt"))
    {
		std::cout << "Failed to initialize database" << std::endl;
		return -1;
	}
    skribbl::Routing r(db);
    r.Run();

    return 0;
}