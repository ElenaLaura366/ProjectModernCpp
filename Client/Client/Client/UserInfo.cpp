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

void UserInfo::DisplayHistory(std::vector<GameHistory> gameHistory)
{

	ui->tableWidget->setRowCount(gameHistory.size());

	int rowIndex = 0;
	for (const auto& game : gameHistory) {

		const auto& [points, date] = game;

		QTableWidgetItem* gameIdItem = new QTableWidgetItem(QString::fromUtf8(points.c_str()));
		QTableWidgetItem* playerIdItem = new QTableWidgetItem(QString::fromUtf8(date.c_str()));

		ui->tableWidget->setItem(rowIndex, 0, gameIdItem);
		ui->tableWidget->setItem(rowIndex, 1, playerIdItem);
		rowIndex++;
	}
}
