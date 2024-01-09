#pragma once
#include <qstring.h>

using GameHistory = std::tuple<int, int, int>;

class User
{
public: 

    User();
    void setUsername(const std::string& username);
    void setLobbyCode(const std::string& lobbyCode);
    void setAdmin();

    QString getUsername();
    std::optional<QString> getLobbyCode();

    void AddGameHistory(int id, int id_game, int points);

    std::vector<GameHistory> GetGameHistory();

    //int GetGameId(GameHistory gameHistory) {
    //    return std::get<0>(gameHistory);
    //}

    //int GetPlayerId(GameHistory gameHistory) {
    //    return std::get<1>(gameHistory);
    //}

    //int GetPointsId(GameHistory gameHistory) {
    //    return std::get<2>(gameHistory);
    //}

private:
    QString m_username;
    bool m_isAdmin;
    std::optional<QString> m_lobbyCode;
    std::vector<GameHistory> m_gamesHistory;
    // game id
    // player id
    // poitns
};

