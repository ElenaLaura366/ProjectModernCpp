#pragma once

#include <QMainWindow>
#include "ui_UserInfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class UserInfoClass; };
QT_END_NAMESPACE

class UserInfo : public QMainWindow
{
	Q_OBJECT

public:
	UserInfo(QWidget *parent = nullptr);
	~UserInfo();

private:
	Ui::UserInfoClass *ui;
};
