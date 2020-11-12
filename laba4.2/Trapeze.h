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

	Trapeze(const Point* ptr) :Quadrangle(ptr) {}				// ����������� � ����������� (������)	
	
	Trapeze(const Trapeze& other) :Quadrangle(other) {}						// ����������� �����������

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
			throw std::logic_error("\n\n��� �� ��������!!");
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

		IsTrapeze();
	}

	string TypeOfShape() const override { return "��������";}
};