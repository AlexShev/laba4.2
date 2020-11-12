#include "FactoryShape.h"

bool FactoryShape::CanIDo(const int size)
{
	if (size == 3 || size == 4 || size == 5 || size == 6) { return true; }
	else { return false; }
}

Shape* FactoryShape::CreateShape(int size, Point* ptr = 0)
{
	if (CanIDo(size))
	{
		switch (size)
		{
		case 3:
			if (ptr == 0)
			{
				return new Triangle();
			}
			else
			{
				return CreateTriangle(ptr);
			}
			break;
		case 4:
			if (ptr == 0)
			{
				return new Quadrangle();
			}
			else
			{
				return CreateQuadrangle(ptr);
			}
			break;
		case 5:
			if (ptr == 0)
			{
				return new Pentagon();
			}
			else
			{
				return new Pentagon(ptr);
			}
			break;
		case 6:
			if (ptr == 0)
			{
				return new Hexagon();
			}
			else
			{
				return new Hexagon(ptr);
			}
			break;
		}
	}
	else
	{
		if (size < 3) 
		{
			throw std::logic_error("Вырожденная фигура, фигура должна состоять минимум из трёх точек!!");
		}
		else
		{
			throw std::logic_error("В пробной версии некоторые фигуры могут быть недоступны, купите полную весию!!");
		}
	}
}

Triangle* FactoryShape::CreateTriangle(Point * ptr)
{
	double a = ptr[0].Section(ptr[1]);
	double b = ptr[1].Section(ptr[2]);
	double c = ptr[2].Section(ptr[0]);
	double epcilon(1e-9);
	bool a1 = abs(a * a + b * b - c * c) < epcilon;	// c гипатинуза
	bool b1 = abs(c * c + a * a - b * b) < epcilon;	// b гипатинуза
	bool c1 = abs(b * b + c * c - a * a) < epcilon;	// a гипатинуза
	bool a2 = abs(b - a) < epcilon;	// b=a
	bool b2 = abs(c - a) < epcilon;	// с=a
	bool c2 = abs(b - c) < epcilon;	// b=c

	if (a2 && b2)
	{
		return new EquilateralTriangle(ptr);
	}
	else if ((a1 && a2) || (b1 && b2) || (c1 && c2))
	{
		return new RightIsoscelesTriangle(ptr);
	}
	else if (a2 || b2 || c2)
	{
		return new IsoscelesTriangle(ptr);
	}

	else if (a1 || b1 || c1)
	{
		return new RightTriangle(ptr);
	}
	else
	{
		return new Triangle(ptr);
	}
}

Quadrangle* FactoryShape::CreateQuadrangle(Point * ptr)
{
	double epcilon(1e-1);
	double a = ptr[0].Section(ptr[1]);
	double b = ptr[1].Section(ptr[2]);
	double c = ptr[2].Section(ptr[3]);
	double d = ptr[3].Section(ptr[0]);
	bool a1 = abs(a - c) < epcilon;										// a=c
	bool b1 = abs(a - b) < epcilon;										// a=b
	bool c1 = abs(b - d) < epcilon;										// b=d
	double v1 = abs(VectorsProduct(ptr[0] - ptr[1], ptr[1] - ptr[2]));	// прямой угол (площадь)
	double v2 = VectorsProduct(ptr[1] - ptr[0], ptr[3] - ptr[2]);		// параллельность
	double v3 = VectorsProduct(ptr[2] - ptr[1], ptr[0] - ptr[3]);		// параллельность

	if (a1 && b1 && c1 && abs(v1 - a * b) < epcilon)
	{
		return new Quadrate(ptr);
	}
	else if (a1 && b1 && c1)
	{
		return new Rhombus(ptr);
	}
	else if (a1 && c1 && abs(v1 - a * b) < epcilon)
	{
		return new Rectangle(ptr);
	}
	else if (a1 && c1)
	{
		return new Parallelogram(ptr);
	}
	else if ((abs(v2) < epcilon && abs(v3) > epcilon || abs(v2) > epcilon && abs(v3) < epcilon))
	{
		return new Trapeze(ptr);
	}
	else
	{
		return new Quadrangle(ptr);
	}
}