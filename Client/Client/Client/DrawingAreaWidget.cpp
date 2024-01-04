#include "DrawingAreaWidget.h"

DrawingAreaWidget::DrawingAreaWidget(QWidget* parent) : QWidget{ parent }, m_isMousePressed{ false } {}

void DrawingAreaWidget::UndoLastLine()
{
	if (!m_drawing.empty()) {
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

const DrawingConfig& DrawingAreaWidget::GetDrawing() const
{
	if (m_line.size() > 0) {
		DrawingConfig dr = m_drawing;
		dr.push_back(m_line);
		return dr;
	}
	return m_drawing;
}

void DrawingAreaWidget::SetDrawing(const DrawingConfig& drawing)
{
	m_drawing = drawing;
}

void DrawingAreaWidget::mousePressEvent(QMouseEvent* event) {
	if (event->button() == Qt::LeftButton) {
		m_line.clear();
		m_line.push_back(event->pos());
		m_isMousePressed = true;
		update();
	}
}

void DrawingAreaWidget::mouseMoveEvent(QMouseEvent* event) {
	if ((event->buttons() & Qt::LeftButton) && m_isMousePressed) {
		m_line.push_back(event->pos());
		update();
	}
}

void DrawingAreaWidget::mouseReleaseEvent(QMouseEvent* event) {
	if (event->button() == Qt::LeftButton && m_isMousePressed) {
		m_line.push_back(event->pos());
		m_drawing.push_back(m_line);
		m_isMousePressed = false;
	}
}

void DrawingAreaWidget::paintEvent(QPaintEvent* event) {
	Q_UNUSED(event);

	QPainter painter(this);
	painter.fillRect(rect(), QColor(255, 255, 255));

	if (!m_drawing.empty()) {
		for (const auto& line : m_drawing)
		{
			painter.setPen(Qt::black);
			painter.drawPolyline(line.data(), line.size());
		}
	}

	if (!m_line.empty())
	{
		painter.setPen(Qt::black);
		painter.drawPolyline(m_line.data(), m_line.size());
	}
}