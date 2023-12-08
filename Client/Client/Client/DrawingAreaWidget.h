#pragma once
#include <QPainter>
#include <QMouseEvent>
#include <QWidget>

class DrawingAreaWidget : public QWidget {
    Q_OBJECT

public:
    DrawingAreaWidget(QWidget* parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:
    QVector<QPoint> points;
    bool isMousePressed;
};

