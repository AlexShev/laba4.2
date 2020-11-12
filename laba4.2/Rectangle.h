#pragma once
#include "Quadrangle.h"

class Rectangle : public Quadrangle
{
public:
	Rectangle()
	{
		_size = 4;
		_ptr[0] = { -1, -0.5 };
		_ptr[1] = { -1,  0.5 };
		_ptr[2] = {  1,  0.5 };
		_ptr[3] = {  1, -0.5 };
	}

	Rectangle& operator=(const Rectangle& other)
	{
		if (this == &other) //�������������� ���������������
		{
			return *this;
		}
		_Destroy();
		_size = 4;
		_ptr = new Point[_size];
		memcpy(_ptr, other._ptr, _size);
		return *this;
	}

	Rectangle(const Point* ptr) :Quadrangle(ptr) {}					// ����������� � ����������� (������)	

	Rectangle(const Rectangle& other) :Quadrangle(other) {}						// ����������� �����������

	void IsRectangle() const
	{
		double epcilon(1e-9);
		double c = abs(VectorsProduct(_ptr[1] - _ptr[0], _ptr[2] - _ptr[1]));
		double a1 = _ptr[0].Section(_ptr[1]);
		double b1 = _ptr[1].Section(_ptr[2]);
		double c1 = _ptr[2].Section(_ptr[3]);
		double d1 = _ptr[3].Section(_ptr[0]);
		if (!(abs(a1-c1) < epcilon && abs(b1-d1) < epcilon && abs(c-a1*b1) < epcilon))
			throw std::logic_error("\n\n��� �� �������������!!");
	}

	void IsExistence() const override
	{
		// �������� �� ��������������� �����
		IsPointOnPoint();

		// �������� �� ���������� ����
		IsStraightAngle();

		// �������� �� �������������� ����� ������ �� ��������
		IsPointOnLine();

		// �������� �� �������������� ������, ��� ���������� ������ ������� 3
		IsLinesCross();

		IsRectangle();
	}

	string TypeOfShape() const override { return "�������������"; }
};