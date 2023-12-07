#pragma once

#include <QWidget>
#include "ui_LoginPage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginPageClass; };
QT_END_NAMESPACE

enum class WindowState {
	LOGIN,
	REGISTER
};

class LoginPage : public QWidget
{
	Q_OBJECT

public:
	LoginPage(QWidget* parent = nullptr);
	~LoginPage();

protected:     
	void paintEvent(QPaintEvent* event) override;

private slots:
	void changeToLogin();
	void changeToRegister();
	void proceed();

signals:
	void loginSuccessful();

private:
	Ui::LoginPageClass* ui;
	WindowState m_windowState;
	void cleanTextFields();

};
