#pragma once

#include <QWidget>
#include "ui_LoginPage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginPageClass; };
QT_END_NAMESPACE

class LoginPage : public QWidget
{
	Q_OBJECT

public:
	LoginPage(QWidget *parent = nullptr);
	~LoginPage();

private:
	Ui::LoginPageClass *ui;
	enum class WindowState{
		LOGIN, 
		REGISTER
	};

	WindowState m_windowState;
//
//private slots:
//	void changeToLogin();
//	void changeToRegister();

//signals:
//	void loginSuccessful();

};
