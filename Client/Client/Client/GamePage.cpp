#include "GamePage.h"
#include <QKeyEvent>
#include <QTableWidgetItem>

GamePage::GamePage(QWidget* parent, Routing* rt)
	: QWidget{ parent }
	, ui{ new Ui::GamePageClass() }
	, m_refreshCount{ 0 }
	, m_rt{ rt }
	, m_leaderBoardShow{ false }
{
	ui->setupUi(this);
	ui->labelWord->setStyleSheet("font-size: 40px;");
	m_drawingArea = ui->drawingArea;

	connect(ui->sendAnswerBtn, &QPushButton::clicked, this, &GamePage::OnSendAnswerBtnClicked);
	connect(ui->undoLastLineBtn, &QPushButton::clicked, this, &GamePage::OnUndoBtnClicked);
	connect(ui->exitGameBtn, &QPushButton::clicked, this, &GamePage::OnExitGameBtnClicked);
	connect(ui->resetDrawingBtn, &QPushButton::clicked, this, &GamePage::OnResetDrawingBtnClicked);
}

GamePage::~GamePage() {
	delete ui;
}

Ui::GamePageClass* GamePage::GetUi()
{
	return ui;
}

void GamePage::paintEvent(QPaintEvent* e)
{
	if (m_refreshCount == 0)
		UpdateEndTurn();
	if (m_refreshCount % kRefreshRate == 0)
	{
		UpdateChat(std::move(m_rt->GetAnswers()));

		QString time = m_rt->GetTime();
		ui->lableSeconds->setText(time);

		if (kTimeOutValues.find(time) != kTimeOutValues.end())
			UpdateEndTurn();

		if (m_rt->GetIsDrawing())
			m_rt->SendDrawing(m_drawingArea->GetDrawing());
		else
			m_drawingArea->SetDrawing(m_rt->GetDrawing());
	}

	m_refreshCount++;
}

void GamePage::keyPressEvent(QKeyEvent* event) {
	if (event->key() == Qt::Key_Return)
		OnSendAnswerBtnClicked();

	if (event->key() == Qt::Key_Z && event->modifiers() & Qt::ControlModifier)
		OnUndoBtnClicked();
}

void GamePage::OnSendAnswerBtnClicked() {
	QString answer = ui->chatInput->text();
	if (answer.isEmpty())
		return;
	emit SendAnswerToServer();
}

void GamePage::UpdateLeaderBoard()
{
	std::vector<std::pair<QString, int16_t>> leaderBoard = m_rt->GetLeaderBoard();
	if (leaderBoard.size() == 0)
		return;

	ui->leaderBoard->clearContents();
	ui->leaderBoard->setRowCount(0);

	auto& tableWidget = ui->leaderBoard;
	int row;
	for (const auto& pair : leaderBoard) {
		int row = tableWidget->rowCount();
		tableWidget->setRowCount(row + 1);

		QTableWidgetItem* playerNameItem = new QTableWidgetItem(pair.first);
		QTableWidgetItem* scoreItem = new QTableWidgetItem(QString::number(pair.second));

		playerNameItem->setTextAlignment(Qt::AlignCenter);
		scoreItem->setTextAlignment(Qt::AlignCenter);

		tableWidget->setItem(row, 0, playerNameItem);
		tableWidget->setItem(row, 1, scoreItem);
	}
}

void GamePage::UpdateChat(const std::vector<QString>& answers) {

	if (answers.size() <= ui->answerList->count())
		return;
	size_t i = ui->answerList->count();
	for (; i < answers.size(); i++)
	{
		QListWidgetItem* answerItem = new QListWidgetItem(answers[i]);
		answerItem->setFlags(answerItem->flags() & ~Qt::ItemIsSelectable);
		ui->answerList->addItem(answerItem);
	}
	ui->answerList->scrollToBottom();
}

void GamePage::UpdateEndTurn()
{
	m_drawingArea->SetIsPlayerDrawing(m_rt->IsDrawingPlayer());

	QString round = m_rt->GetRound();
	ui->labelRound->setText(round);

	if (round == kGameOverState && !m_leaderBoardShow)
		ShowLeaderBoard();

	UpdateLeaderBoard();

	QString word = m_rt->GetWord();

	if (m_rt->GetIsDrawing()) {
		ui->labelWord->setText(word);
	}
	else {
		QString hiddenWord;
		for (size_t i = 0; i < word.size(); i++)
			hiddenWord += "_ ";

		ui->labelWord->setText(hiddenWord);
	}

}

void GamePage::OnUndoBtnClicked() {
	m_drawingArea->UndoLastLine();
}

void GamePage::OnResetDrawingBtnClicked() {
	m_drawingArea->ResetDrawing();
}

void GamePage::OnExitGameBtnClicked() {

	ui->answerList->clear();
	m_drawingArea->ResetDrawing();

	emit ExitGame();
}

void GamePage::ShowLeaderBoard() {
	m_leaderBoardShow = true;
	std::vector<std::pair<QString, int16_t>> playersAndScores = m_rt->GetLeaderBoard();

	m_leaderBoard = new LeaderBoardWidget(this, playersAndScores);
	m_leaderBoard->show();
}


