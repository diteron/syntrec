#pragma once

class CentralWidget : public QWidget {
public:
    CentralWidget(QWidget* parent = nullptr);
    ~CentralWidget();

    void addWidget(QWidget* widget, int preferredStretch);

private:
    QHBoxLayout* layout_ = nullptr;

};

