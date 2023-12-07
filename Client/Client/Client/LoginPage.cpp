#include "LoginPage.h"

LoginPage::LoginPage(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::LoginPageClass())
	, m_windowState(WindowState::LOGIN)
{
	ui->setupUi(this);
	connect(ui->btnLogin, &QPushButton::clicked, this, &LoginPage::changeToLogin);
	connect(ui->btnRegister, &QPushButton::clicked, this, &LoginPage::changeToRegister);
	connect(ui->btnProceed, &QPushButton::clicked, this, &LoginPage::proceed);
	ui->lineEdit_2->setEchoMode(QLineEdit::Password);
	ui->lineEdit_3->setEchoMode(QLineEdit::Password);
}

LoginPage::~LoginPage()
{
	delete ui;
}

void LoginPage::changeToLogin()
{
	if (m_windowState != WindowState::LOGIN) {
		cleanTextFields();
	}
	m_windowState = WindowState::LOGIN;
}

void LoginPage::changeToRegister()
{
	if (m_windowState != WindowState::REGISTER) {
		cleanTextFields();
	}
	m_windowState = WindowState::REGISTER;
}

void LoginPage::paintEvent(QPaintEvent* event){
	if (m_windowState == WindowState::LOGIN) {
		ui->title->setText("Please Login in order to enter the game");
		ui->btnProceed->setText("LOGIN");
		ui->lineEdit_3->setVisible(false);
		ui->label_3->setVisible(false);
		// de adaugat linia
	}
	else {
		ui->title->setText("Please Register in order to enter the game");
		ui->btnProceed->setText("REGISTER");
		ui->lineEdit_3->setVisible(true);
		ui->label_3->setVisible(true);
	}
}

void LoginPage::cleanTextFields() {
	ui->lineEdit->setText("");
	ui->lineEdit_2->setText("");
	ui->lineEdit_3->setText("");
}

void LoginPage::proceed() {
	emit loginSuccessful();
}