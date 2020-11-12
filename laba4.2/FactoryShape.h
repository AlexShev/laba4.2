#pragma once
#include "Shape.h"
#include "Triangle.h"
#include "RightTriangle.h"
#include "IsoscelesTriangle.h"
#include "EquilateralTriangle.h"
#include "RightIsoscelesTriangle.h"
#include "Quadrangle.h"
#include "Rectangle.h"
#include "Rhombus.h"
#include "Trapeze.h"
#include "Quadrate.h"
#include "Parallelogram.h"
#include "Pentagon.h"
#include "Hexagon.h"

class FactoryShape
{
public:
	bool CanIDo(const int size);
	Shape* CreateShape(int size, Point* ptr);
	Triangle* CreateTriangle(Point* ptr);
	Quadrangle* CreateQuadrangle(Point* ptr);
};