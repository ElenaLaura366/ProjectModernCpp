#pragma once
#include <qstring.h>

class User
{
public: 
    User();
    void setUsername(const std::string& username);
    void setLobbyCode(const std::string& lobbyCode);
    void setAdmin();

    QString getUsername();
    std::optional<QString> getLobbyCode();

    bool isAdmin();

private:
    QString m_username;
    bool m_isAdmin;
    std::optional<QString> m_lobbyCode;
};

