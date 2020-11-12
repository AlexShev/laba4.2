#pragma once
#include "Shape.h"

class Hexagon :public Shape
{
public:
	Hexagon()
	{
		_size = 6;
		_ptr = new Point[6];
		_ptr[0] = { -0.5, -sqrt(3) / 2 };
		_ptr[1] = { -1, 0 };
		_ptr[2] = { -0.5, sqrt(3) / 2 };
		_ptr[3] = { 0.5, sqrt(3) / 2 };
		_ptr[4] = { 1, 0 };
		_ptr[5] = { 0.5, - sqrt(3) / 2 };
	}

	Hexagon(const Point * ptr) :Shape(6, ptr) {}							// Конструктор с параметрами (массив)	
	
	Hexagon(const Hexagon& other) :Shape(other) {}							// Конструктор копирования

	Hexagon& operator=(const Hexagon& other)								// Оператор приваивания
	{
		if (this == &other)
		{
			return *this;
		}
		_Destroy();
		_size = 6;
		_ptr = new Point[_size];
		memcpy(_ptr, other._ptr, _size);
		return *this;
	}

	virtual string TypeOfShape() const override { return "Шестиугольник"; }	// тип
};