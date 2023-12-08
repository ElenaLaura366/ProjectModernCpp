#include "DrawingAreaWidget.h"

DrawingAreaWidget::DrawingAreaWidget(QWidget* parent) : QWidget{ parent }, isMousePressed{ false } {}

void DrawingAreaWidget::mousePressEvent(QMouseEvent* event) {
	if (event->button() == Qt::LeftButton) {
		points.clear();
		points << event->pos();
		isMousePressed = true;
		update();  // Solicită o re-desenare
	}
}

void DrawingAreaWidget::mouseMoveEvent(QMouseEvent* event) {
	if ((event->buttons() & Qt::LeftButton) && isMousePressed) {
		points << event->pos();
		update();  // Solicită o re-desenare
	}
}

void DrawingAreaWidget::mouseReleaseEvent(QMouseEvent* event) {
	if (event->button() == Qt::LeftButton && isMousePressed) {
		isMousePressed = false;
	}
}

void DrawingAreaWidget::paintEvent(QPaintEvent* event) {
	Q_UNUSED(event);
	QPainter painter(this);
	painter.fillRect(rect(), QColor(255, 255, 255));

	if (!points.isEmpty()) {
		painter.setPen(Qt::black);
		painter.drawPolyline(points.data(), points.size());
	}
}