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
    ~Client();

private slots:
    void changeToLoginPage();
    void changeToGamePage();
    void changeToLobbyPage();

private:
    bool validInput();

private:
    Ui::ClientClass* ui;
    QStackedWidget* stackedWidget;
    LoginPage* loginPage;
    GamePage* gamePage;
    LobbyPage* lobbyPage;

signals:
    void loginButtonClicked();
};

#endif