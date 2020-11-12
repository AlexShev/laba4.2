#pragma once
#include "Shape.h"

class Triangle :public Shape
{
public:
	Triangle();
	Triangle(const Point* ptr):Shape(3, ptr) {}					// Конструктор с параметрами (массив)	
	Triangle(const Triangle& other):Shape(other) {}				// Конструктор копирования
	Triangle& operator=(const Triangle& other);					// Оператор приваивания

	virtual string TypeOfShape() const override { return "Обычный Треугольник"; }	// тип
	double Perimeter() const override;												// периметр
	double Squear()	const override;													// площадь
	void IsExistence() const override;
};