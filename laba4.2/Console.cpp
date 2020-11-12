#include "Console.h"
#include <fstream>

using std::cout;
using std::cin;
using std::endl;

void Console::Run()
{
	Sheet XoY;
	try
	{
		cout << "������ ������������ ������ �� �����?\n";
		if (Confirmation())
		{
			string namefile;
			std::ifstream fin;
			fin.open("result.txt");

			if (fin.peek() == EOF) 
			{
				namefile = "source.txt";
			}
			else
			{
				cout << "����� ����������� ������ � �������� ������� �������� 1\n";
				cout << "����� ������������ ���� � ����������� �� ��������� �������� 2\n";
				switch (ReadComand())
				{
				case 1: namefile = "result.txt"; break;
				case 2: namefile = "source.txt"; break;
				default: throw std::logic_error("�� ���-�� �� ��� ������");
				}
			}
			fin.close();
			ReadDataFromFile(XoY, namefile);
		}
	}
	catch (std::exception & err)
	{
		std::cerr << endl << err.what() << endl << endl;
	}

	int operation;
	do {
		try {
			Menu();
			operation = ReadComand();
			switch (operation)
			{
			case 1:	AddShapeToSheet(XoY); break;
			case 2:	EraseById(XoY); break;
			case 3:	EraseByPoint(XoY); break;
			case 4:	Clear(XoY); break;
			case 5:	ShowSheet(XoY); break;
			case 6:	ShowShapeByPoint(XoY); break;
			case 7:	ShowAllInformation(XoY); break;
			case 8:
				if (ThereIsShape(XoY))
				{
					ShowShapeInformation(&XoY[ReadId(XoY)]);
				}
				break;
			case 9:	ShowShapeInformationByPoint(XoY); break;
			case 10: RotationShape(XoY); break;
			case 11: ShiftShape(XoY); break;
			case 12: ComparisonShape(XoY); break;
			case 13: IntersectionShape(XoY); break;
			case 14: IncludeShape(XoY); break;
			}
		}
		catch (std::exception & err)
		{
			std::cerr << endl << endl << err.what() << endl << endl;
		}

	} while (operation != 0);
	
	try
	{
		cout << "������ ��������� ������ � �����?\n";
		if (Confirmation()) DounlandDataToFile(XoY);
	}
	catch (std::exception & err)
	{
		std::cerr << endl << endl << err.what() << endl << endl;
	}
}

void Console::Menu()
{
	cout << "�������� ��������\n";
	cout << " 0: ��������� ������\n";
	cout << " 1: �������� ������ �� ���������\n";
	cout << " 2: ������� ������ �� Id\n";
	cout << " 3: ������� ������ ���������� �������� �������\n";
	cout << " 4: ��������� ���������\n";
	cout << " 5: �������� ������ �� ���������\n";
	cout << " 6: �������� ������ ���������� �������� �������\n";
	cout << " 7: �������� ���������� � ���� ������� �� ���������\n";
	cout << " 8: �������� ���������� � ������� �� ������\n";
	cout << " 9: �������� ���������� � ������� ���������� �������� �������\n";
	cout << "10: �������� ��������� ������ �� �������� ����\n";
	cout << "11: ����������� ��������� ������ �� �������� ������\n";
	cout << "12: �������� ������� ���� ��������� �����\n";
	cout << "13: ��������� �� ����������� ��� ������\n";
	cout << "14: ��������� �� �������� ����� ������ � ������\n";
}

void Console::AddShapeToSheet(Sheet& XoY) const
{
		XoY.Insert(ReadShape());
		cout << "\n������ ������� �� ���������.\n\n";
}

void Console::EraseById(Sheet& XoY)
{
	if (ThereIsShape(XoY))
	{
		int index = ReadId(XoY);
		if (Confirmation())
		{
			XoY.EraseById(index);
			cout << "������ �������!\n\n";
		}
	}
}

