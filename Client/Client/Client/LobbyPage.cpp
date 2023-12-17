#include "LobbyPage.h"

LobbyPage::LobbyPage(QWidget *parent)
	: QWidget{ parent }
	, ui{ new Ui::LobbyClass() }
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

void LobbyPage::ChangeToGamePage()
{
	emit goToGamePage();
}

void LobbyPage::ChangeToLoginPage()
{
	emit goToLoginPage();
}

void LobbyPage::OnJoinLobbyClicked()
{
	emit SendJoinLobbyToServer();
}

void LobbyPage::OnCreateLobbyClicked()
{
	emit SendCreateLobbyToServer();
}
