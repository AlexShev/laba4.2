#pragma once
#include <iostream>
#include "Sheet.h"
#include "ConcoleForFactoryShape.h"

class Console
{
	friend class ConsoleForSheetMaager;
public:
	void Run();								// �����������
private:
	void Menu();												// ����������
																	
	void AddShapeToSheet(Sheet& XoY) const;						// �1 �������� �����������
	void EraseById(Sheet& XoY);									// �2 ������� �� Id
	void EraseByPoint(Sheet& XoY);								// �3 ������� �� �����
	void Clear(Sheet& XoY);										// �4 ��������� ���������
	void ShowSheet(const Sheet& XoY) const;						// �5 �������� ���������� �������������
	void ShowShapeByPoint(const Sheet& XoY) const;				// �6 ���������� � ������������ �� �����
	void ShowAllInformation(const Sheet& XoY) const;			// �7 ���������� � ���� �������������
	void ShowShapeInformation(const Shape* shape) const;		// �8 ���������� � ������������ �� ������
	void ShowShapeInformationByPoint(const Sheet& XoY) const;	// �9 ���������� � ������������ �� �����
	void RotationShape(Sheet& XoY);								// �10 �������� ������
	void ShiftShape(Sheet& XoY);								// �11 ����������� ������
	void ComparisonShape(const Sheet& XoY) const;				// �12 ��������� ������� �����
	void IntersectionShape(const Sheet& XoY) const;				// �13 ����������� �����
	void IncludeShape(const Sheet& XoY) const;					// �14 �������� �����

	int ReadComand() const;
	void ReadDataFromFile(Sheet& XoY, const string& nameFile);
	void DounlandDataToFile(Sheet& XoY);
	Shape* ReadShape() const;									// ��������� ���������� ������������ 
	int ReadId(const Sheet& XoY) const;							// ������ ������������ ������
	void SetTwoId(int& i1, int& i2, const Sheet& XoY) const;	// ���� ���� ������������ ��������
	bool Confirmation() const;									// ������ �� �������������
	bool ThereIsShape(const Sheet& XoY) const;
	bool ThereAreShapes(const Sheet& XoY) const;
};