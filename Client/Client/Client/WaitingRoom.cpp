#include "WaitingRoom.h"

WaitingRoom::WaitingRoom(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::WaitingRoomClass())
{
	ui->setupUi(this);
	
	connect(ui->startGame, &QPushButton::clicked, this, &WaitingRoom::ChangeToGamePage);
	
	User currentUser1;
	currentUser1.setUsername("User1");
	User currentUser2;
	currentUser2.setUsername("User2");
	User currentUser3;
	currentUser3.setUsername("User3");
	User currentUser4;
	currentUser4.setUsername("User4");

	addUserToRoom(currentUser1);
	addUserToRoom(currentUser2);
	addUserToRoom(currentUser3);
	addUserToRoom(currentUser4);
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
	ui->listWidget->addItem(item); // Add the item to the list
	ui->listWidget->setItemWidget(item, userWidget);
}
