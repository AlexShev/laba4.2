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
		cout << "Хотите использовать данные из файла?\n";
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
				cout << "Чтобы использовть данные с прошлого запуска нажимите 1\n";
				cout << "Чтобы использовать файл с параметрами по умолчанию нажимите 2\n";
				switch (ReadComand())
				{
				case 1: namefile = "result.txt"; break;
				case 2: namefile = "source.txt"; break;
				default: throw std::logic_error("Вы что-то не так нажали");
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
		cout << "Хотите сохранить данные в файла?\n";
		if (Confirmation()) DounlandDataToFile(XoY);
	}
	catch (std::exception & err)
	{
		std::cerr << endl << endl << err.what() << endl << endl;
	}
}

void Console::Menu()
{
	cout << "Выберете действие\n";
	cout << " 0: завершить работу\n";
	cout << " 1: добавить фигуру на плоскость\n";
	cout << " 2: удалить фигуру по Id\n";
	cout << " 3: удалить фигуры содержащие введённую вершину\n";
	cout << " 4: почистить плоскость\n";
	cout << " 5: показать фигуру на плоскости\n";
	cout << " 6: показать фигуры содержащие введённую вершину\n";
	cout << " 7: показать информацию о всех фигурах на плоскости\n";
	cout << " 8: показать информацию о фигурах по номеру\n";
	cout << " 9: показать информацию о фигурах содержащие введённую вершину\n";
	cout << "10: вращение выбранной фигуры на введённый угол\n";
	cout << "11: перемещение выбранной фигуры на введённый вектор\n";
	cout << "12: сравнить площади двух выбронных фигур\n";
	cout << "13: проверить на пересечение две фигуры\n";
	cout << "14: проверить на включене одной фигуры в другую\n";
}

void Console::AddShapeToSheet(Sheet& XoY) const
{
		XoY.Insert(ReadShape());
		cout << "\nФигура занесёна на плоскость.\n\n";
}

void Console::EraseById(Sheet& XoY)
{
	if (ThereIsShape(XoY))
	{
		int index = ReadId(XoY);
		if (Confirmation())
		{
			XoY.EraseById(index);
			cout << "Фигура удалена!\n\n";
		}
	}
}

void Console::EraseByPoint(Sheet& XoY)
{
	if (ThereIsShape(XoY))
	{
		cout << "Введите точку!\n";
		Point point;
		cin >> point;
		if (Confirmation())
		{
			XoY.EraseByPoint(point);
			cout << "\nФигуры содержащие эту точку удалены!\n\n";
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
			cout << "Плоскость отчищена!\n\n";
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
		cout << "Введите точку!\n";
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
	cout << "Координыты центра " << shape->Center() << endl << endl;
}

void Console::ShowShapeInformationByPoint(const Sheet& XoY) const
{
	if (ThereIsShape(XoY))
	{
		cout << "Введите точку!\n";
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
		cout << "Введите угол поворота в градусах\n";
		cin >> angle;

		if (Confirmation())
		{
			cout << "\nФигура успешно повёрнута.\n" << XoY.RotationShape(id, angle) << endl;
		}
	}
}

void Console::ShiftShape(Sheet& XoY)
{
	if (ThereIsShape(XoY))
	{
		int id = ReadId(XoY);

		Point vector;
		cout << "Введите вектор смещения\n";
		cin >> vector;

		if (Confirmation())
		{
			cout << "\nФигура сдвинута на введённый вектор.\n" << XoY.ShiftShape(id, vector) << endl << endl;
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

		cout << "Первая фигура:\n" << XoY[i1] << endl;
		cout << "Вторая фигура:\n" << XoY[i2] << endl;

		double Comparison = XoY[i1].Comparison(XoY[i2]);

		if (Comparison > 1)
		{
			cout << "площадь первой фигуры больше второй в " << Comparison << " раз\n\n";
		}
		else if (Comparison < -1)
		{
			cout << "площадь второй фигуры больше первой в " << -Comparison << " раз\n\n";
		}
		else
		{
			cout << "площадь первой фигуры равна площади второй\n\n";
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

		cout << "Первая фигура:\n" << XoY[i1] << endl;
		cout << "Вторая фигура:\n" << XoY[i2] << endl;

		if (XoY[i1].Intersection(XoY[i2]))
		{
			cout << "Есть пересечение.\n\n";
		}
		else
		{
			cout << "Нет пересечения.\n\n";
		}

	}
}

void Console::IncludeShape(const Sheet& XoY) const
{
	if (ThereAreShapes(XoY))
	{
		int i1, i2;
		SetTwoId(i1, i2, XoY);
		cout << "Первая фигура:\n" << XoY[i1] << endl;
		cout << "Вторая фигура:\n" << XoY[i2] << endl;

		if (XoY[i2].Include(XoY[i1]))
		{
			cout << "Первая фигура входит во вторую.\n\n";
		}
		else
		{
			cout << "Первая фигура НЕ входит во вторую.\n\n";
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
	else throw std::logic_error("Ошибка чтения файла!!");
}

void Console::DounlandDataToFile(Sheet& XoY) 
{
	std::ofstream fout;
	fout.open("result.txt");

	if (fout.is_open())
	{
		if(XoY.GetMapById().empty()) throw std::logic_error("К сожалению плоскость пуска, ничего не записалось!!");

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
	else throw std::logic_error("Ошибка чтения файла!!");
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
		cout << "Доступные Id:";
		for (auto it : XoY.GetIdIHave())
		{
			cout << "  " << it;
		}
		cout << "\nВведите Id интересующей фигуры\n";
		int id = ReadComand();
		XoY.IdEr(id);
		return id;
	}
}

void Console::SetTwoId(int& i1, int& i2, const Sheet& XoY) const
{
	i1 = ReadId(XoY);
	do {
		cout << "Введите Id друго фигуры, кроме " << i1 << endl;
		i2 = ReadId(XoY);
	} while (i1 == i2);
}

bool Console::Confirmation() const
{
	string i;
	cout << "Введите 0 для подтверждения, иначе любую другую комбинацию клавишь: ";
	cin >> i;
	if(i != "0") cout << "\nОтмена команды!\n\n";
	return i == "0";
}

bool Console::ThereIsShape(const Sheet& XoY) const
{
	if (XoY.GetSize() > 0) return true;
	cout << "Плоскость пуста, добавте фигуру (команда 1)\n\n";
	return false;
}

bool Console::ThereAreShapes(const Sheet& XoY) const
{
	ThereIsShape(XoY);
	if (XoY.GetSize() > 1) return true;
	cout << "На плоскости меньше двух фигур, добавте фигуру (команда 1)\n\n";
	return false;
}