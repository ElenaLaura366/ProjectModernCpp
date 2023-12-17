#include "Client.h"

#include <QPushButton>

Client::Client(QWidget *parent)
    : QMainWindow{ parent },
    ui{ new Ui::ClientClass }
{
    ui->setupUi(this);

    m_stackedWidget = ui->centralWidget->findChild<QStackedWidget*>("stackedWidget");

    m_loginPage = new LoginPage(this);
    m_gamePage = new GamePage(this, &m_rt);
    m_lobbyPage = new LobbyPage(this);

    m_stackedWidget->addWidget(m_gamePage);
    m_stackedWidget->addWidget(m_lobbyPage);
    m_stackedWidget->addWidget(m_loginPage);
    
    setCentralWidget(m_stackedWidget);
    
    connect(m_lobbyPage, &LobbyPage::goToLoginPage, this, &Client::ChangeToLoginPage);
    connect(m_lobbyPage, &LobbyPage::goToGamePage, this, &Client::ChangeToGamePage);
     
    connect(m_gamePage, &GamePage::SendAnswerToServer, this, &Client::HandleAnswer);
    connect(m_gamePage, &GamePage::ExitGame, this, &Client::ExitGame);
    
    connect(m_loginPage, &LoginPage::loginSuccessful, this, &Client::ChangeToLobbyPage);
    connect(m_loginPage, &LoginPage::SendLoginToServer, this, &Client::HandleLogin);
    connect(m_loginPage, &LoginPage::SendRegisterToServer, this, &Client::HandleRegister);
    
    ChangeToLoginPage();
}

void Client::paintEvent(QPaintEvent* e)
{
    auto ceva = 0;
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

void Client::HandleAnswer()
{
    auto gameUi = m_gamePage->GetUi();
    std::string answer = gameUi->chatInput->text().toUtf8().constData();
    gameUi->chatInput->clear();

    if (!m_rt.SendAnswer(answer))
        QMessageBox::information(nullptr, "Server Conection Problem", "Answert not sent.");

}

void Client::ExitGame()
{
    if(!m_rt.ExitGame())
        QMessageBox::information(nullptr, "Server Conection Problem", "Player did not exit game.");
    else
        ChangeToLobbyPage();
}

bool Client::ValidInput() {
    return true;
}

void Client::HandleLogin(){
    
    auto loginUi = m_loginPage->GetUi();

    std::string username = loginUi->inputUsername->text().toUtf8().constData();
    std::string password = loginUi->inputPsw->text().toUtf8().constData();
 
    if (m_rt.SendLogin(username, password) == true) {
        QMessageBox::information(nullptr, "Title", "This is a simple message box.");
        emit loginButtonClicked();
    }
    else {
        QMessageBox::information(nullptr, "Title", "Wrong credentials.");
    }
}

void Client::HandleRegister() {

    auto loginUi = m_loginPage->GetUi();

    std::string username = loginUi->inputUsername->text().toUtf8().constData();
    std::string password = loginUi->inputPsw->text().toUtf8().constData();


    if (m_rt.SendRegister(username, password) == true) {
        QMessageBox::information(nullptr, "Title", "Your account has been registered successfully");
        emit loginButtonClicked();
    }
    else {
        QMessageBox::information(nullptr, "Title", "Something went wrong");
    }
}