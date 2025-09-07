#include "header.h"
#include <ctime>

int main() 
{
    setlocale(LC_ALL, "Russian");
    srand(static_cast<unsigned>(time(0)));

    cout << "Выберите задание:\n";
    cout << "1 - Базовые операции с точкой\n";
    cout << "2 - Перегруженные операции\n";

    int choice = inputIntRange("Ваш выбор (1 или 2): ", 1, 2);

    if (choice == 1)
        task1();
    else
        task2();

    return 0;
}
