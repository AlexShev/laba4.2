#include "Sheet.h"

void Sheet::Insert(Shape* shape)
{
	InsertInShapeById(shape);
	
	InsertInShapesByPoint(*shape);
}

void Sheet::EraseById(int id)
{
	IdEr(id);

	EraseInShapesByPoint(*_shapeById[id]);
	
	EraseInShapeById(id);
}

void Sheet::EraseByPoint(const Point& point)
{
	PointEr(point);

	std::list<Shape*> temp = operator[](point);

	for (auto it : temp)
	{
		EraseInShapesByPoint(*it);
	}

	for (auto it : temp)
	{	
		EraseInShapeById(it->GetId());
	}
}

const Shape& Sheet::operator[](int id) const
{
	IdEr(id);

	return *_shapeById.at(id);
}

const std::list<Shape*> Sheet::operator[](const Point& point) const
{
	PointEr(point);

	std::list<Shape*> temp;

	for (auto it = _shapesByPoint.at(point).begin(); it != _shapesByPoint.at(point).end(); ++it)
	{
		temp.push_back(_shapeById.find(*it)->second);
	}

	return temp;
}

const Shape& Sheet::RotationShape(int id, double angle)
{
	Shape* temp = _shapeById[id];

	EraseInShapesByPoint(*temp);

	temp->Rotation(angle);

	InsertInShapesByPoint(*temp);

	return *temp;
}

const Shape& Sheet::ShiftShape(int id, const Point& vector)
{
	Shape* temp = _shapeById[id];

	EraseInShapesByPoint(*temp);

	temp->Shift(vector);

	InsertInShapesByPoint(*temp);

	return *temp;
}

void Sheet::Clear()
{
	if (_shapeById.size()) for (auto p : _shapeById) delete p.second;

	_iHaveTheseId.clear();

	_shapeById.clear();

	_shapesByPoint.clear();
}

void Sheet::IdEr(int id) const
{
	auto it = std::find(_iHaveTheseId.begin(), _iHaveTheseId.end(), id);

	if (it == _iHaveTheseId.end()) throw std::logic_error("Не существующий Id!!");
}

void Sheet::PointEr(const Point & point) const
{
	if (_shapesByPoint.find(point) == _shapesByPoint.end()) throw std::logic_error("Фигур с такой вершиной нет!!");
}

void Sheet::InsertInShapesByPoint(const Shape& shape)
{
	int size = shape.GetSize();

	int id = shape.GetId();

	for (int i = 0; i < size; i++)
	{
		_shapesByPoint[shape[i]].insert(id);
	}
}

void Sheet::EraseInShapesByPoint(const Shape& shape)
{
	int size = shape.GetSize();

	int id = shape.GetId();

	for (int i = 0; i < size; i++)
	{
		Point temp = shape[i];

		_shapesByPoint[temp].erase(id);

		if (_shapesByPoint[temp].empty()) 
		{
			_shapesByPoint.erase(temp);
		}
	}
}

void Sheet::InsertInShapeById(Shape* shape)
{
	int id = shape->GetId();

	_iHaveTheseId.insert(id);

	_shapeById.insert(std::make_pair(id, shape));
}

void Sheet::EraseInShapeById(int id)
{
	_iHaveTheseId.erase(id);

	delete _shapeById[id];

	_shapeById.erase(id);
}