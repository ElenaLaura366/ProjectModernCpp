#include "WaitingRoom.h"

WaitingRoom::WaitingRoom(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::WaitingRoomClass())
{
	ui->setupUi(this);
	
	connect(ui->startGame, &QPushButton::clicked, this, &WaitingRoom::ChangeToGamePage);

}


void WaitingRoom::ChangeToGamePage() {
	emit goToGame();
}

WaitingRoom::~WaitingRoom()
{
	delete ui;
}

void WaitingRoom::SetRoomCode(QString lobbyCode)
{
	ui->label_2->setText(lobbyCode);
}
