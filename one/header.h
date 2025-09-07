#pragma once
#pragma once
#include <iostream>
using namespace std;

class Point {
private:
    double x, y;

public:
    Point();
    Point(double x, double y);
    Point(const Point& other);

    double getX() const;
    double getY() const;
    double distanceToOrigin() const;

    Point operator--();
    Point operator-();

    operator int() const;
    explicit operator double() const;

    Point operator-(int value);
    double operator-(const Point& p);

    friend ostream& operator<<(ostream& os, const Point& p);
};

Point getPointFromUserChoice();
void task1();
void task2();
int inputIntRange(const string& prompt, int min, int max);
double inputDouble(const string& prompt);
