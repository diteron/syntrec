#include "pch.h"
#include "main_window.h"

MainWindow::MainWindow(int width, int height, QWidget* parent) 
    : QMainWindow(parent), houseGrammar_()
{
    resize(width, height);
    centralWidget_ = new CentralWidget(this);
    setCentralWidget(centralWidget_);

    sideBar_ = new SideBar(centralWidget_);
    sideBar_->connect(sideBar_, &SideBar::recognitionButtonClicked, this, &MainWindow::recognition);
    sideBar_->connect(sideBar_, &SideBar::generateButtonClicked, this, &MainWindow::generateQLines);
    sideBar_->connect(sideBar_, &SideBar::clearButtonClicked, this, &MainWindow::clearCanvas);
    centralWidget_->addWidget(sideBar_, 1);

    Qt::ColorScheme systemColorScheme = qApp->styleHints()->colorScheme();
    QColor dataViewColor = (systemColorScheme == Qt::ColorScheme::Dark) ? QColor(220, 224, 227) : Qt::white;

    canvas_ = new DrawingCanvas(createPalette(dataViewColor), centralWidget_);
    centralWidget_->addWidget(canvas_, 8);
}

MainWindow::~MainWindow()
{}

QPalette MainWindow::createPalette(const QColor& backgroundColor)
{
    QPalette palette;
    QBrush brush(backgroundColor);
    brush.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Window, brush);
    palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
    return palette;
}

void MainWindow::drawGeneratedLines(std::vector<QLine>& lines)
{
    canvas_->drawLines(std::move(lines));
}

std::vector<Element> MainWindow::getElementsForRecognition() const
{
    const std::vector<QLine>& drawnLines = canvas_->getDrawnLines();
    std::vector<Element> recognitionElements{};
    for (const auto& drawnLine : drawnLines) {
        recognitionElements.push_back(houseGrammar_.getTerminalElement(Line(Point(drawnLine.x1(), drawnLine.y1()),
                                                                            Point(drawnLine.x2(), drawnLine.y2()))));
    }

    return recognitionElements;
}

void MainWindow::generateQLines()
{
    Element house = houseGrammar_.getHouse();
    house.scaleTransform(static_cast<double>(canvas_->width() - 100) / house.getLength(),
                         static_cast<double>(canvas_->height() - 50) / house.getHeight());
    house.shiftTransform(50, 50);

    std::vector<QLine> qLines;
    const std::vector<Line>& houseLines = house.getLines();
    for (const auto& line : houseLines) {
        Point startPoint = line.getStartPoint();
        Point endPoint = line.getEndPoint();
        qLines.push_back(QLine(startPoint.getX(), startPoint.getY(),
                               endPoint.getX(), endPoint.getY()));
    }

    canvas_->clear();
    drawGeneratedLines(qLines);
}

void MainWindow::recognition()
{
    std::vector<Element> elements = getElementsForRecognition();
    std::string resultMessage = houseGrammar_.isHouse(elements);
    QMessageBox::information(0, QApplication::applicationName(), resultMessage.c_str());
}

void MainWindow::clearCanvas()
{
    canvas_->clear();
}
