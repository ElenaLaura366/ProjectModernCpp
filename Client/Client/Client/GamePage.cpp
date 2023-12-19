#include "GamePage.h"
#include <QKeyEvent>

GamePage::GamePage(QWidget *parent, Routing* rt)
	: QWidget{ parent }
	, ui{ new Ui::GamePageClass() }
	, m_refreshCount{0}
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
	if(m_refreshCount % kRefreshRate == 0)
	{
		auto answers = m_rt->GetAnswers();

		if (answers.size() != 0 && answers.size() > m_answers.size())
		{
			m_answers.clear();
			m_answers = answers;
		}
		UpdateChat();
	}

	m_refreshCount++;
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
	emit SendAnswerToServer();
}

void GamePage::UpdateChat() {

	ui->answerList->clear();
	for (const auto& text : m_answers)
	{
		QListWidgetItem* answerItem = new QListWidgetItem(text);
		answerItem->setFlags(answerItem->flags() & ~Qt::ItemIsSelectable);
		ui->answerList->addItem(answerItem);
	}
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


