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
    connect(m_gamePage, &GamePage::goToLobbyPage, this, &Client::ChangeToLobbyPage);

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

bool Client::ValidInput() {
    return true;
}