void Console::EraseByPoint(Sheet& XoY)
{
	if (ThereIsShape(XoY))
	{
		cout << "������� �����!\n";
		Point point;
		cin >> point;
		if (Confirmation())
		{
			XoY.EraseByPoint(point);
			cout << "\n������ ���������� ��� ����� �������!\n\n";
		}
	}
}

void Console::Clear(Sheet& XoY)
{
	if (ThereIsShape(XoY))
	{
		if (Confirmation())
		{
			XoY.Clear();
			cout << "��������� ��������!\n\n";
		}
	}
}

void Console::ShowSheet(const Sheet& XoY) const
{
	if (ThereIsShape(XoY))
	{
		for (const auto &p : XoY.GetMapById())
		{
			cout << "Id "  << p.second->GetId() << "    " << *p.second << endl << endl;
		}
	}
}

void Console::ShowShapeByPoint(const Sheet& XoY) const
{
	if (ThereIsShape(XoY))
	{
		cout << "������� �����!\n";
		Point point;
		cin >> point;

		for (const auto& p : XoY[point])
		{
			cout << "Id " << p->GetId() << "    " << *p << endl << endl;
		}
	}
}

void Console::ShowAllInformation(const Sheet& XoY) const
{
	if (ThereIsShape(XoY))
	{
		for (const auto& p : XoY.GetMapById())
		{
			ShowShapeInformation(p.second);
		}
	}
}

void Console::ShowShapeInformation(const Shape* shape) const
{
	cout << "Id " << shape->GetId() << endl;
	cout << shape->TypeOfShape() << endl;
	cout << *shape << endl;
	cout << "S= " << shape->Squear() << endl;
	cout << "P= " << shape->Perimeter() << endl;
	cout << "���������� ������ " << shape->Center() << endl << endl;
}

void Console::ShowShapeInformationByPoint(const Sheet& XoY) const
{
	if (ThereIsShape(XoY))
	{
		cout << "������� �����!\n";
		Point point;
		cin >> point;

		for (const auto& p : XoY[point])
		{
			ShowShapeInformation(p);
		}
	}
}

void Console::RotationShape(Sheet& XoY)
{
	if (ThereIsShape(XoY))
	{
		int id = ReadId(XoY);

		double angle;
		cout << "������� ���� �������� � ��������\n";
		cin >> angle;

		if (Confirmation())
		{
			cout << "\n������ ������� ��������.\n" << XoY.RotationShape(id, angle) << endl;
		}
	}
}

void Console::ShiftShape(Sheet& XoY)
{
	if (ThereIsShape(XoY))
	{
		int id = ReadId(XoY);

		Point vector;
		cout << "������� ������ ��������\n";
		cin >> vector;

		if (Confirmation())
		{
			cout << "\n������ �������� �� �������� ������.\n" << XoY.ShiftShape(id, vector) << endl << endl;
		}
	}
}

void Console::ComparisonShape(const Sheet& XoY) const
{
	if (ThereAreShapes(XoY))
	{
		int i1, i2;
		if (XoY.GetSize() == 2)
		{
			i1 = XoY.GetMapById().cbegin()->first;
			i2 = XoY.GetMapById().crbegin()->first;
		}
		else
		{
			SetTwoId(i1, i2, XoY);
		}

		cout << "������ ������:\n" << XoY[i1] << endl;
		cout << "������ ������:\n" << XoY[i2] << endl;

		double Comparison = XoY[i1].Comparison(XoY[i2]);

		if (Comparison > 1)
		{
			cout << "������� ������ ������ ������ ������ � " << Comparison << " ���\n\n";
		}
		else if (Comparison < -1)
		{
			cout << "������� ������ ������ ������ ������ � " << -Comparison << " ���\n\n";
		}
		else
		{
			cout << "������� ������ ������ ����� ������� ������\n\n";
		}
	}
}

