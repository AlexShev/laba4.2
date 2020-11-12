#pragma once
#include "Point.h"

using std::string;

class Shape 
{
public:
	Shape() = default;
	Shape(int size, const Point* ptr);		// Конструктор с параметрами (массив)	
	Shape(const Shape& other);				// Конструктор копирования
	Shape& operator=(const Shape& other);	// Оператор приваивания
	virtual ~Shape() { _Destroy(); }

	int GetId() const { return _myId; }
	int GetSize() const { return _size; }
	const Point& operator [](int index) const;
	
	virtual	void IsExistence() const;		// существование
	void IsPointOnPoint() const;
	bool IsOnePoint(const Point& point) const;
	void IsStraightAngle() const;
	void IsLinesCross() const;
	void IsPointOnLine() const;
	
	Point Center() const;								// центр тяжести												
	virtual double Perimeter() const;					// периметр		
	virtual double Squear()	const;						// площадь
	virtual string TypeOfShape() const = 0 ;			// тип фигуры
	Shape& Rotation(double angle);						// вращение
	Shape& Shift(const Point& vector);					// перемещение
	double Comparison(const Shape& shape) const;		// сравнение площади фигур
	bool Intersection(const Shape& shape) const;		// пересечение
	bool Include(const Shape& shape) const;				// вложение
	bool IncludePoint(const Point& point) const;		// вложение точки в фигуру

	friend istream& operator >> (istream& is, Shape& shape);
	friend ostream& operator << (ostream& os, const Shape& shape);
	
protected:
	Point* _ptr = 0;
	int _size = 0;
	void _Destroy() { if (_ptr) delete[] _ptr; }

private:
	int GenerateID();									// индивидуальный номер
	const int _myId = GenerateID();
};