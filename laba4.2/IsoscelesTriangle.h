#pragma once
#include "Triangle.h"

class IsoscelesTriangle : public Triangle
{
public:
	IsoscelesTriangle()
	{
		_size = 3;
		_ptr[0] = { -1,0 };
		_ptr[1] = { 1,0 };
		_ptr[2] = { 0,2 };
	}

	IsoscelesTriangle(const IsoscelesTriangle& other) :Triangle(other) {}// Конструктор копирования

	IsoscelesTriangle(const Point* ptr) :Triangle(ptr) {}					 // Конструктор с параметрами (массив)	
	
	IsoscelesTriangle& operator=(const IsoscelesTriangle& other)
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

	void IsIsoscelesTriangle() const
	{
		double epcilon(1e-9);
		double a = _ptr[0].Section(_ptr[1]);
		double b = _ptr[1].Section(_ptr[2]);
		double c = _ptr[2].Section(_ptr[0]);
		bool a2 = abs(a - b) < epcilon && abs(b - c) > epcilon;	// a=b, b<>c
		bool b2	= abs(b - c) < epcilon && abs(b - a) > epcilon;	// b=c, b<>a
		bool c2 = abs(c - a) < epcilon && abs(b - c) > epcilon;	// c=a, b<>c
		if (!(a2||b2||c2))
		throw std::logic_error("\n\nЭто не равнобедренный треугольник!!");
	}

	void IsExistence() const override
	{
		// проверка на накладывающиеся точки
		IsPointOnPoint();

		// проверка на развёрнутый угол
		IsStraightAngle();

		// нужное условие
		IsIsoscelesTriangle();
	}

	string TypeOfShape() const override { return "Равнобедренный Треугольник"; }		// тип
};
