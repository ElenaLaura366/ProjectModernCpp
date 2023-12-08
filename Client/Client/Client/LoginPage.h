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

private:
	void cleanTextFields();

private slots:
	void ChangeToLogin();
	void ChangeToRegister();
	void Proceed();

signals:
	void loginSuccessful();

private:
	Ui::LoginPageClass* ui;
	WindowState m_windowState;
};
