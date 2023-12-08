#include "LobbyPage.h"

LobbyPage::LobbyPage(QWidget *parent)
	: QWidget{ parent }
	, ui{ new Ui::LobbyClass() }
{
	ui->setupUi(this);

	connect(ui->logoutBtn, &QPushButton::clicked, this, &LobbyPage::ChangeToLoginPage);
	connect(ui->createLobbyBtn, &QPushButton::clicked, this, &LobbyPage::ChangeToGamePage);
	connect(ui->joinLobbyBtn, &QPushButton::clicked, this, &LobbyPage::ChangeToGamePage);

}

LobbyPage::~LobbyPage()
{
	delete ui;
}

void LobbyPage::ChangeToGamePage()
{
	emit goToGamePage();
}

void LobbyPage::ChangeToLoginPage()
{
	emit goToLoginPage();
}
