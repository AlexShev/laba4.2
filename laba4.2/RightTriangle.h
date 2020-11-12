#pragma once
#include "Triangle.h"

class RightTriangle : public Triangle
{
public:
	RightTriangle()
	{
		_size = 3;
		_ptr[0] = { 0,0 };
		_ptr[1] = { 2,0 };
		_ptr[2] = { 0,1 };
	}

	RightTriangle& operator=(const RightTriangle& other)
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

	RightTriangle(const Point* ptr) :Triangle(ptr) {}					// Конструктор с параметрами (массив)	

	void IsRightTriangle() const
	{
		double epcilon(1e-9);
		double a = _ptr[0].Section(_ptr[1]);
		double b = _ptr[1].Section(_ptr[2]);
		double c = _ptr[2].Section(_ptr[0]);	
		bool a2 = abs(a * a + b * b - c * c) < epcilon;	// c гипатинуза
		bool b2 = abs(c * c + a * a - b * b) < epcilon;	// b гипатинуза
		bool c2 = abs(b * b + c * c - a * a) < epcilon;	// a гипатинуза
		if (!(a2 || b2 || c2))
		throw std::logic_error("\n\nЭто не прямоугольный треугольник!!");
	}

	void IsExistence() const override
	{
		// проверка на накладывающиеся точки
		IsPointOnPoint();

		// проверка на развёрнутый угол
		IsStraightAngle();

		// нужное условие
		IsRightTriangle();
	}

	string TypeOfShape() const override { return "Прямоугольный Треугольник"; }		// тип
};