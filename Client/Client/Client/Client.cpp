#include "Client.h"

#include <QPushButton>

Client::Client(QWidget *parent)
    : QMainWindow{ parent },
    ui{ new Ui::ClientClass }
{
    ui->setupUi(this);

    m_stackedWidget = ui->centralWidget->findChild<QStackedWidget*>("stackedWidget");

    m_loginPage = new LoginPage(this);
    m_gamePage = new GamePage(this);
    m_lobbyPage = new LobbyPage(this);

    m_stackedWidget->addWidget(m_gamePage);
    m_stackedWidget->addWidget(m_lobbyPage);
    m_stackedWidget->addWidget(m_loginPage);
    
    setCentralWidget(m_stackedWidget);
    
    connect(m_loginPage, &LoginPage::loginSuccessful, this, &Client::ChangeToLobbyPage);
    connect(m_lobbyPage, &LobbyPage::goToLoginPage, this, &Client::ChangeToLoginPage);
    connect(m_lobbyPage, &LobbyPage::goToGamePage, this, &Client::ChangeToGamePage);
    connect(m_gamePage, &GamePage::ExitGame, this, &Client::ChangeToLobbyPage);
    connect(m_gamePage, &GamePage::ExitGame, this, &Client::ExitGame);
    connect(m_gamePage, SIGNAL(GamePage::SendAnswerToServer(const std::string&)), this, SLOT(Client::HandleAnswer(const std::string&)));
    connect(m_loginPage, SIGNAL(LoginPage::SendLoginToServer(const std::string&, const std::string&)), this, SLOT(Client::HandleLogin(const std::string&, const std::string&)));
    connect(m_loginPage, SIGNAL(LoginPage::SendRegisterToServer(const std::string&, const std::string&)), this, SLOT(Client::HandleRegister(const std::string&, const std::string&)));

    m_rt.SendLogin("admin", "123");
    
    ChangeToLoginPage();
}

void Client::ChangeToLoginPage() {
    m_stackedWidget->setCurrentWidget(m_loginPage);
}

void Client::ChangeToGamePage() {
    m_stackedWidget->setCurrentWidget(m_gamePage);
}

void Client::ChangeToLobbyPage(){
    
    m_stackedWidget->setCurrentWidget(m_lobbyPage);
}

void Client::HandleAnswer(const std::string& answer)
{
    m_rt.SendAnswer(answer);
}

void Client::ExitGame()
{
    m_rt.ExitGame();
}

bool Client::ValidInput() {
    return true;
}

void Client::HandleLogin(const std::string& username, const std::string& password) {
    m_rt.SendLogin(username, password);
}


void Client::HandleRegister(const std::string& username, const std::string& password) {
    m_rt.SendRegister(username, password);
}