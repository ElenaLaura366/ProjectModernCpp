#pragma once

#include <QWidget>
#include "ui_LobbyPage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LobbyClass; };
QT_END_NAMESPACE

class LobbyPage : public QWidget
{
	Q_OBJECT

public:
	LobbyPage(QWidget *parent = nullptr);
	~LobbyPage();

private slots:
	void changeToLoginPage();

signals:
	void goToLoginPage();

private:
	Ui::LobbyClass *ui;
};
