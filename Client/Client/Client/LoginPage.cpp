#include "LoginPage.h"

LoginPage::LoginPage(QWidget *parent)
	: QWidget{ parent }
{
	this->setStyleSheet("background-color: red;");
	this->show();
}

LoginPage::~LoginPage()
{
}

void LoginPage::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.fillRect(rect(), Qt::red); // Umple widget-ul cu culoarea roșie

	QWidget::paintEvent(event); // Ap
}
