#pragma once
#include "Shape.h"

class Pentagon :public Shape
{
public:
	Pentagon()
	{
		_size = 5;
		_ptr = new Point[5];
		double Pi = acos(-1);
		_ptr[0] = { -sin(Pi / 5), -cos(Pi / 5) };
		_ptr[1] = { -2* sin(Pi / 5)*cos(2 * Pi / 10), 1 - 2 * sin(Pi / 5)*sin(2 * Pi / 10) };
		_ptr[2] = { 0,1 };
		_ptr[3] = { 2 * sin(Pi / 5) * cos(2 * Pi / 10), 1 - 2 * sin(Pi / 5) * sin(2 * Pi / 10) };
		_ptr[4] = { sin(Pi / 5), -cos(Pi / 5) };
	}

	Pentagon(const Point* ptr) :Shape(5, ptr) {}								// Конструктор с параметрами (массив)	
	
	Pentagon(const Pentagon& other) :Shape(other) {}						// Конструктор копирования
	
	Pentagon& operator=(const Pentagon& other)								// Оператор приваивания
	{
		if (this == &other) //предотвращение самокопирования
		{
			return *this;
		}
		_Destroy();
		_size = 5;
		_ptr = new Point[_size];
		memcpy(_ptr, other._ptr, _size);
		return *this;
	}
	
	virtual string TypeOfShape() const override { return "Пятиугольник"; }	// тип
};