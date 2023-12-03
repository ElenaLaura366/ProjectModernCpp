#include "LoginPage.h"

LoginPage::LoginPage(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::LoginPageClass())
	, m_windowState(WindowState::LOGIN)
{
	ui->setupUi(this);
	//connect(ui->btnLogin, &QPushButton::clicked, this, &LoginPage::changeToLogin);
	//connect(ui->btnRegister, &QPushButton::clicked, this, &LoginPage::changeToRegister);
}

LoginPage::~LoginPage()
{
	delete ui;
}

