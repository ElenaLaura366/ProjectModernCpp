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
	m_drawingArea = ui->drawingArea;

	ui->labelWord->setStyleSheet("font-size: 40px;");


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
	if (m_refreshCount % kRefreshRate == 0)
	{
		auto answers = m_rt->GetAnswers();

		if (answers.size() != 0 && answers.size() > m_answers.size())
		{
			m_answers.clear();
			m_answers = answers;
		}
		UpdateChat();

		m_drawingArea->SetIsPlayerDrawing(m_rt->IsDrawingPlayer());

		QString seconds = m_rt->GetTime();
		ui->lableSeconds->setText(seconds);


		QString round = m_rt->GetRound();
		ui->labelRound->setText(round);

		if (round == kGameOverState && !m_leaderBoardShow)
		{
			ShowLeaderBoard();
		}

		UpdateLeaderBoard();

		QString word = m_rt->GetWord();

		if (m_rt->GetIsDrawing()) {
			m_rt->SendDrawing(m_drawingArea->GetDrawing());
			ui->labelWord->setText(word);
		}
		else
		{
			m_drawingArea->SetDrawing(m_rt->GetDrawing());
			QString hiddenWord;
			for (size_t i = 0; i < word.size(); i++)
				hiddenWord += "_ ";

			ui->labelWord->setText(hiddenWord);
		}
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

void GamePage::UpdateChat() {

	ui->answerList->clear();
	for (const auto& text : m_answers)
	{
		QListWidgetItem* answerItem = new QListWidgetItem(text);
		answerItem->setFlags(answerItem->flags() & ~Qt::ItemIsSelectable);
		ui->answerList->addItem(answerItem);
	}
	ui->answerList->scrollToBottom();
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
	std::vector<std::pair<QString, int16_t>> playersAndScores = m_rt->GetLeaderBoard();

	m_leaderBoard = new LeaderBoardWidget(this, playersAndScores);
	m_leaderBoard->show();
}


