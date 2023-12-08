#pragma once
#include <QPainter>
#include <QMouseEvent>
#include <QWidget>

class DrawingAreaWidget : public QWidget {
    Q_OBJECT

public:
    DrawingAreaWidget(QWidget* parent = nullptr);
    void UndoLastLine();

private:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:
    QVector<QVector<QPoint>> m_drawing;
    QVector<QPoint> m_line;
    bool m_isMousePressed;
};

