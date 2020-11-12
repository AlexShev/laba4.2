#pragma once
#include "Shape.h"

class Triangle :public Shape
{
public:
	Triangle();
	Triangle(const Point* ptr):Shape(3, ptr) {}					// ����������� � ����������� (������)	
	Triangle(const Triangle& other):Shape(other) {}				// ����������� �����������
	Triangle& operator=(const Triangle& other);					// �������� �����������

	virtual string TypeOfShape() const override { return "������� �����������"; }	// ���
	double Perimeter() const override;												// ��������
	double Squear()	const override;													// �������
	void IsExistence() const override;
};