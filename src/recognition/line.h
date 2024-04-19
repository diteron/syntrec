#pragma once

#include "point.h"

class Line {
public:
    Line();
    Line(Point start, Point end);
    ~Line();

    Point getStartPoint() const;
    Point getEndPoint() const;

    void scaleTransform(double xScale, double yScale, Point scalingCenter);
    void shiftTransform(double xDelta, double yDelta);

    friend bool operator==(const Line& left, const Line& right);
    friend bool operator!=(const Line& left, const Line& right);

private:
    Point startPoint_;
    Point endPoint_;
};
