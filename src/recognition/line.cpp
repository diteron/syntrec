#include "pch.h"

#include "line.h"

Line::Line()
    : startPoint_(), endPoint_()
{}

Line::Line(Point start, Point end)
    : startPoint_(start), endPoint_(end)
{}

Line::~Line()
{}

Point Line::getStartPoint() const
{
    return startPoint_;
}

Point Line::getEndPoint() const
{
    return endPoint_;
}

void Line::scaleTransform(double xScale, double yScale, Point scalingCenter)
{
    Point scaleVector(xScale, yScale);
    startPoint_ = scaleVector * (startPoint_ - scalingCenter) + scalingCenter;
    endPoint_ = scaleVector * (endPoint_ - scalingCenter) + scalingCenter;
}

void Line::shiftTransform(double xDelta, double yDelta)
{
    Point shiftVector(xDelta, yDelta);
    startPoint_ += shiftVector;
    endPoint_ += shiftVector;
}

bool operator==(const Line& left, const Line& right)
{
    return (left.startPoint_ == right.startPoint_) && (left.endPoint_ == right.endPoint_);
}

bool operator!=(const Line& left, const Line& right)
{
    return !(left == right);
}
