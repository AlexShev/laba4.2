#pragma once
#include "Triangle.h"

class EquilateralTriangle : public Triangle
{
public:
	EquilateralTriangle()
	{
		_size = 3;
		_ptr[0] = { -1. / sqrt(3),0 };
		_ptr[1] = { 1. / sqrt(3),0 };
		_ptr[2] = { 0,1 };
	}

	EquilateralTriangle& operator=(const EquilateralTriangle& other)
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

	EquilateralTriangle(const Point* ptr) :Triangle(ptr) {}					// ����������� � ����������� (������)	

	void IsEquilateralTriangle() const
	{
		double epcilon(1e-9);
		double a = _ptr[0].Section(_ptr[1]);
		double b = _ptr[1].Section(_ptr[2]);
		double c = _ptr[2].Section(_ptr[0]);
		if (abs(a - b) > epcilon && abs(b - c) > epcilon && abs(c - a) > epcilon)
			throw std::logic_error("\n\n��� �� ���������� �����������!!");
	}

	void IsExistence() const override
	{
		// �������� �� ��������������� �����
		IsPointOnPoint();

		// �������� �� ���������� ����
		IsStraightAngle();

		// ������ �������
		IsEquilateralTriangle();
	}

	string TypeOfShape() const override { return "���������� �����������"; }		// ���
};