#pragma once

/**
    \file
    \details
        В файле описывается шаблонный класс разреженной матрицы, а также вспомогательная структура Position
*/

#include <iostream>
#include <map>
#include <algorithm>

/**
    \brief
        Позиция элемента матрицы
    \details
        Используется в качестве ключа в std::map
*/
struct Position
{    
    /**
        \brief
            X координата элемента
    */
    int x;

    /**
        \brief
            Y координата элемента
    */
    int y;

    /**
        \brief
            Переопределение оператора "меньше", необходимое для использования структуры в качестве ключа std::map
        \param other ссылка на сравниваемую структуру
    */
    bool operator<(const Position& other) const
    {
        return (x < other.x || (x == other.x && (y < other.y)));
    }
};

/**
    \brief
        Шаблонный класс разреженной матрицы
    \details
        Специализируется типом элемента и значением по умолчанию
*/
template <typename T, T initial>
class Matrix
{
private:
    /**
        \brief
            Данные матрицы
    */     
    std::map<Position, T> data;
public:

    class Element
    {
    public:    
        Element(Matrix& matrix, /*Position position,*/ T value) : 
            m_matrix(matrix),
            // m_position(position),
            m_value(value)
        {}

        // Element& operator=(T new_value)
        // {

        // }        

        // operator T() const
        // {
            
        // } 

    private:
        Matrix& m_matrix;
        // Position m_position;
        T m_value;
    };


    /**
        \brief
            Вспомогательный вложенный прокси-класс
        \details
            Необходим для реализации обращения к элементам матрицы через оператор [][]
    */
    class SubMatrix
    {
    public: 
        /**
            \brief
                Конструктор класса
            \param super ссылка на матрицу "верхнего" уровня
            \param x X координата элемента
        */       
        SubMatrix(Matrix& super, int x):
            matrix(super),
            m_x(x)
        {}

        /**
            \brief
                Переопределение оператора []
            \param y Y координата элемента
        */
        T& operator[](int y)
        {
            Position key{m_x, y};
            return matrix.data[key];       
        }

    private:
        /**
            \brief
                Матрица "верхнего" уровня
        */
        Matrix& matrix;
        /**
            \brief
                X координата элемента
        */
        int m_x;
    };

    /**
        \brief
            Переопределение оператора []
        \param x X координата элемента
    */  
    SubMatrix operator[](int x)
    {
        return SubMatrix(*this, x);
    }

    /**
        \brief
            Метод, возвращающий количество занятых ячеек
        \details
            Подсчет количества ячеек не равных значению по умолчанию            
    */
    int size()
    {
        return std::count_if(data.begin(), data.end(), [](const auto& pair)
        {
            return pair.second != initial;
        });
    }

    /**
    \brief
        Реализация итератора для обхода элементов матрицы    
    */
    class Iterator
    {
    private:
        typename std::map<Position, T>::iterator iter;
    public:
        Iterator(typename std::map<Position, T>::iterator it) : iter(it) {}

        /**
            \brief
                Переопределение оператора разыменования элемента
            \details
                Врозвращает кортеж из координат элемента и его значения - необходим для реализации функциональности, требуемой по заданию 
        */
        std::tuple<int, int, T> operator*()
        {
            return { 
                iter->first.x, 
                iter->first.y, 
                iter->second 
            };
        }

        Iterator& operator++()
        {
            ++iter;
            return *this;
        }

        bool operator!=(const Iterator& other)
        {
            return iter != other.iter;
        }
    };

    Iterator begin()
    {
        return Iterator(data.begin());
    }

    Iterator end()
    {
        return Iterator(data.end());
    }
};