#include "LobbyPage.h"

LobbyPage::LobbyPage(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::LobbyClass())
{
	ui->setupUi(this);
}

LobbyPage::~LobbyPage()
{
	delete ui;
}
