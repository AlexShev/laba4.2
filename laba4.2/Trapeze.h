#pragma once
#include "Quadrangle.h"

class Trapeze : public Quadrangle
{
public:
	Trapeze()
	{
		_size = 4;
		_ptr[0] = { 0, 0 };
		_ptr[1] = { 0, 1 };
		_ptr[2] = { 1, 1 };
		_ptr[3] = { 1.5, 0 };
	}

	Trapeze& operator=(const Trapeze& other)
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

	Trapeze(const Point* ptr) :Quadrangle(ptr) {}				// Конструктор с параметрами (массив)	
	
	Trapeze(const Trapeze& other) :Quadrangle(other) {}						// Конструктор копирования

	void IsTrapeze() const
	{
		double epcilon(1e-9);
		Point AB = _ptr[1] - _ptr[0];
		Point BC = _ptr[2] - _ptr[1];
		Point CD = _ptr[3] - _ptr[2];
		Point DA = _ptr[0] - _ptr[3];
		double a = VectorsProduct(AB, CD);
		double b = VectorsProduct(BC, DA);
		if (!(abs(a) < epcilon && abs(b) > epcilon|| abs(a) > epcilon && abs(b) < epcilon))
			throw std::logic_error("\n\nЭто не трапеция!!");
	}

	void IsExistence() const override// пока в разработке
	{
		// проверка на накладывающиеся точки
		IsPointOnPoint();

		// проверка на развёрнутый угол
		IsStraightAngle();

		// проверка на принадлежность точки любому из отрезков
		IsPointOnLine();

		// проверка на пересекаюхиеся прямые, при количестве вершин больших 3
		IsLinesCross();

		IsTrapeze();
	}

	string TypeOfShape() const override { return "Трапеция";}
};