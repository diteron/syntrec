#pragma once

#include "point.h"
#include "line.h"
#include "object.h"

class Element {
public:
    Element(const Object& obj);
    Element(const Object& obj, Line line);
    Element(const Object& obj, std::vector<Line>&& lines,
            Point startPos, Point endPos);

    const Object& getNonterminal() const;
    Point getStartPos() const;
    Point getEndPos() const;
    const std::vector<Line>& getLines() const;
    double getLength() const;
    double getHeight() const;

    void setStartPos(Point pos);
    void setEndPos(Point pos);

    void scaleTransform(double xScale, double yScale);
    void shiftTransform(int xDelta, int yDelta);

private:
    Object obj_;
    Point startPos_;
    Point endPos_;
    double length_;
    double height_;
    std::vector<Line> lines_;
};

