#include "WaitingRoom.h"

WaitingRoom::WaitingRoom(QWidget* parent)
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

void WaitingRoom::addUserToRoom(const User& user)
{
	UserWidget* userWidget = new UserWidget(user, this);

	QListWidgetItem* item = new QListWidgetItem();
	item->setSizeHint(userWidget->sizeHint());
	ui->listWidget->addItem(item);
	ui->listWidget->setItemWidget(item, userWidget);
}

void WaitingRoom::UpdatePlayerList(const std::vector<User>& players) 
{
	ui->listWidget->clear();
	for (const auto& player : players) {
		UserWidget* userWidget = new UserWidget(player, this);
		QListWidgetItem* item = new QListWidgetItem();
		item->setSizeHint(userWidget->sizeHint());
		ui->listWidget->addItem(item);
		ui->listWidget->setItemWidget(item, userWidget);
	}
}

void WaitingRoom::FetchPlayers() 
{
	std::string stdLobbyCode = lobbyCode.toStdString();
	std::vector<User> players = m_rt->GetPlayers(stdLobbyCode);
	UpdatePlayerList(players);
}