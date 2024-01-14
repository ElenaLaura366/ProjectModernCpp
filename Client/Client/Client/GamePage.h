#pragma once

#include <QWidget>
#include "ui_GamePage.h"
#include "Routing.h"
#include "LeaderBoardWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GamePageClass; };
QT_END_NAMESPACE

class GamePage : public QWidget
{
	Q_OBJECT

public:
	GamePage(QWidget* parent = nullptr, Routing* m_rt = nullptr);
	~GamePage();

	Ui::GamePageClass* GetUi();
	void paintEvent(QPaintEvent* e) override;

private:
	void ShowLeaderBoard();

	void UpdateLeaderBoard();
	void UpdateChat(const std::vector<QString>& answers);
	void UpdateEndTurn();

	void keyPressEvent(QKeyEvent* event) override;
	void OnSendAnswerBtnClicked();
	void OnUndoBtnClicked();
	void OnResetDrawingBtnClicked();
	void OnExitGameBtnClicked();

signals:
	void ExitGame();
	void HandleEndGame();
	void SendAnswerToServer();

private:
	Ui::GamePageClass* ui;
	DrawingAreaWidget* m_drawingArea;
	LeaderBoardWidget* m_leaderBoard;
	Routing* m_rt;
	uint m_refreshCount;
	QString m_word;

	static const uint8_t kRefreshRate{ 5 };
	const QString kGameOverState { "Game Over" };
	const QString kWaitingState { "Waiting" };
};
