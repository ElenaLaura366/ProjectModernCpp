#include "Database.h"

/*skribbl::Database::Database(Storage& db)
	: m_db{ db }
{}*/

skribbl::Database::Database()
{
	std::ofstream f("output.txt");
	 f<< "Copie\n";
	 f.close();
}

bool skribbl::Database::Initialize(const std::string& fileName)
{
	m_db.sync_schema();
	auto initWordsCount = m_db.count<Words>();
	if (initWordsCount == 0)
		PopulateStorage(fileName);

	auto wordsCount = m_db.count<Words>();
	return wordsCount != 0;
}

bool skribbl::Database::CheckUserExists(const std::string& username)
{
	auto user = m_db.get_all<User>(sql::where(sql::c(&User::m_username) == username));
	return !user.empty();
}

void skribbl::Database::CreateNewUser(const std::string& username, const std::string& password)
{
	m_db.insert(User{ -1, username, password, 0 });
}

std::optional<skribbl::User> skribbl::Database::AuthenticateUser(const std::string& username, const std::string& password)
{
	auto users = m_db.get_all<User>(sql::where(sql::c(&User::m_username) == username));
	if (!users.empty())
	{
		const auto& user = users.front();
		if (user.m_password == password)
		{
			return user;
		}
	}
	return std::nullopt;
}

std::vector<int> skribbl::Database::GetIdWords()
{
	return m_db.select(&Words::m_id);
}

std::string skribbl::Database::GetWord(int id)
{
	return m_db.select(&Words::m_word, sql::where(sql::c(&Words::m_id) == id)).front();
}

void skribbl::Database::AddGames(year_month_day date)
{
	m_db.insert(Games{ -1, date });
}

std::vector<skribbl::Games> skribbl::Database::GetGames()
{
	return m_db.get_all<Games>();
}

year_month_day skribbl::Database::CurrentDate()
{
	auto now = system_clock::now();
	auto current_time = system_clock::to_time_t(now); // Convert to time_t

	// Use localtime_s for a safer alternative to localtime
	std::tm local_time{};
	localtime_s(&local_time, &current_time);

	// Ensure safe conversion to unsigned int
	auto year = local_time.tm_year + 1900;
	auto month = static_cast<unsigned int>(local_time.tm_mon + 1);
	auto day = static_cast<unsigned int>(local_time.tm_mday);

	std::chrono::year_month_day currentDate{ std::chrono::year{year},
											std::chrono::month{month},
											std::chrono::day{day} };

	return currentDate;
}

void skribbl::Database::PopulateStorage(const std::string& fileName)
{
	std::vector <Words> words;
	std::ifstream fin(fileName);
	if (!fin.is_open())
	{
		throw std::exception("File was unable to be oppened"); // TODO: treat this exception
	}
	else
	{
		std::string word;
		while (fin >> word)
		{
			words.push_back({ -1, word });
		}
		fin.close();
		m_db.insert_range(words.begin(), words.end());
	}
}

void skribbl::Database::AddGameHistory(int playerId, int gameId, int points)
{
	if (!UserExists(playerId)) {
		throw std::exception("User ID does not exist."); //schimba
	}

	if (!GameExists(gameId)) {
		throw std::exception("Game ID does not exist.");
	}

	try {
		m_db.insert(GameHistory{-1,std::make_unique<int>(playerId) ,std::make_unique<int>(gameId) ,points });
	}
	catch (const std::exception& e) {
		throw std::exception("Error adding game history");
	}
}

bool skribbl::Database::UserExists(int userId)
{
	return m_db.count<User>(sqlite_orm::where(sqlite_orm::c(&User::m_id) == userId)) > 0;
}

bool skribbl::Database::GameExists(int gameId)
{
	return m_db.count<Games>(sqlite_orm::where(sqlite_orm::c(&Games::m_id) == gameId)) > 0;
}

std::vector<skribbl::GameHistory> skribbl::Database::GetGameHistory(int userId)
{
	return m_db.get_all<GameHistory>(sqlite_orm::where(sqlite_orm::c(&GameHistory::m_id_player) == userId));
}
