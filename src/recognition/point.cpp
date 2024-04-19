#include "pch.h"
#include "point.h"

Point::Point()
    : x_(0), y_(0)
{}

Point::Point(double x, double y)
    : x_(x), y_(y)
{}

Point::~Point()
{}

double Point::getX() const
{
    return x_;
}

double Point::getY() const
{
    return y_;
}

void Point::setX(double x)
{
    x_ = x;
}

void Point::setY(double y)
{
    y_ = y;
}

Point& Point::operator+=(const Point& shiftVector)
{
    x_ += shiftVector.x_;
    y_ += shiftVector.y_;
    return *this;
}

Point& Point::operator-=(const Point& shiftVector)
{
    x_ -= shiftVector.x_;
    y_ -= shiftVector.y_;
    return *this;
}

Point& Point::operator*=(const Point& scaleVector)
{
    x_ *= scaleVector.x_;
    y_ *= scaleVector.y_;
    return *this;
}

bool operator==(const Point& lpoint, const Point& rpoint)
{
    return (lpoint.x_ == rpoint.x_) && (lpoint.y_ == rpoint.y_);
}

bool operator!=(const Point& lpoint, const Point& rpoint)
{
    return !(lpoint == rpoint);
}

Point operator+(Point lpoint, const Point& shiftVector)
{
    lpoint += shiftVector;
    return lpoint;
}

Point operator-(Point lpoint, const Point& shiftVector)
{
    lpoint -= shiftVector;
    return lpoint;
}

Point operator*(Point lpoint, const Point& scaleVector)
{
    lpoint *= scaleVector;
    return lpoint;
}
