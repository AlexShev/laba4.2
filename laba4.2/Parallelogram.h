#pragma once
#include "Quadrangle.h"

class Parallelogram : public Quadrangle
{
public:
	Parallelogram()
	{
		_size = 4;
		_ptr[0] = { 0, 0 };
		_ptr[1] = { 0.5, 1 };
		_ptr[2] = { 1.5,  1 };
		_ptr[3] = { 1, 0 };
	}

	Parallelogram& operator=(const Parallelogram& other)
	{
		if (this == &other)
		{
			return *this;
		}
		_Destroy();
		_size = 4;
		_ptr = new Point[_size];
		memcpy(_ptr, other._ptr, _size);
		return *this;
	}

	Parallelogram(const Point* ptr) :Quadrangle(ptr) {}					// ����������� � ����������� (������)	

	Parallelogram(const Parallelogram& other) :Quadrangle(other) {}		// ����������� �����������

	void IsParallelogram() const
	{
		double epcilon(1e-9);
		double a1 = _ptr[0].Section(_ptr[1]);
		double b1 = _ptr[1].Section(_ptr[2]);
		double c1 = _ptr[2].Section(_ptr[3]);
		double d1 = _ptr[3].Section(_ptr[0]);
		if (!(abs(a1 - c1) < epcilon && abs(b1 - d1) < epcilon))
			throw std::logic_error("\n\n��� �� ��������������!!");
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

		IsParallelogram();
	}
	string TypeOfShape() const override {	return "��������������";}
};