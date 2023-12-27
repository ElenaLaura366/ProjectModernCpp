#pragma once

#include <QWidget>
#include "ui_WaitingRoom.h"

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

private slots:
	void ChangeToGamePage();

signals:
	void goToGame();

private:
	Ui::WaitingRoomClass *ui;
};
