#include "UserInfo.h"

UserInfo::UserInfo(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::UserInfoClass())
{
	ui->setupUi(this);
}

UserInfo::~UserInfo()
{
	delete ui;
}
