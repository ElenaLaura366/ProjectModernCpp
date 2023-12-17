#pragma once

#include <QWidget>
#include "ui_GamePage.h"
#include "Routing.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GamePageClass; };
QT_END_NAMESPACE

class GamePage : public QWidget
{
	Q_OBJECT

public:
	GamePage(QWidget *parent = nullptr, Routing* m_rt = nullptr);
	~GamePage();

	Ui::GamePageClass* GetUi();
	void paintEvent(QPaintEvent* e) override;

private:
	void UpdateChat(const QString& username, const QString& answer);

	void keyPressEvent(QKeyEvent* event) override;
	void OnSendAnswerBtnClicked();
	void OnUndoBtnClicked();
	void OnResetDrawingBtnClicked();
	void OnExitGameBtnClicked();

signals:
	void ExitGame();
	void SendAnswerToServer();

private:
	Ui::GamePageClass *ui;
	DrawingAreaWidget* m_drawingArea;
	Routing* m_rt;
};
