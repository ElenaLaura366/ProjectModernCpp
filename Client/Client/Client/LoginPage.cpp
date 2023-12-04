#include "LoginPage.h"

LoginPage::LoginPage(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::LoginPageClass())
	, m_windowState(WindowState::LOGIN)
{
	ui->setupUi(this);
	connect(ui->btnLogin, &QPushButton::clicked, this, &LoginPage::changeToLogin);
	connect(ui->btnRegister, &QPushButton::clicked, this, &LoginPage::changeToRegister);
}

LoginPage::~LoginPage()
{
	delete ui;
}

void LoginPage::changeToLogin()
{
	m_windowState = WindowState::LOGIN;

}

void LoginPage::changeToRegister()
{
	m_windowState = WindowState::REGISTER;
}

void LoginPage::paintEvent(QPaintEvent* event){
	if (m_windowState == WindowState::LOGIN) {
		ui->title->setText("Please Login in order to enter the game");
		ui->btnProceed->setText("LOGIN");
		// de adaugat linia
	}
	else {
		ui->title->setText("Please Register in order to enter the game");
		ui->btnProceed->setText("REGISTER");
	}
}
