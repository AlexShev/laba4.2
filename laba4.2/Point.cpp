#include "Point.h"

double Point::Section(const Point& B = 0) const // растояние между точкам
{
	return sqrt((_x - B._x) * (_x - B._x) + (_y - B._y) * (_y - B._y));
}

int Point::Quarter() const
{
	if (_x == 0 && _y == 0)
		return 0;	// иначе никак
	if (_x > 0 && _y >= 0)
		return 1;
	if (_x <= 0 && _y > 0)
		return 2;
	if (_x <= 0 && _y < 0)
		return 3;
	return 4;
}

double VectorsProduct(const Point & A, const Point & B)
{
	return A._x* B._y - A._y * B._x;
}

bool LinesCross(const Point & A, const Point & B, const Point & C, const Point & D)
{
	Point A1, B1, C1, D1, A2, B2;
	A1 = D - C;
	B1 = A - C;

	double v1 = VectorsProduct(A1, A - C);
	double v2 = VectorsProduct(A1, B - C);
	double v3 = VectorsProduct(C1, C - A);
	double v4 = VectorsProduct(C1, D - A);

	if ((v1 * v2 < 0) && (v3 * v4 < 0))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

const Point operator+(const Point & left, const Point & right)
{
	return Point(left._x + right._x, left._y + right._y);
}

const Point operator-(const Point & left, const Point & right)
{
	return Point(left._x - right._x, left._y - right._y);
}

bool Point::operator==(const Point & right) const
{
	return (_x == right._x && _y == right._y);
}

bool Point::operator!=(const Point & right) const
{
	return !(*this == right);
}

/*
сравниваются положение точек по четвертям плоскости (1<2<3<4)
если равны, сравнивается углы с осью OX (с помощью знака векторного произведения и понятия правой тройки)
если равны, растояние до точки О
*/

bool Point::operator<(const Point & B) const
{
	int a = this->Quarter(), b = B.Quarter();
	if (a == b)
	{
		double right3 = VectorsProduct(*this, B);
		if (abs(right3)>1e-9) // сравнение с 0, учитывая погрешность
			return right3 > 0;
		else
			return this->Section() < B.Section();
	}
	else return a < b;
}

bool Point::operator>(const Point & B) const
{
	return !(*this < B || *this == B);
}

istream& operator >> (istream & is, Point & B)
{
	is >> B._x >> B._y;
	return is;
}

ostream& operator << (ostream & os, const Point & A)
{
	os << "(" << A._x << ";" << A._y << ")";
	return os;
}
