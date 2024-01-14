#include "LobbyPage.h"
#include <QMessageBox>

LobbyPage::LobbyPage(QWidget* parent, std::shared_ptr<Routing> rt)
	: QWidget{ parent }
	, ui{ new Ui::LobbyClass() }
	, m_rt{ rt }
{
	ui->setupUi(this);

	connect(ui->logoutBtn, &QPushButton::clicked, this, &LobbyPage::ChangeToLoginPage);
	connect(ui->joinLobbyBtn, &QPushButton::clicked, this, &LobbyPage::OnJoinLobbyClicked);
	connect(ui->createLobbyBtn, &QPushButton::clicked, this, &LobbyPage::OnCreateLobbyClicked);
}

LobbyPage::~LobbyPage()
{
	delete ui;
}

Ui::LobbyClass* LobbyPage::GetUi()
{
	return ui;
}

void LobbyPage::ChangeToLoginPage()
{
	emit GoToLoginPage();
}

void LobbyPage::OnJoinLobbyClicked()
{
	if (ui->lobbyCode->text().isEmpty()) {
		QMessageBox::warning(nullptr, "Title", "LobbyCode field is null");
		return;
	}

	std::string lobbyCode = ui->lobbyCode->text().toUtf8().constData();
	if (!m_rt->SendJoinLobby(lobbyCode)) {
		QMessageBox::information(nullptr, "Server Conection Problem", "Lobby not joined.");
		return;
	} 
	else {
		GoToWaitingRoom();
	}
}

void LobbyPage::OnCreateLobbyClicked()
{
	std::string lobbyName = m_rt->GetPlayerName();

	if (!m_rt->SendCreateLobby(lobbyName)) {
		QMessageBox::information(nullptr, "Server Conection Problem", "Lobby not created."); //de revizuit
	}
	else {
		GoToWaitingRoom();
	}
}
