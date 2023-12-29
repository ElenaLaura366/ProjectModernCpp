#include "Client.h"

#include <QPushButton>

Client::Client(QWidget* parent)
	: QMainWindow{ parent },
	ui{ new Ui::ClientClass }
{
	ui->setupUi(this);

	m_stackedWidget = ui->centralWidget->findChild<QStackedWidget*>("stackedWidget");
	ui->mainToolBar->hide();
	ui->menuBar->hide();
	ui->mainToolBar->setStyleSheet("background: transparent;");


	m_loginPage = new LoginPage(this);
	m_gamePage = new GamePage(this, &m_rt);
	m_lobbyPage = new LobbyPage(this);
	m_waitingRoom = new WaitingRoom(this);
	m_userInfo = new UserInfo();

	m_stackedWidget->addWidget(m_gamePage);
	m_stackedWidget->addWidget(m_lobbyPage);
	m_stackedWidget->addWidget(m_loginPage);
	m_stackedWidget->addWidget(m_waitingRoom);

	setCentralWidget(m_stackedWidget);

	connect(m_lobbyPage, &LobbyPage::goToLoginPage, this, &Client::ChangeToLoginPage);
	//connect(m_lobbyPage, &LobbyPage::goToGamePage, this, &Client::ChangeToGamePage);
	connect(m_lobbyPage, &LobbyPage::SendCreateLobbyToServer, this, &Client::HandleCreateLobby);
	connect(m_lobbyPage, &LobbyPage::SendJoinLobbyToServer, this, &Client::HandleJoinLobby);
	connect(m_gamePage, &GamePage::SendAnswerToServer, this, &Client::HandleAnswer);
	connect(m_gamePage, &GamePage::ExitGame, this, &Client::ExitGame);
	
	connect(m_waitingRoom, &WaitingRoom::goToGame, this, &Client::ChangeToGamePage);

	connect(m_loginPage, &LoginPage::loginSuccessful, this, &Client::ChangeToLobbyPage);
	connect(m_loginPage, &LoginPage::SendLoginToServer, this, &Client::HandleLogin);
	connect(m_loginPage, &LoginPage::SendRegisterToServer, this, &Client::HandleRegister); 

	QAction* menuAction = new QAction("Game history", this);
	QMenu* menuUsername = ui->menuUsername;
	menuUsername->addAction(menuAction);
	connect(menuAction, &QAction::triggered, this, &Client::ShowUserInfo);


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

void Client::ChangeToLobbyPage() {

	m_stackedWidget->setCurrentWidget(m_lobbyPage);
}

void Client::ChangeToWaitingRoom()
{
	auto optionalLobbyCode = user.getLobbyCode();
	if (!optionalLobbyCode.has_value()) {
		QMessageBox::information(nullptr, "Error", "Lobby Code is not set.");
		return;
	}

	QString lobbyCode = optionalLobbyCode.value();
	m_waitingRoom->SetRoomCode(lobbyCode);
	m_waitingRoom->addUserToRoom(user);
	m_stackedWidget->setCurrentWidget(m_waitingRoom);
}

void Client::ShowUserInfo()
{
	m_userInfo->setWindowTitle(user.getUsername() + "'s game history");
	m_userInfo->show();
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
	if (!m_rt.ExitGame())
		QMessageBox::information(nullptr, "Server Conection Problem", "Player did not exit game.");
	else
		ChangeToLobbyPage();
}

bool Client::ValidInput() {
	return true;
}

void Client::HandleLogin() {

	auto loginUi = m_loginPage->GetUi();

	std::string username = loginUi->inputUsername->text().toUtf8().constData();
	std::string password = loginUi->inputPsw->text().toUtf8().constData();

	if (m_rt.SendLogin(username, password) == true) {
		user.setUsername(username);
		QMessageBox::information(nullptr, "Title", "Hello " + user.getUsername());
		emit loginButtonClicked();
		ui->menuUsername->setTitle(user.getUsername());
		ui->mainToolBar->show();
		ui->menuBar->show();
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
		user.setUsername(username);

		QMessageBox::information(nullptr, "Title", "Your account has been registered successfully, " + user.getUsername());
		emit loginButtonClicked(); 
		ui->menuUsername->setTitle(user.getUsername());
		ui->mainToolBar->show();
		ui->menuBar->show();
	}
	else {
		QMessageBox::information(nullptr, "Title", "An account with this username already exist");
	}
}

void Client::HandleCreateLobby()
{
	auto lobbyUiUser = m_loginPage->GetUi();
	user.setAdmin();

	std::string lobbyName = lobbyUiUser->inputUsername->text().toUtf8().constData();

	if (!m_rt.SendCreateLobby(lobbyName)) {
		QMessageBox::information(nullptr, "Server Conection Problem", "Lobby not created."); //de revizuit
	}
	if (m_rt.SendCreateLobby(lobbyName)) {
		user.setLobbyCode(m_rt.GetLobbyCode());
		ChangeToWaitingRoom();
	}
}

void Client::HandleJoinLobby()
{
	auto lobbyUi = m_lobbyPage->GetUi();
	std::string lobbyName = lobbyUi->lobbyCode->text().toUtf8().constData();
	user.setLobbyCode(lobbyName);

	if (!m_rt.SendJoinLobby(lobbyName)) {
		QMessageBox::information(nullptr, "Server Conection Problem", "Lobby not joined.");
		return;
	}
	else {
		ChangeToWaitingRoom();
	}
}

