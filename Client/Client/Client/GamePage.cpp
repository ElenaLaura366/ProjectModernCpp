#include "GamePage.h"
#include <QKeyEvent>
#include "DrawingAreaWidget.h"

GamePage::GamePage(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::GamePageClass())
{
	
	ui->setupUi(this);
	DrawingAreaWidget* Dr = ui->drawingArea;

	connect(ui->sendAnswer, &QPushButton::clicked, this, &GamePage::SendAnswer);
}

GamePage::~GamePage()
{
	delete ui;
}

void GamePage::keyPressEvent(QKeyEvent* event) 
{
	if (event->key() == Qt::Key_Return)
	{
		SendAnswer();
	}
}

void GamePage::mouseEvent(QMouseEvent* event)
{

}

void GamePage::SendAnswer()
{
	QString answer = ui->chatInput->text();
	if (answer.isEmpty())
		return;
	ui->chatInput->clear();
	UpdateChat("client", answer);
}

void GamePage::UpdateChat(const QString& username, const QString& answer)
{
	QString text = username + ": " + answer;
	QListWidgetItem* answerItem = new QListWidgetItem(text);
	ui->answerList->addItem(answerItem);
	update();
}



