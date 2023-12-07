#pragma once

#include <QWidget>
#include "ui_GamePage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GamePageClass; };
QT_END_NAMESPACE

class GamePage : public QWidget
{
	Q_OBJECT

public:
	GamePage(QWidget *parent = nullptr);
	~GamePage();

private:
	Ui::GamePageClass *ui;
};