void Console::IntersectionShape(const Sheet& XoY) const
{
	if (ThereAreShapes(XoY))
	{
		int i1, i2;

		if (XoY.GetSize() == 2)
		{
			i1 = XoY.GetMapById().cbegin()->first;
			i2 = XoY.GetMapById().crbegin()->first;
		}
		else
		{
			SetTwoId(i1, i2, XoY);
		}

		cout << "������ ������:\n" << XoY[i1] << endl;
		cout << "������ ������:\n" << XoY[i2] << endl;

		if (XoY[i1].Intersection(XoY[i2]))
		{
			cout << "���� �����������.\n\n";
		}
		else
		{
			cout << "��� �����������.\n\n";
		}

	}
}

void Console::IncludeShape(const Sheet& XoY) const
{
	if (ThereAreShapes(XoY))
	{
		int i1, i2;
		SetTwoId(i1, i2, XoY);
		cout << "������ ������:\n" << XoY[i1] << endl;
		cout << "������ ������:\n" << XoY[i2] << endl;

		if (XoY[i2].Include(XoY[i1]))
		{
			cout << "������ ������ ������ �� ������.\n\n";
		}
		else
		{
			cout << "������ ������ �� ������ �� ������.\n\n";
		}
	}
}

Shape* Console::ReadShape() const
{
	ConsoleForFactoryShape F;
	return F.ReadShape();
}

void Console::ReadDataFromFile(Sheet& XoY, const string& nameFile)
{
	std::ifstream fin;
	fin.open(nameFile);
	
	FactoryShape Factory;

	if (fin.is_open())
	{
		while (true)
		{
			int size;
			fin >> size;
			if (fin.eof()) break;
			Point* ptr = new Point[size];
			for (int i = 0; i < size; i++)
			{
				fin >> ptr[i];
			}
			XoY.Insert(Factory.CreateShape(size, ptr));
			delete[] ptr;
		}
		fin.close();
	}
	else throw std::logic_error("������ ������ �����!!");
}

void Console::DounlandDataToFile(Sheet& XoY) 
{
	std::ofstream fout;
	fout.open("result.txt");

	if (fout.is_open())
	{
		if(XoY.GetMapById().empty()) throw std::logic_error("� ��������� ��������� �����, ������ �� ����������!!");

		for (auto it : XoY.GetMapById())
		{
			int size = it.second->GetSize();
			fout << size;
			for (int i = 0; i < size; i++)
			{
				fout << ' ' << it.second->operator[](i).X()<<' '<< it.second->operator[](i).Y();
			}
			fout << endl;
		}
		fout.close();
	}
	else throw std::logic_error("������ ������ �����!!");
}

int Console::ReadComand() const
{
	std::string s;
	cout << ">> ";
	cin >> s;
	cout << endl;
	for (auto c : s)
	{
		if (!isdigit(c))
			return -1;
	}
	return atoi(s.c_str());
}

int Console::ReadId(const Sheet& XoY) const
{
	if (XoY.GetSize() == 1) return XoY.GetMapById().cbegin()->first;

	if (XoY.GetSize() > 1)
	{
		cout << "��������� Id:";
		for (auto it : XoY.GetIdIHave())
		{
			cout << "  " << it;
		}
		cout << "\n������� Id ������������ ������\n";
		int id = ReadComand();
		XoY.IdEr(id);
		return id;
	}
}

void Console::SetTwoId(int& i1, int& i2, const Sheet& XoY) const
{
	i1 = ReadId(XoY);
	do {
		cout << "������� Id ����� ������, ����� " << i1 << endl;
		i2 = ReadId(XoY);
	} while (i1 == i2);
}

bool Console::Confirmation() const
{
	string i;
	cout << "������� 0 ��� �������������, ����� ����� ������ ���������� �������: ";
	cin >> i;
	if(i != "0") cout << "\n������ �������!\n\n";
	return i == "0";
}

bool Console::ThereIsShape(const Sheet& XoY) const
{
	if (XoY.GetSize() > 0) return true;
	cout << "��������� �����, ������� ������ (������� 1)\n\n";
	return false;
}

bool Console::ThereAreShapes(const Sheet& XoY) const
{
	ThereIsShape(XoY);
	if (XoY.GetSize() > 1) return true;
	cout << "�� ��������� ������ ���� �����, ������� ������ (������� 1)\n\n";
	return false;
}