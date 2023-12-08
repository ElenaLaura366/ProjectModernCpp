#include "LobbyPage.h"

LobbyPage::LobbyPage(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::LobbyClass())
{
	ui->setupUi(this);

	connect(ui->logoutBtn, &QPushButton::clicked, this, &LobbyPage::changeToLoginPage);
	connect(ui->createLobbyBtn, &QPushButton::clicked, this, &LobbyPage::changeToGamePage);
	connect(ui->joinLobbyBtn, &QPushButton::clicked, this, &LobbyPage::changeToGamePage);

}

LobbyPage::~LobbyPage()
{
	delete ui;
}

void LobbyPage::changeToGamePage()
{
	emit goToGamePage();
}

void LobbyPage::changeToLoginPage()
{
	emit goToLoginPage();
}
