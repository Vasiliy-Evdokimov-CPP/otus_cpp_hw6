/**
    \file
    \brief
        В файле описывается шаблонный класс разреженной матрицы, а также вспомогательная структура Position
*/

#pragma once

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
public:

    /**
        \brief
            Порокси-класс для работы с элементами матрицы
        \details
            Используется для контроля присваиваемых и возвращаемых значений согласно заданию
    */
    template <typename R>
    class Element
    {
    public:
        /**
            \brief
                Констуктор класса
            \param matrix ссылка на матрицу
            \param position позиция элемента
        */    
        Element(Matrix& matrix, Position position) : 
            m_matrix(matrix),
            m_position(position)            
        {}

        /**
            \brief
                Переопределение оператора присваивания значения элементу
            \param new_value присваиваемое значение
        */
        Element& operator=(R new_value)
        {
            if (new_value == initial)
            {
                auto it = m_matrix.data.find(m_position);
                if (it != m_matrix.data.end())
                    m_matrix.data.erase(it);
            } else {
                m_matrix.data[m_position] = new_value;
            }
            //
            return *this;    
        }        

        /**
            \brief
                Переопределение оператора получения значения элемента            
        */
        operator R() const
        {
            if (m_matrix.data.find(m_position) == m_matrix.data.end())
            {                
                return initial;
            } else {             
                return m_matrix.data[m_position];
            }
        } 

    private:
        /**
            \brief
                Ссылка на матрицу
        */
        Matrix& m_matrix;
        /**
            \brief
                Позиция элемента
        */
        Position m_position;        
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
        Element<T> operator[](int y)
        {            
            Position key{m_x, y};
            Element<T> new_element(matrix, key);
            return new_element;
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
        return data.size();
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
private:
    /**
        \brief
            Данные матрицы
    */     
    std::map<Position, T> data;
};