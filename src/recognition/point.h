#pragma once

class Point {
public:
    Point();
    Point(double x, double y);
    ~Point();

    double getX() const;
    double getY() const;
    void setX(double x);
    void setY(double y);

    Point& operator+=(const Point& shiftVector);
    Point& operator-=(const Point& shiftVector);
    Point& operator*=(const Point& scaleVector);
    friend bool operator==(const Point& lpoint , const Point& rpoint);
    friend bool operator!=(const Point& lpoint, const Point& rpoint);
    friend Point operator+(Point lpoint, const Point& shiftVector);
    friend Point operator-(Point lpoint, const Point& shiftVector);
    friend Point operator*(Point lpoint, const Point& scaleVector);

private:
    double x_ = 0;
    double y_ = 0;
};
