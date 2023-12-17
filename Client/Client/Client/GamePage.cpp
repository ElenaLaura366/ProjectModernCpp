#include "GamePage.h"
#include <QKeyEvent>

GamePage::GamePage(QWidget *parent, Routing* rt)
	: QWidget{ parent }
	, ui{ new Ui::GamePageClass() }
	, m_rt{ rt }
{
	ui->setupUi(this);
	m_drawingArea = ui->drawingArea;

	connect(ui->sendAnswerBtn, &QPushButton::clicked, this, &GamePage::OnSendAnswerBtnClicked); 
	connect(ui->undoLastLineBtn, &QPushButton::clicked, this, &GamePage::OnUndoBtnClicked);
	connect(ui->exitGameBtn, &QPushButton::clicked, this, &GamePage::OnExitGameBtnClicked);
	connect(ui->resetDrawingBtn, &QPushButton::clicked, this, &GamePage::OnResetDrawingBtnClicked);
}

GamePage::~GamePage(){
	delete ui;
}

Ui::GamePageClass* GamePage::GetUi()
{
	return ui;
}

void GamePage::paintEvent(QPaintEvent* e)
{
	m_rt->GetAnswers();
	//m_rt->GetDrawing();
}

void GamePage::keyPressEvent(QKeyEvent* event) {
	if (event->key() == Qt::Key_Return) {
		OnSendAnswerBtnClicked();
	}

	if (event->key() == Qt::Key_Z && event->modifiers() & Qt::ControlModifier) {
		OnUndoBtnClicked();
	}
}

void GamePage::OnSendAnswerBtnClicked() {
	QString answer = ui->chatInput->text();
	if (answer.isEmpty())
		return;
	UpdateChat("client", answer);
	emit SendAnswerToServer();
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

void GamePage::OnResetDrawingBtnClicked() {
	m_drawingArea->ResetDrawing();
}

void GamePage::OnExitGameBtnClicked(){

	ui->answerList->clear();
	m_drawingArea->ResetDrawing();

	emit ExitGame();
}


