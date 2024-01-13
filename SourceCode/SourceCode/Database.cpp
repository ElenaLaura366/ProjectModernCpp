#include "Database.h"

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

int skribbl::Database::GetNumberOfWords()
{
	return m_db.count<Words>();
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

std::vector<std::tuple<int, std::string>> skribbl::Database::GetGameHistory(const std::string& username)
{
	auto userId = m_db.select(&User::m_id, sql::where(sql::c(&User::m_username) == username));

	std::vector<std::tuple<int, std::string>> gameHistory = m_db.select(sql::columns(&GameHistory::m_points, sql::strftime("%Y-%m-%d", &Games::m_date)), sql::inner_join<Games>(sql::on (sql::c(&GameHistory::m_id_game) == &Games::m_id)));

	return gameHistory;
}

void skribbl::Database::AddCustomWordToDatabase(const std::string& word)
{
	if(m_db.count<Words>(sql::where(sql::c(&Words::m_word) == word)) == 0)
		m_db.insert(Words{ -1, word });
}
