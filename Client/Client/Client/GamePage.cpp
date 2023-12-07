#include "GamePage.h"

GamePage::GamePage(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::GamePageClass())
{
	
	ui->setupUi(this);
}

GamePage::~GamePage()
{
	delete ui;
}
