#include "Client.h"

#include <QPushButton>

Client::Client(QWidget *parent)
    : QMainWindow(parent), 
    ui(new Ui::ClientClass)
{
    ui->setupUi(this);

    stackedWidget = ui->centralWidget->findChild<QStackedWidget*>("stackedWidget");

    loginPage = new LoginPage(this);
    gamePage = new GamePage(this);
    lobbyPage = new LobbyPage(this);

    stackedWidget->addWidget(gamePage);
    stackedWidget->addWidget(lobbyPage);
    stackedWidget->addWidget(loginPage);
    
    setCentralWidget(stackedWidget);
    
    connect(loginPage, &LoginPage::loginSuccessful, this, &Client::changeToLobbyPage);
    connect(lobbyPage, &LobbyPage::goToLoginPage, this, &Client::changeToLoginPage);

    //connect(ui->btnLoginPage, &QPushButton::clicked, this, &Client::changeToLoginPage);
    //connect(ui->btnGamePage, &QPushButton::clicked, this, &Client::changeToGamePage);

    changeToLoginPage();
}

Client::~Client()
{}

void Client::changeToLoginPage() {
    stackedWidget->setCurrentWidget(loginPage);
}

void Client::changeToGamePage() {
    stackedWidget->setCurrentWidget(gamePage);
}

void Client::changeToLobbyPage(){
    stackedWidget->setCurrentWidget(lobbyPage);
}

bool Client::validInput() {
    return true;
}