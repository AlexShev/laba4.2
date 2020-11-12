#pragma once
#include "Triangle.h"

class RightIsoscelesTriangle : public Triangle
{
public:
	RightIsoscelesTriangle()
	{
		_size = 3;
		_ptr[0] = { 0,0 };
		_ptr[1] = { 2,0 };
		_ptr[2] = { 0,1 };
	}

	RightIsoscelesTriangle& operator=(const RightIsoscelesTriangle& other)
	{
		if (this == &other) //�������������� ���������������
		{
			return *this;
		}
		_Destroy();
		_size = 3;
		_ptr = new Point[_size];
		memcpy(_ptr, other._ptr, _size);
		return *this;
	}

	RightIsoscelesTriangle(const Point* ptr) :Triangle(ptr) {} 					// ����������� � ����������� (������)	
	
	void IsRightIsoscelesTriangle() const
	{
		double epcilon(1e-9);
		double a = _ptr[0].Section(_ptr[1]);
		double b = _ptr[1].Section(_ptr[2]);
		double c = _ptr[2].Section(_ptr[0]);
		bool a2 = abs(a * a + b * b - c * c) < epcilon && abs(b - a) < epcilon;	// c ����������, b=a
		bool b2 = abs(c * c + a * a - b * b) < epcilon && abs(c - a) < epcilon;	// b ����������, �=a
		bool c2 = abs(b * b + c * c - a * a) < epcilon && abs(b - c) < epcilon;	// a ����������, b=c
		if (!(a2 || b2 || c2))
			throw std::logic_error("\n\n��� �� ������������� �����������!!");
	}

	void IsExistence() const override
	{
		// �������� �� ��������������� �����
		IsPointOnPoint();

		// �������� �� ���������� ����
		IsStraightAngle();

		// ������ �������
		IsRightIsoscelesTriangle();
	}

	string TypeOfShape() const override { return "������������-�������������� �����������"; }		// ���
};