#pragma once

#include <iostream>
#include <map>
#include <algorithm>

struct Position
{    
    int x;
    int y;

    bool operator<(const Position& other) const
    {
        return (x < other.x || (x == other.x && (y < other.y)));
    }
};

template <typename T, T initial>
class Matrix
{
private:
    std::map<Position, T> data;
public:
    class SubMatrix
    {
    public:        
        SubMatrix(Matrix& m, int x):
            matrix(m),
            m_x(x)
        {}

        T& operator[](int y)
        {
            return matrix.data[{m_x, y}];
        }

    private:
        Matrix& matrix;
        int m_x;
    };

    SubMatrix operator[](int x)
    {
        return SubMatrix(*this, x);
    }

    int size()
    {
        return std::count_if(data.begin(), data.end(), [](const auto& pair)
        {
            return pair.second != initial;
        });
    }
    
    class Iterator
    {
    private:
        typename std::map<Position, T>::iterator iter;
    public:
        Iterator(typename std::map<Position, T>::iterator it) : iter(it) {}

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