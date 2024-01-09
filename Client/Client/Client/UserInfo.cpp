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

		const auto& [gameId, playerId, points] = game;

		QTableWidgetItem* gameIdItem = new QTableWidgetItem(QString::number(gameId));
		QTableWidgetItem* playerIdItem = new QTableWidgetItem(QString::number(playerId));
		QTableWidgetItem* pointsItem = new QTableWidgetItem(QString::number(points));

		ui->tableWidget->setItem(rowIndex, 0, gameIdItem);
		ui->tableWidget->setItem(rowIndex, 1, playerIdItem);
		ui->tableWidget->setItem(rowIndex, 2, pointsItem);
		rowIndex++;
	}
}
