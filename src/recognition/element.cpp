#include "pch.h"
#include "element.h"

Element::Element(const Object& obj)
    : obj_(obj), lines_(), startPos_(), endPos_(),
      length_(0), height_(0)
{}

Element::Element(const Object& obj, Line line)
    : obj_(obj), lines_()
{
    lines_.push_back(line);
    startPos_ = Point(std::min(line.getStartPoint().getX(), line.getEndPoint().getX()),
                      std::min(line.getStartPoint().getY(), line.getEndPoint().getY()));
    endPos_ = Point(std::max(line.getStartPoint().getX(), line.getEndPoint().getX()),
                    std::max(line.getStartPoint().getY(), line.getEndPoint().getY()));
    length_ = std::abs(endPos_.getX() - startPos_.getX());
    height_ = std::abs(endPos_.getY() - startPos_.getY());
}

Element::Element(const Object& obj, std::vector<Line>&& lines,
                 Point startPos, Point endPos)
    : obj_(obj), lines_(std::move(lines)),
      startPos_(startPos), endPos_(endPos)
{
    length_ = std::abs(endPos_.getX() - startPos_.getX());
    height_ = std::abs(endPos_.getY() - startPos_.getY());
}

const Object& Element::getNonterminal() const
{
    return obj_;
}

Point Element::getStartPos() const
{
    return startPos_;
}

Point Element::getEndPos() const
{
    return endPos_;
}

const std::vector<Line>& Element::getLines() const
{
    return lines_;
}

double Element::getLength() const
{
    return length_;
}

double Element::getHeight() const
{
    return height_;
}

void Element::setStartPos(Point pos)
{
    startPos_ = pos;
}

void Element::setEndPos(Point pos)
{
    endPos_ = pos;
}

void Element::scaleTransform(double xScale, double yScale)
{
    Point scaleVector(xScale, yScale);
    Point deltaVector = endPos_ - startPos_;
    deltaVector *= scaleVector;
    endPos_ = startPos_ + deltaVector;
    for (Line& line : lines_) {
        line.scaleTransform(xScale, yScale, startPos_);
    }
}

void Element::shiftTransform(int xDelta, int yDelta)
{
    Point shiftVector(xDelta, yDelta);
    startPos_ += shiftVector;
    endPos_ += shiftVector;
    for (Line& line : lines_) {
        line.shiftTransform(xDelta, yDelta);
    }
}
