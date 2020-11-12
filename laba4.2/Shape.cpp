#include "Shape.h"

Shape::Shape(int size, const Point* ptr) // ����������� � �����������, � ��������
{
	_size = size;
	_ptr = new Point[_size];
	for (int i = 0; i < _size; i++)
	{
		_ptr[i] = ptr[i];
	}
	IsExistence();
}

Shape::Shape(const Shape& other)
{
	_Destroy();
	_size = other._size;
	_ptr = new Point[_size];
	memcpy(_ptr, other._ptr, _size);
}

Shape& Shape::operator=(const Shape& other)
{
	if (this == &other) //�������������� ���������������
	{
		return *this;
	}
	_Destroy();
	_size = other._size;
	_ptr = new Point[_size];
	memcpy(_ptr, other._ptr, _size);
	return *this;
}

const Point& Shape::operator [](int index) const
{
	if (index >= 0 && index < _size)
		return _ptr[index];
	else throw std::logic_error("����� �� ������� �������");
}

int Shape::GenerateID()
{
	static int s_id = 0;
	return ++s_id;
}

void Shape::IsExistence() const
{
	if (_size < 3)
	{
		delete[] _ptr;
		throw std::logic_error("����������� ������, ������ ������ �������� ������� �� ��� �����!!");
	}

	// �������� �� ��������������� �����
	IsPointOnPoint();

	// �������� �� ���������� ����
	IsStraightAngle();

	// �������� �� �������������� ����� ������ �� ��������
	IsPointOnLine();

	// �������� �� �������������� ������, ��� ���������� ������ ������� 3
	if (_size > 3)
	{
		IsLinesCross();
	}
}

void Shape::IsPointOnPoint() const
{
	for (int i = 0; i < _size - 1; i++)
	{
		for (int j = i + 1; j < _size; j++)
		{
			if (_ptr[i] == _ptr[j])
			{
				delete[] _ptr;
				throw std::logic_error("��������������� �����!!");
			}
		}
	}
}

bool Shape::IsOnePoint(const Point& point) const
{
	for (int i = 0; i < _size; i++)
	{
		if (point == _ptr[i])
		{
			return true;
		}
	}
	return false;
}


void Shape::IsStraightAngle() const
{
	for (int i = 0; i < _size; i++)
	{
		if (abs(VectorsProduct(_ptr[(i + 1) % _size] - _ptr[i % _size], _ptr[(i + 2) % _size] - _ptr[(i + 1) % _size])) < 1e-9)
		{
			delete[] _ptr;
			throw std::logic_error("��� ����� ����� �� ����� ������!!");
		}
	}
}

void Shape::IsLinesCross() const
{
	for (int i = 0; i < _size; i++)
	{
		for (int j = i + 2; j < _size; j++)
		{
			if (LinesCross(_ptr[i % _size], _ptr[(i + 1) % _size], _ptr[j % _size], _ptr[(j + 1) % _size]))
			{
				delete[] _ptr;
				throw std::logic_error("����������� ������!!");
			}
		}
	}

}

void Shape::IsPointOnLine() const
{
	for (int i = 0; i < _size; i++)
	{
		for (int j = i + 1; j < _size + i - 1; j++)
		{
			if (abs((_ptr[j % _size]._x - _ptr[i % _size]._x) * (_ptr[(j + 1) % _size]._y - _ptr[i % _size]._y)
				- (_ptr[(j + 1) % _size]._x - _ptr[i % _size]._x) * (_ptr[j % _size]._y - _ptr[i % _size]._y)) < 1e-9)
			{
				delete[] _ptr;
				throw std::logic_error("���� �� ������ ����� �� ����� �� ������!!");
			}
		}
	}
}

Point Shape::Center() const	// ����� �������
{
	Point D;
	
	for (int i = 0; i < _size; i++)
	{
		D._x += _ptr[i]._x;
		D._y += _ptr[i]._y;
	}
	
	D._x /= _size;
	D._y /= _size;
	
	return D;
}

double Shape::Comparison(const Shape& shape) const
{
	double S1 = Squear();
	double S2 = shape.Squear();

	if (S1 > S2)
	{
		return S1 / S2;
	}
	else if (S1 < S2)
	{
		return -S2 / S1;
	}
	else
	{
		return 1;
	}
}

double Shape::Perimeter() const	// ��������
{
	double P = 0;

	for (int i = 0; i < _size - 1; i++)
	{
		P += _ptr[i % _size].Section(_ptr[(i+1) % _size]);
	}

	return P;
}

