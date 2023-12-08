#include "LobbyPage.h"

LobbyPage::LobbyPage(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::LobbyClass())
{
	ui->setupUi(this);

	connect(ui->logoutBtn, &QPushButton::clicked, this, &LobbyPage::changeToLoginPage);
}

LobbyPage::~LobbyPage()
{
	delete ui;
}

void LobbyPage::changeToLoginPage()
{
	emit goToLoginPage();
}
