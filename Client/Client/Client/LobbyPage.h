#pragma once

#include <QWidget>
#include "ui_LobbyPage.h"
#include "Routing.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LobbyClass; };
QT_END_NAMESPACE

class LobbyPage : public QWidget
{
	Q_OBJECT

public:
	LobbyPage(QWidget *parent = nullptr, std::shared_ptr<Routing> rt = nullptr);
	~LobbyPage();

	Ui::LobbyClass* GetUi();

private slots:
	void ChangeToLoginPage();
	void OnJoinLobbyClicked();
	void OnCreateLobbyClicked();

signals:
	void GoToLoginPage();
	void GoToWaitingRoom();

private:
	Ui::LobbyClass *ui;
	std::shared_ptr<Routing> m_rt;
};
