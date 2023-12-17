#include "LoginPage.h"

LoginPage::LoginPage(QWidget *parent)
	: QWidget{ parent }
	, ui{ new Ui::LoginPageClass() }
	, m_windowState{ WindowState::LOGIN }
{
	ui->setupUi(this);
	connect(ui->btnLogin, &QPushButton::clicked, this, &LoginPage::ChangeToLogin);
	connect(ui->btnRegister, &QPushButton::clicked, this, &LoginPage::ChangeToRegister);
	connect(ui->btnProceed, &QPushButton::clicked, this, &LoginPage::Proceed);
	ui->inputPsw->setEchoMode(QLineEdit::Password);
	ui->inputPswConf->setEchoMode(QLineEdit::Password);
}

LoginPage::~LoginPage()
{
	delete ui;
}

Ui::LoginPageClass* LoginPage::GetUi()
{
	return ui;
}

void LoginPage::ChangeToLogin()
{
	if (m_windowState != WindowState::LOGIN) {
		cleanTextFields();
	}
	m_windowState = WindowState::LOGIN;
	update();
}

void LoginPage::ChangeToRegister()
{
	if (m_windowState != WindowState::REGISTER) {
		cleanTextFields();
	}
	m_windowState = WindowState::REGISTER;
	update();
}

void LoginPage::paintEvent(QPaintEvent* event){
	if (m_windowState == WindowState::LOGIN) {
		ui->title->setText("Please Login in order to enter the game");
		ui->btnProceed->setText("LOGIN");
		ui->inputPswConf->setVisible(false);
		ui->labelPswConf->setVisible(false);
		// de adaugat linia
	}
	else {
		ui->title->setText("Please Register in order to enter the game");
		ui->btnProceed->setText("REGISTER");
		ui->inputPswConf->setVisible(true);
		ui->labelPswConf->setVisible(true);
	}
}

void LoginPage::cleanTextFields() {
	ui->inputUsername->setText("");
	ui->inputPsw->setText("");
	ui->inputPswConf->setText("");
}

void LoginPage::Proceed() {

	if (m_windowState == WindowState::LOGIN) {
		OnLogin();
	}
	else {
		OnRegister();
	}
	emit loginSuccessful();
}


void LoginPage::OnLogin() {
	if (ui->inputUsername->text().isEmpty() || ui->inputPsw->text().isEmpty())
	{
		QMessageBox::warning(nullptr, "Title", "One or more of the fields are null");
		return;
	}
	emit SendLoginToServer();
}


void LoginPage::OnRegister() {
	if (ui->inputUsername->text().isEmpty() || ui->inputPsw->text().isEmpty() || ui->inputPswConf->text().isEmpty())
	{
		QMessageBox::warning(nullptr, "Title", "One or more of the fields are null");
		return;
	}

	if (ui->inputPsw->text() != ui->inputPswConf->text()) {
		QMessageBox::warning(nullptr, "Register error", "The two passwords are not the same");
		emit SendRegisterToServer();

	}
}