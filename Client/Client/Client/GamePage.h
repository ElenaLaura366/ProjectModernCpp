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

	void KeyPressEvent(QKeyEvent* event);

	void SendAnswer();
	void UpdateChat(const QString& username, const QString& answer);

private:
	void OnUndoBtnClicked();

private:
	Ui::GamePageClass *ui;
	DrawingAreaWidget* m_drawingArea;
};
