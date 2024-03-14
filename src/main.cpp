#include <iostream>
#include "matrix.hpp"

int main()
{
    const int default_value = 0;

    //  При запуске программы необходимо создать матрицу с пустым значением 0.
    Matrix<int, default_value> matrix;

    //  Заполнить главную диагональ матрицы (от [0,0] до [9,9]) значениями от 0 до 9.
    //  Второстепенную диагональ (от [0,9] до [9,0]) значениями от 9 до 0.
    for (int i = 0; i < 10; ++i) 
    {
        matrix[i][i] = i;
        matrix[i][9 - i] = 9 - i;
    }

    //  Необходимо вывести фрагмент матрицы от [1,1] до [8,8]. Между столбцами пробел.
    //  Каждая строка матрицы на новой строке консоли.
    for (int i = 1; i < 9; ++i)
        for (int j = 1; j < 9; ++j)
            std::cout << matrix[i][j] << ((j < 8) ? " " : "\n");

    //  Вывести количество занятых ячеек.
    std::cout << "Filled cells count = " << matrix.size() << std::endl;

    //  Вывести все занятые ячейки вместе со своими позициями.
    int pos_x, pos_y, value;
    for (auto cell: matrix)
    {
        std::tie(pos_x, pos_y, value) = cell;
        if (value != default_value)
            std::cout << "(" << pos_x << ";" << pos_y << ") = " << value << std::endl;
    }

    return 0;
}