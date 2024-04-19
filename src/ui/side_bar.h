#pragma once

class SideBar : public QWidget {

    Q_OBJECT

public:
    SideBar(QWidget* parent = nullptr);
    ~SideBar();

private:
    QPushButton* createPushButton(QWidget* parent, const char* buttonText,
                                  int maxWidth, int maxHeight);

    QVBoxLayout* layout_ = nullptr;
    QPushButton* generateButton_ = nullptr;
    QPushButton* recognitionButton_ = nullptr;
    QPushButton* clearButton_ = nullptr;
    QSpacerItem* spacer_ = nullptr;

    const int spacerWidth_ = 20;
    const int spacerHeight_ = 40;
    const int buttonsMaxHeight_ = 40;
    const int buttonsMaxWidth_ = 90;

private slots:
    void generateButtonClick();
    void recognitionButtonClick();
    void clearButtonClick();

signals:
    void generateButtonClicked();
    void recognitionButtonClicked();
    void clearButtonClicked();
};

