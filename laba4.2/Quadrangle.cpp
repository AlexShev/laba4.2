#include "Quadrangle.h"

Quadrangle::Quadrangle()					// координаты "обычного" треугольника
{
	_size = 4;
	_ptr = new Point[4];
	_ptr[0] = { 0,0 };
	_ptr[1] = { 1,0 };
	_ptr[2] = { 2,2 };
	_ptr[3] = { 0,1 };
}

Quadrangle& Quadrangle::operator=(const Quadrangle& other)
{
	if (this == &other) //предотвращение самокопирования
	{
		return *this;
	}
	_Destroy();
	_size = 4;
	_ptr = new Point[_size];
	memcpy(_ptr, other._ptr, _size);
	return *this;
}

double Quadrangle::Perimeter() const
{
	return _ptr[0].Section(_ptr[1]) + _ptr[1].Section(_ptr[2]) + _ptr[2].Section(_ptr[3]) + _ptr[3].Section(_ptr[0]);
}

