#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QStackedWidget>
#include "ui_Client.h"
#include "LoginPage.h"
#include "GamePage.h"
#include "LobbyPage.h"


class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget *parent = nullptr);
    ~Client() = default;

private slots:
    void ChangeToLoginPage();
    void ChangeToGamePage();
    void ChangeToLobbyPage();

private:
    bool ValidInput();

private:
    Ui::ClientClass* ui;
    QStackedWidget* m_stackedWidget;
    LoginPage* m_loginPage;
    GamePage* m_gamePage;
    LobbyPage* m_lobbyPage;

signals:
    void loginButtonClicked();
};

#endif