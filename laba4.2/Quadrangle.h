#pragma once
#include "Shape.h"

class Quadrangle :public Shape
{
public:
	Quadrangle();
	Quadrangle(const Point* ptr) :Shape(4, ptr) {}								// Конструктор с параметрами (массив)	
	Quadrangle(const Quadrangle& other) :Shape(other) {}						// Конструктор копирования
	Quadrangle& operator=(const Quadrangle& other);								// Оператор приваивания

	virtual string TypeOfShape() const override { return "Четырёхугольник"; }	// тип
	double Perimeter() const override;											// периметр
};