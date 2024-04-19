#pragma once

#include "recognition/line.h"

class DrawingCanvas : public QWidget {
public:
    DrawingCanvas(const QPalette& backgroundColor, QWidget* parent = nullptr);
    ~DrawingCanvas();

    int getWidth() const;
    int getHeight() const;

    const std::vector<QLine>& getDrawnLines() const;
    void drawLines(std::vector<QLine>&& lines);

    void clear();

private:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    void drawLines(QPainter& painter);

    bool isLineDrawing_ = false;
    QPoint startPoint_;
    QPoint endPoint_;

    std::vector<QLine> lines_;
};
