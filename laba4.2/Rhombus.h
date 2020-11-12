#pragma once
#include "Quadrangle.h"

class Rhombus : public Quadrangle
{
public:
	Rhombus()
	{
		_size = 4;
		_ptr[0] = { -2,  0 };
		_ptr[1] = {  0,  1 };
		_ptr[2] = {  2,  0 };
		_ptr[3] = {  0, -1 };
	}

	Rhombus& operator=(const Rhombus& other)
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
	
	Rhombus(const Point* ptr) :Quadrangle(ptr) {}					// ����������� � ����������� (������)	

	Rhombus(const Rhombus& other) :Quadrangle(other) {}						// ����������� �����������

	void IsRhombus() const
	{
		double epcilon(1e-9);
		double a1 = _ptr[0].Section(_ptr[1]);
		double b1 = _ptr[1].Section(_ptr[2]);
		double c1 = _ptr[2].Section(_ptr[3]);
		double d1 = _ptr[3].Section(_ptr[0]);
		if (!(abs(a1 - c1) < epcilon && abs(a1 - b1) < epcilon && abs(b1 - d1) < epcilon))
			throw std::logic_error("\n\n��� �� ����!!");
	}

	void IsExistence() const override// ���� � ����������
	{
		// �������� �� ��������������� �����
		IsPointOnPoint();

		// �������� �� ���������� ����
		IsStraightAngle();

		// �������� �� �������������� ����� ������ �� ��������
		IsPointOnLine();

		// �������� �� �������������� ������, ��� ���������� ������ ������� 3
		IsLinesCross();
	
		IsRhombus();
	}

	string TypeOfShape() const override { return "����"; }
};