#pragma once

#include "central_widget.h"
#include "side_bar.h"
#include "drawing_canvas.h"
#include "recognition/house_grammar.h"

class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    MainWindow(int width, int height, QWidget* parent = nullptr);
    ~MainWindow();

private:
    QPalette createPalette(const QColor& backgroundColor);
    void drawGeneratedLines(std::vector<QLine>& lines);
    std::vector<Element> getElementsForRecognition() const;

    CentralWidget* centralWidget_ = nullptr;
    SideBar* sideBar_ = nullptr;
    DrawingCanvas* canvas_ = nullptr;

    HouseGrammar houseGrammar_;

public slots:
    void generateQLines();
    void recognition();
    void clearCanvas();
};

