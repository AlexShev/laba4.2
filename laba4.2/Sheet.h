#pragma once
#include <map>
#include <set>
#include <list>
#include "Shape.h"

class Sheet
{
public:
	const std::set<int>& GetIdIHave() const { return _iHaveTheseId; }
	const std::map<int, Shape*>& GetMapById() const { return _shapeById; }
	const std::map<Point, std::set<int>>& GetMapByPoint() const { return _shapesByPoint; }
	
	void Insert(Shape* ref);
	void EraseById(int id);
	void EraseByPoint(const Point& point);

	const Shape& operator[](int index) const;
	const std::list<Shape*> operator[](const Point& point) const;
	const Shape& RotationShape(int id, double angle);
	const Shape& ShiftShape(int id, const Point& vector);

	void Clear();
	int GetSize() const { return _shapeById.size(); }
	void IdEr(int id) const;
	void PointEr(const Point& point) const;
	~Sheet() { Clear(); }

private:
	void InsertInShapesByPoint(const Shape& shape);
	void EraseInShapesByPoint(const Shape& shape);
	void InsertInShapeById(Shape* shape);
	void EraseInShapeById(int id);

	// попытка оптимизации по быстродействию в ущерб памяти, учитывая погрешности
	std::map<int, Shape*> _shapeById;
	std::map<Point, std::set<int>> _shapesByPoint;
	std::set<int> _iHaveTheseId;
};