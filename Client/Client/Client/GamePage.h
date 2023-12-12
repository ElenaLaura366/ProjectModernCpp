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
	void UpdateChat(const QString& username, const QString& answer);

	void keyPressEvent(QKeyEvent* event) override;
	void OnSendAnswerBtnClicked();
	void OnUndoBtnClicked();
	void OnResetDrawingBtnClicked();
	void OnExitGameBtnClicked();

signals:
	void ExitGame();
	void SendAnswerToServer(const std::string& answer);

private:
	Ui::GamePageClass *ui;
	DrawingAreaWidget* m_drawingArea;
};
