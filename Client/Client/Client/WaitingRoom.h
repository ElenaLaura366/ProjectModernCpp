#pragma once

#include <QWidget>
#include <QListWidgetItem>
#include "ui_WaitingRoom.h"
#include "User.h"
#include "UserWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class WaitingRoomClass; };
QT_END_NAMESPACE

class WaitingRoom : public QWidget
{
	Q_OBJECT

public:
	WaitingRoom(QWidget *parent = nullptr);
	~WaitingRoom();
	void SetRoomCode(QString lobbyCode);
	void addUserToRoom(const User& user);

private slots:
	void ChangeToGamePage();

signals:
	void goToGame();

private:
	Ui::WaitingRoomClass *ui;
};
