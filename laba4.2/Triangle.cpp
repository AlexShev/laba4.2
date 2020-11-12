#include "Triangle.h"

Triangle::Triangle()	// координаты "обычного" треугольника
{
	_size = 3;
	_ptr = new Point[3];
	_ptr[0] = { -1./sqrt(3),0 };
	_ptr[1] = { 1,0 };
	_ptr[2] = { 0,1 };
}

Triangle& Triangle::operator=(const Triangle& other)
{
	if (this == &other) //предотвращение самокопирования
	{
		return *this;
	}
	_Destroy();
	_size = 3;
	_ptr = new Point[_size];
	memcpy(_ptr, other._ptr, _size);
	return *this;
}

double Triangle::Perimeter() const
{
	return _ptr[0].Section(_ptr[1]) + _ptr[1].Section(_ptr[2]) + _ptr[2].Section(_ptr[0]);
}

double Triangle::Squear() const
{
	return abs((_ptr[1].X() - _ptr[0].X()) * (_ptr[2].Y() - _ptr[0].Y()) -
		(_ptr[2].X() - _ptr[0].X()) * (_ptr[1].Y() - _ptr[0].Y())) / 2.;
}

void Triangle::IsExistence() const
{
	IsPointOnPoint();	// проверка на накладывающиеся точки

	IsStraightAngle();	// проверка на развёрнутый угол
}