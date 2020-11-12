#pragma once
#include <iostream>
#include "Sheet.h"
#include "ConcoleForFactoryShape.h"

class Console
{
	friend class ConsoleForSheetMaager;
public:
	void Run();								// исполнитель
private:
	void Menu();												// функционал
																	
	void AddShapeToSheet(Sheet& XoY) const;						// №1 добавить треугольник
	void EraseById(Sheet& XoY);									// №2 удалить по Id
	void EraseByPoint(Sheet& XoY);								// №3 удалить по точке
	void Clear(Sheet& XoY);										// №4 отчистить плоскость
	void ShowSheet(const Sheet& XoY) const;						// №5 показать координаиы треугольников
	void ShowShapeByPoint(const Sheet& XoY) const;				// №6 информация о треугольнике по точке
	void ShowAllInformation(const Sheet& XoY) const;			// №7 информация о всех треугольниках
	void ShowShapeInformation(const Shape* shape) const;		// №8 информация о треугольнике по номеру
	void ShowShapeInformationByPoint(const Sheet& XoY) const;	// №9 информация о треугольнике по точке
	void RotationShape(Sheet& XoY);								// №10 вращение фигуры
	void ShiftShape(Sheet& XoY);								// №11 перемещение фигуры
	void ComparisonShape(const Sheet& XoY) const;				// №12 сравнение площади фигур
	void IntersectionShape(const Sheet& XoY) const;				// №13 пересечение фигур
	void IncludeShape(const Sheet& XoY) const;					// №14 вложение фигур

	int ReadComand() const;
	void ReadDataFromFile(Sheet& XoY, const string& nameFile);
	void DounlandDataToFile(Sheet& XoY);
	Shape* ReadShape() const;									// установка параметров треугольника 
	int ReadId(const Sheet& XoY) const;							// ввести существующий индекс
	void SetTwoId(int& i1, int& i2, const Sheet& XoY) const;	// ввод пары существующих индексов
	bool Confirmation() const;									// запрос на подтверждение
	bool ThereIsShape(const Sheet& XoY) const;
	bool ThereAreShapes(const Sheet& XoY) const;
};