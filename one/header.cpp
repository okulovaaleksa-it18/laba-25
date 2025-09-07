#include "header.h"
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <string>
#include <sstream>

// Конструктор по умолчанию
Point::Point() : x(0), y(0) {}

// Конструктор с параметрами
Point::Point(double x, double y) : x(x), y(y) {}

// Конструктор копирования
Point::Point(const Point& other) : x(other.x), y(other.y) {}

// Координата x
double Point::getX() const { return x; }

// Координата y
double Point::getY() const { return y; }

// Расстояние до начала координат
double Point::distanceToOrigin() const 
{
    return sqrt(x * x + y * y);
}

// Уменьшить координаты на 1
Point Point::operator--() 
{
    --x;
    --y;
    return *this;
}

// Поменять местами
Point Point::operator-() 
{
    return Point(y, x);
}

// к целому (x)
Point::operator int() const 
{
    return static_cast<int>(x);
}

// к double (y)
Point::operator double() const
{
    return y;
}

// Уменьшить x на заданное целое число
Point Point::operator-(int value) 
{
    return Point(x - value, y);
}

// Расстояние между двумя точками
double Point::operator-(const Point& p) 
{
    return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
}

// Перегрузка вывода в поток
ostream& operator<<(ostream& os, const Point& p) 
{
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

double inputDouble(const string& prompt) 
{
    string line;
    double value;

    while (true) 
    {
        cout << prompt;
        getline(cin, line);
        stringstream ss(line);

        if (ss >> value) 
        {
            char extra;
            if (!(ss >> extra)) 
            {
                return value;
            }
        }
        cerr << "Ошибка! Введите корректное вещественное число. \n";
    }
}

int inputIntRange(const string& prompt, int min, int max) 
{
    string input;
    int value;

    while (true) 
    {
        cout << prompt;
        getline(cin, input); 

        try 
        {
            size_t pos;
            value = stoi(input, &pos);
            if (pos != input.length()) 
            {
                throw invalid_argument("Неверный символ");
            }
            if (value < min || value > max) 
            {
                throw out_of_range("Выход за пределы диапазона");
            }
            return value;
        }
        catch (exception&) 
        {
            cerr << "Ошибка! Введите целое число от " << min << " до " << max << ".\n";
        }
    }
}

Point getPointFromUserChoice() 
{
    cout << "\nВыберите источник данных:\n";
    cout << "1 - Ввод с клавиатуры\n";
    cout << "2 - Чтение из файла laba25.txt\n";
    cout << "3 - Случайная генерация\n";

    int choice = inputIntRange("Ваш выбор (1-3): ", 1, 3);

    switch (choice) 
    {
    case 1:
    {
        double x = inputDouble("Введите x: ");
        double y = inputDouble("Введите y: ");
        return Point(x, y);
    }
    case 2: 
    {
        ifstream file("laba25.txt");
        if (!file.is_open()) 
        {
            cerr << "Ошибка! Файл не найден. Будет использована точка (0, 0).\n";
            return Point();
        }
        double x, y;
        file >> x >> y;
        file.close();
        return Point(x, y);
    }
    case 3: 
    {
        cout << "Выберите тип генерации:\n";
        cout << "1 - Целые числа\n";
        cout << "2 - Вещественные числа\n";
        int genType = inputIntRange("Ваш выбор (1 или 2): ", 1, 2);

        if (genType == 1) 
        {
            int x = rand() % 101 - 50;
            int y = rand() % 101 - 50;
            return Point(x, y);
        }
        else 
        {
            double x = (rand() % 10001 - 5000) / 100.0;
            double y = (rand() % 10001 - 5000) / 100.0;
            return Point(x, y);
        }
    }
default:
    return Point();
    }
}

// Задание 1: работа с точкой
void task1()
{
    cout << "\n=== Задание 1 ===\n";

    Point p = getPointFromUserChoice();
    cout << "\nСозданная точка: " << p << endl;
    cout << "Расстояние до (0, 0): " << p.distanceToOrigin() << endl;
    Point pCopy = Point(p);
    cout << "Копия точки: " << pCopy << endl;
    Point c = Point();
    cout << "Нулевая координата: " << c << endl;
}

// Задание 2: перегрузка операций
void task2() 
{
    cout << "\n=== Задание 2 ===\n";

    Point p = getPointFromUserChoice();

    cout << "\nИсходная точка: " << p << endl;
    cout << "\nУнарные операции:\n";
    --p; // уменьшить координаты
    cout << "--p: " << p << endl;

    Point pSwapped = -p; // поменять местами
    cout << "-p: " << pSwapped << endl;

    // Приведения типов
    cout << "\nПриведение типов:\n";
    int xInt = p; // приведение к int
    double yDouble = static_cast<double>(p); // приведение к double
    cout << "int(p): " << xInt << endl;
    cout << "double(p): " << yDouble << endl;

    // Бинарные операции
    cout << "\nБинарные операции:\n";
    int n = inputIntRange("Введите число, на которое уменьшить x: ", -1000, 1000);
    Point pMod = p - n; // уменьшить x на n
    cout << "p - " << n << ": " << pMod << endl;

    // Ввод второй точки
    cout << "Введите вторую точку:\n";
    double x2 = inputDouble("Введите x: ");
    double y2 = inputDouble("Введите y: ");
    Point p2(x2, y2);
    double d = pMod - p2; // расстояние между двумя точками
    cout << "Расстояние до " << p2 << ": " << d << endl;
}
