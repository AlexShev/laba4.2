#pragma once
#include "Shape.h"

class Quadrangle :public Shape
{
public:
	Quadrangle();
	Quadrangle(const Point* ptr) :Shape(4, ptr) {}								// ����������� � ����������� (������)	
	Quadrangle(const Quadrangle& other) :Shape(other) {}						// ����������� �����������
	Quadrangle& operator=(const Quadrangle& other);								// �������� �����������

	virtual string TypeOfShape() const override { return "��������������"; }	// ���
	double Perimeter() const override;											// ��������
};