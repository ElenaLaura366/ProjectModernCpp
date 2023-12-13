#include "Routing.h"
#include "Database.h"

int main()
{
    skribbl::Database db;
    db.Initialize("wordsFile.txt");
    /*
    auto now = system_clock::now();
    auto current_time = system_clock::to_time_t(now); // Convert to time_t

    // Use localtime_s for a safer alternative to localtime
    std::tm local_time{};
    localtime_s(&local_time, &current_time);

    // Ensure safe conversion to unsigned int
    auto year = local_time.tm_year + 1900;
    auto month = static_cast<unsigned int>(local_time.tm_mon);
    auto day = static_cast<unsigned int>(local_time.tm_mday);

    std::chrono::year_month_day currentDate{ std::chrono::year{year},  Trebuie sa mut astea in alta parte
                                            std::chrono::month{month},
                                            std::chrono::day{day} };

    // Add game with the current date
    db.AddGames(currentDate);

    std::vector<Games> gamesList = db.GetGames();
    for (const auto& game : gamesList)
    {
        std::cout << game.m_id << " " << game.m_date << "\n";
    }
    */
    skribbl::Routing r;
    r.Run();

    return 0;
}