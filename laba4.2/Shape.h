#pragma once
#include "Point.h"

using std::string;

class Shape 
{
public:
	Shape() = default;
	Shape(int size, const Point* ptr);		// ����������� � ����������� (������)	
	Shape(const Shape& other);				// ����������� �����������
	Shape& operator=(const Shape& other);	// �������� �����������
	virtual ~Shape() { _Destroy(); }

	int GetId() const { return _myId; }
	int GetSize() const { return _size; }
	const Point& operator [](int index) const;
	
	virtual	void IsExistence() const;		// �������������
	void IsPointOnPoint() const;
	bool IsOnePoint(const Point& point) const;
	void IsStraightAngle() const;
	void IsLinesCross() const;
	void IsPointOnLine() const;
	
	Point Center() const;								// ����� �������												
	virtual double Perimeter() const;					// ��������		
	virtual double Squear()	const;						// �������
	virtual string TypeOfShape() const = 0 ;			// ��� ������
	Shape& Rotation(double angle);						// ��������
	Shape& Shift(const Point& vector);					// �����������
	double Comparison(const Shape& shape) const;		// ��������� ������� �����
	bool Intersection(const Shape& shape) const;		// �����������
	bool Include(const Shape& shape) const;				// ��������
	bool IncludePoint(const Point& point) const;		// �������� ����� � ������

	friend istream& operator >> (istream& is, Shape& shape);
	friend ostream& operator << (ostream& os, const Shape& shape);
	
protected:
	Point* _ptr = 0;
	int _size = 0;
	void _Destroy() { if (_ptr) delete[] _ptr; }

private:
	int GenerateID();									// �������������� �����
	const int _myId = GenerateID();
};