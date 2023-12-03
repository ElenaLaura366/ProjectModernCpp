#pragma once
#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>
#include <QPainter>


class LoginPage  : public QWidget
{
	Q_OBJECT

public:
	LoginPage(QWidget *parent = nullptr);
	~LoginPage();
	void paintEvent(QPaintEvent* event);

signals:
	void loginSuccessful();

};

#endif