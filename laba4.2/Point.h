#pragma once
#include <iostream>
using std::ostream;
using std::istream;

class Point
{
	friend class Shape;
public:
	Point(double x = 0, double y = 0) : _x(x), _y(y) {}

	double Section(const Point& B) const;
	int Quarter() const;
	friend double VectorsProduct(const Point& A, const Point& B);
	friend bool LinesCross(const Point& A, const Point& B, const Point& C, const Point& D);
	friend const Point operator+(const Point& left, const Point& right);
	friend const Point operator-(const Point& left, const Point& right);
	bool operator==(const Point& right) const;
	bool operator!=(const Point& right) const;
	bool operator<(const Point& B) const;
	bool operator>(const Point& B) const;
	friend istream& operator >> (istream& is, Point& B);
	friend ostream& operator << (ostream& os, const Point& A);

	double X() const {return _x; }
	double Y() const {return _y; }
private:
	double _x, _y;
};