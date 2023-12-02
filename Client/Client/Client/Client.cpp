#include "Client.h"

#include <QPushButton>

Client::Client(QWidget *parent)
    : QMainWindow(parent)
{
    //ui->setupUi(this);

    //stackedWidget = ui->centralWidget->findChild<QStackedWidget*>("stackedWidget");

    //loginPage = new LoginPage(this);
    //gamePage = new GamePage(this);

    //stackedWidget->addWidget(loginPage);
    //stackedWidget->addWidget(gamePage);

    ////connect(ui->btnLoginPage, &QPushButton::clicked, this, &Client::changeToLoginPage);
    ////connect(ui->btnGamePage, &QPushButton::clicked, this, &Client::changeToGamePage);

    //changeToLoginPage();
}

Client::~Client()
{}

void Client::changeToLoginPage() {
    stackedWidget->setCurrentWidget(loginPage);
}

void Client::changeToGamePage() {
    stackedWidget->setCurrentWidget(gamePage);
}