#pragma once
#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>


class LoginPage  : public QWidget
{
	Q_OBJECT

public:
	LoginPage(QWidget *parent = nullptr);
	~LoginPage();

signals:
	void loginSuccessful();

};

#endif