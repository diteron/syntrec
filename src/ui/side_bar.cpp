#include "pch.h"
#include "side_bar.h"

SideBar::SideBar(QWidget* parent) : QWidget(parent)
{
    layout_ = new QVBoxLayout(this);

    generateButton_ = createPushButton(this, "Generate",
                                      buttonsMaxWidth_, buttonsMaxHeight_);
    recognitionButton_ = createPushButton(this, "Recognition",
                                          buttonsMaxWidth_, buttonsMaxHeight_);
    clearButton_ = createPushButton(this, "Clear",
                                          buttonsMaxWidth_, buttonsMaxHeight_);
    generateButton_->connect(generateButton_, &QPushButton::clicked, this, &SideBar::generateButtonClick);
    recognitionButton_->connect(recognitionButton_, &QPushButton::clicked, this, &SideBar::recognitionButtonClick);
    clearButton_->connect(clearButton_, &QPushButton::clicked, this, &SideBar::clearButtonClick);
    layout_->addWidget(generateButton_);
    layout_->addWidget(recognitionButton_);
    layout_->addWidget(clearButton_);

    spacer_ = new QSpacerItem(spacerWidth_, spacerHeight_, QSizePolicy::Minimum, QSizePolicy::Expanding);
    layout_->addItem(spacer_);
}

SideBar::~SideBar()
{}

QPushButton* SideBar::createPushButton(QWidget* parent, const char* buttonText,
                                       int maxWidth, int maxHeight) 
{
    QPushButton* pushButton = new QPushButton(buttonText, parent);
    pushButton->setMaximumSize(QSize(maxWidth, maxHeight));
    return pushButton;
}

void SideBar::recognitionButtonClick()
{
    emit recognitionButtonClicked();
}

void SideBar::generateButtonClick()
{
    emit generateButtonClicked();
}

void SideBar::clearButtonClick()
{
    emit clearButtonClicked();
}
