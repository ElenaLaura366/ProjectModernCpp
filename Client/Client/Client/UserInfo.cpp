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
	for (const auto& history : gameHistory) {
		 
		const auto& [points, date] = history;

		QTableWidgetItem* pointsCell = new QTableWidgetItem(QString::fromUtf8(points.c_str()));
		QTableWidgetItem* dateCell = new QTableWidgetItem(QString::fromUtf8(date.c_str()));

		ui->tableWidget->setItem(rowIndex, 0, pointsCell);
		ui->tableWidget->setItem(rowIndex, 1, dateCell);
		rowIndex++;
	}
}