double Shape::Squear() const	// �������
{
	double S = 0;

	for (int i = 0; i < _size; i++)
	{
		S = S + abs(_ptr[i% _size]._x * _ptr[(i + 1) % _size]._y - _ptr[(i + 1) % _size]._x * _ptr[i % _size]._y);
	}

	return abs(S)/2.;
}

Shape& Shape::Shift(const Point& vector)		// �����������
{
	for (int i = 0; i < _size; i++)
	{
		_ptr[i] = _ptr[i] + vector;
	}
	return *this;
}

Shape& Shape::Rotation(double angle)
{
	const double PI = acos(-1);		// ����� ��
	const Point D = Center();
	double cs = cos(PI * angle / 180.);
	double sn = sin(PI * angle / 180.);
	Point temp;

	for (int i = 0; i < _size; i++)
	{
		temp = _ptr[i] - D;
		_ptr[i]._x = D._x + temp._x * cs - temp._y * sn;
		_ptr[i]._y = D._y + temp._y * cs + temp._x * sn;
	}
	
	return *this;
}

bool Shape::Intersection(const Shape& shape) const
{
	if (!Include(shape)) // ��������� ����� ������ �� ���� ������
	{
		int count = 0;
		for (int i = 0; i < shape._size; i++)
		{
			if (IncludePoint(shape._ptr[i])) return true;
		}
		for (int i = 0; i < _size; i++)
		{
			if (shape.IncludePoint(_ptr[i])) return true;
		}
		return false;
	}
	else return false;
}

bool Shape::IncludePoint(const Point& point) const
{
	bool b = false;
	
	for (int i = 0; i < _size - 1; i++)	//��� ���������� ����� ��� �
	{
		if (point._x == _ptr[i]._x && point._y == _ptr[i]._y)
			return true;	//���� ����� � �������

		if (point._x <= _ptr[i]._x && point._y <= _ptr[i]._y && point._y > _ptr[i + 1]._y 
			|| point._x <= _ptr[i]._x && point._y >= _ptr[i]._y && point._y < _ptr[i + 1]._y)
		{
			b = !b;	// ���� ��������� ����������� �������� ����� ��� - ���
		}
		if (_ptr[i]._y != _ptr[i + 1]._y)
		{
			if (((point._x <= _ptr[i]._x && point._x >= _ptr[i + 1]._x) || (point._x >= _ptr[i]._x && point._x <= _ptr[i + 1]._x))
				&& (point._x * (_ptr[i]._x - _ptr[i + 1]._x) / (_ptr[i]._y - _ptr[i + 1]._y) == point._y))
				return true;
		}	//���� ����� ����� �� �����

		if ((_ptr[i]._y == _ptr[i + 1]._y) && (point._y == _ptr[i]._y) && ((point._x <= _ptr[i]._x && point._x >= _ptr[i + 1]._x) || (point._x >= _ptr[i]._x && point._x <= _ptr[i + 1]._x)))
			return true;	//���� ����� ����� �� �����

		if ((_ptr[i]._y == _ptr[i + 1]._y) && (point._y == _ptr[i + 1]._y))
		{
			b = !b;	// ���� ����� ����������� ����, �� ��� ��� ����� ��� ���� ����������
		}
	}

	if (point._x <= _ptr[0]._x && point._y <= _ptr[0]._y && point._y >= _ptr[_size - 1]._y || point._x <= _ptr[0]._x && point._y >= _ptr[0]._y && point._y <= _ptr[_size - 1]._y)
	{
		b = !b;//����������� � ��������� ������
	}
	
	if ((_ptr[0]._y == _ptr[_size - 1]._y) && (_ptr[0]._y == point._y))
	{
		b = !b;//���� ����� ����������� ����, �� ��� ��� ����� ��� ���� ����������
	}
	
	if (point._x == _ptr[_size - 1]._x && point._y == _ptr[_size - 1]._y) 
		return true;//���� ����� � �������

	return b;
}

bool Shape::Include(const Shape& shape) const
{
	if (shape.Squear() > Squear())
	{
		return 0;
	}

	int count = 0;
	
	for (int i = 0; i < shape._size; i++)
	{
		if (IncludePoint(shape._ptr[i])) ++count;
	}
	
	return count % shape._size == 0;
}

istream& operator >> (istream& is, Shape& shape)
{
	for (int i = 0; i < shape._size; i++)
	{
		is >> shape._ptr[i];
	}	
	shape.IsExistence();
	return is;
}

ostream& operator << (ostream& os, const Shape& shape)
{
	char a = 'A';
	for (int i = 0; i < shape._size; i++)
	{
		os  << a++ << shape._ptr[i] << "    ";
	}
	return os;
}