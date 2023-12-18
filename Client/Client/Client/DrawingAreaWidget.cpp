#include "DrawingAreaWidget.h"

DrawingAreaWidget::DrawingAreaWidget(QWidget* parent) : QWidget{ parent }, m_isMousePressed{ false } {}

void DrawingAreaWidget::UndoLastLine()
{
	if (!m_drawing.isEmpty()) {
		m_drawing.pop_back();
		m_line.clear();
		update();
	}
}

void DrawingAreaWidget::ResetDrawing()
{
	m_drawing.clear();
	m_line.clear();
	update();
}

void DrawingAreaWidget::mousePressEvent(QMouseEvent* event) {
	if (event->button() == Qt::LeftButton) {
		m_line.clear();
		m_line << event->pos();
		m_isMousePressed = true;
		update();
	}
}

void DrawingAreaWidget::mouseMoveEvent(QMouseEvent* event) {
	if ((event->buttons() & Qt::LeftButton) && m_isMousePressed) {
		m_line << event->pos();
		update();
	}
}

void DrawingAreaWidget::mouseReleaseEvent(QMouseEvent* event) {
	if (event->button() == Qt::LeftButton && m_isMousePressed) {
		m_isMousePressed = false;
		m_drawing.push_back(m_line);
	}
}

void DrawingAreaWidget::paintEvent(QPaintEvent* event) {
	//Q_UNUSED(event);

	// routing to get drawing?

	QPainter painter(this);
	painter.fillRect(rect(), QColor(255, 255, 255));

	if (!m_drawing.isEmpty()) {
		for (const auto& line : m_drawing)
		{
			painter.setPen(Qt::black);
			painter.drawPolyline(line.data(), line.size());
		}
	}

	if (!m_line.isEmpty())
	{
		painter.setPen(Qt::black);
		painter.drawPolyline(m_line.data(), m_line.size());
	}
}