#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QStackedWidget>
#include "ui_Client.h"
#include "loginpage.h"
#include "gamepage.h"


class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget *parent = nullptr);
    ~Client();

private slots:
    void changeToLoginPage();
    void changeToGamePage();

private:
    Ui::ClientClass* ui;
    QStackedWidget* stackedWidget;
    LoginPage* loginPage;
    GamePage* gamePage;
};

#endif