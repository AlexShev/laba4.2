#pragma once
#include "FactoryShape.h"

using std::cout;
using std::cin;
using std::endl;

class ConsoleForFactoryShape
{
public:
	void WhatICan()
	{
		cout << "���� � ���� �������� ������ � ��������������, ������-, ����- � ����������������\n";
	}

	Shape* ReadShape()
	{
		FactoryShape Factory;

		int size;
		Point* ptr = 0;
		
		WhatICan();
		cout << "������� ���������� ������: ";
		cin >> size;

		if (Factory.CanIDo(size))
		{
			string i;
			cout << "\n������ ���������� ��������� �� ���������?\n";
			cout << "������� 0 ��� �������������, ����� ����� ������ ���������� �������: ";
			cin >> i;

			if (i != "0")
			{
				ptr = new Point[size];

				for (int i = 0; i < size; i++)
				{
					cout << "������� ���������� ����� � " << i + 1 << endl;
					cin >> ptr[i];
					cout << endl;
				}
			}
		}
		
		try
		{
			Shape* shape = Factory.CreateShape(size, ptr);
			delete[] ptr;
			return shape;
		}
		catch (std::exception & err)
		{
			delete[] ptr;
			std::cerr << endl << err.what();
			throw std::logic_error("������ �� �������� �� ���������!!!");
		}
		
	}
};