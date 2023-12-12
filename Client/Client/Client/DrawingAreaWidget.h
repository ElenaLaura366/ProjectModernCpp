#pragma once

#include <QPainter>
#include <QMouseEvent>
#include <QWidget>

using DrawingConfig = QVector<QVector<QPoint>>;

class DrawingAreaWidget : public QWidget {
	Q_OBJECT

public:
	DrawingAreaWidget(QWidget* parent = nullptr);
	void UndoLastLine();
	void ResetDrawing();

private:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void paintEvent(QPaintEvent* event) override;

private:
	DrawingConfig m_drawing;
	QVector<QPoint> m_line;
	bool m_isMousePressed;
};

