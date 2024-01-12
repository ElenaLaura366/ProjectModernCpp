#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QStackedWidget>
#include <QMessageBox>

#include "ui_Client.h"
#include "LoginPage.h"
#include "GamePage.h"
#include "LobbyPage.h"
#include "UserInfo.h"
#include "WaitingRoom.h"
#include "User.h"

#include "Routing.h"


class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget *parent = nullptr);
    ~Client() = default;

    void closeEvent(QCloseEvent* event) override;

private slots:
    void ChangeToLoginPage();
    void ChangeToGamePage();
    void ChangeToLobbyPage();
    void ChangeToWaitingRoom();
    void ShowUserInfo();

    void HandleAnswer();
    void HandleLogin();
    void HandleRegister();
    void HandleCreateLobby();
    void HandleJoinLobby();
    // void handeStartGame() // when the game has been started? 
    void ExitGame();

private:
    bool ValidInput();
    User user;
    
private:
    Ui::ClientClass* ui;
    QStackedWidget* m_stackedWidget;
    LoginPage* m_loginPage;
    GamePage* m_gamePage;
    LobbyPage* m_lobbyPage;
    UserInfo* m_userInfo;
    WaitingRoom* m_waitingRoom;


    Routing m_rt;

signals:
    void loginButtonClicked();

};

#endif