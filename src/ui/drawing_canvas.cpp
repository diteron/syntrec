#include "pch.h"
#include "drawing_canvas.h"

DrawingCanvas::DrawingCanvas(const QPalette& backgroundColor, QWidget* parent)
    : QWidget(parent), lines_(),
      startPoint_(), endPoint_()
{
    setAutoFillBackground(true);
    setPalette(backgroundColor);
}

DrawingCanvas::~DrawingCanvas()
{}

int DrawingCanvas::getWidth() const
{
    return width();
}

int DrawingCanvas::getHeight() const
{
    return height();
}

const std::vector<QLine>& DrawingCanvas::getDrawnLines() const
{
    return lines_;
}

void DrawingCanvas::drawLines(std::vector<QLine>&& lines)
{
    lines_ = std::move(lines);
    update();
}

void DrawingCanvas::clear()
{
    lines_.clear();
    update();
}

void DrawingCanvas::mousePressEvent(QMouseEvent* event)
{
    if (!isLineDrawing_) {
        startPoint_ = event->pos();
        isLineDrawing_ = true;
    }
}

void DrawingCanvas::mouseReleaseEvent(QMouseEvent* event)
{
    if (isLineDrawing_) {
        endPoint_ = event->pos();
        isLineDrawing_ = false;
        update();
        lines_.push_back(QLine(startPoint_, endPoint_));
    }
}

void DrawingCanvas::mouseMoveEvent(QMouseEvent* event)
{
    if (isLineDrawing_) {
        endPoint_ = event->pos();
        update();
    }
}

void DrawingCanvas::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QPen pen = QPen(QBrush(Qt::black), 2, Qt::SolidLine);
    painter.setPen(pen);

    painter.begin(this);
    if (isLineDrawing_) {
        painter.drawLine(startPoint_, endPoint_);
    }
    drawLines(painter);
    painter.end();
}

void DrawingCanvas::drawLines(QPainter& painter)
{
    for (const QLine& line : lines_) {
        painter.drawLine(line);
    }
}
