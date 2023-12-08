#include "GamePage.h"
#include <QKeyEvent>

GamePage::GamePage(QWidget *parent)
	: QWidget{ parent }
	, ui{ new Ui::GamePageClass() }
{
	ui->setupUi(this);
	m_drawingArea = ui->drawingArea;

	connect(ui->sendAnswer, &QPushButton::clicked, this, &GamePage::SendAnswer); 
	connect(ui->undoLastLine, &QPushButton::clicked, this, &GamePage::OnUndoBtnClicked);
}

GamePage::~GamePage(){
	delete ui;
}

void GamePage::KeyPressEvent(QKeyEvent* event) {
	if (event->key() == Qt::Key_Return) {
		SendAnswer();
	}

	if (event->key() == Qt::Key_Z && event->modifiers() & Qt::ControlModifier) {
		OnUndoBtnClicked();
	}
}

void GamePage::SendAnswer() {
	QString answer = ui->chatInput->text();
	if (answer.isEmpty())
		return;
	ui->chatInput->clear();
	UpdateChat("client", answer);
}

void GamePage::UpdateChat(const QString& username, const QString& answer) {
	QString text = username + ": " + answer;
	QListWidgetItem* answerItem = new QListWidgetItem(text);
	ui->answerList->addItem(answerItem);
	update();
}

void GamePage::OnUndoBtnClicked() {
	m_drawingArea->UndoLastLine();
}



