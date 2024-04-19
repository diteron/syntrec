#include "pch.h"
#include "central_widget.h"

CentralWidget::CentralWidget(QWidget* parent) : QWidget(parent)
{
    layout_ = new QHBoxLayout(this);
    layout_->setContentsMargins(8, 8, 8, 8);
}

CentralWidget::~CentralWidget()
{}

void CentralWidget::addWidget(QWidget* widget, int preferredStretch)
{
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(preferredStretch);
    widget->setSizePolicy(sizePolicy);

    widget->setParent(this);
    layout_->addWidget(widget);
}
