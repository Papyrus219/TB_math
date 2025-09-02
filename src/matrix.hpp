#ifndef TB_MATH_MATRIX_HPP
#define TB_MATH_MATRIX_HPP

#include<initializer_list>
#include"exeptions.hpp"

namespace tbmath
{

template<typename T ,int Y, int X>
class Matrix
{
private:
    class Row
    {
        T& operator[](int b);

        T* row{};

        ~Row() {delete row;}
    };

    Row* matrix{};

public:
    Matrix(std::initializer_list<T> content = {});
    int Size() {return X * Y;};
    int Y_size() {return Y;};
    int X_size() {return X;};

    Row& operator[](int a);

    Matrix operator*(int a);
    Matrix& operator*=(int a);
    Matrix operator+(Matrix a);
    Matrix& operator+=(Matrix a);

    Matrix<T,X,Y> Transform();

    ~Matrix() {delete matrix;}
};

template<typename T, int Y, int X> Matrix<T,Y,X> operator*(Matrix<T,Y,X> a, int b)
{
    for(int i=0;i<Y;i++)
    {
        for(int j=1;j<=X;j++)
        {
            a.matrix[i][j] *= a;
        }
    }

    return a;
}

template<typename T, int Y, int X> Matrix<T, Y, X>::Matrix(std::initializer_list<T> content)
{
    matrix = new Row[Y];

    for(int i=0;i<Y;i++)
        matrix[i].row = new T[X];

    int i{},j{};
    for(auto el : content)
    {
        matrix[i].row[j] = el;

        j++;
        if(j == X)
        {
            i++;
            j = 0;

            if(i == Y)
                throw TB_Out_of_range{"Too much value to inicializate!"};
        }
    }
}

template<typename T, int Y, int X> typename Matrix<T,Y,X>::Row& Matrix<T, Y, X>::operator[](int a)
{
    if(a < 1)
        throw TB_Out_of_range{"The first [] value is too low!"};
    else if(a >= Y)
        throw TB_Out_of_range{"The first [] value is too high!"};

    return matrix[a-1];
}

template<typename T, int Y, int X> T & Matrix<T, Y, X>::Row::operator[](int b)
{
    if(b < 1)
        throw TB_Out_of_range{"The second [] value is too low!"};
    else if(b >= X)
        throw TB_Out_of_range{"The second [] value is too high!"};

    return row[b-1];
}

template<typename T, int Y, int X> Matrix<T, Y, X> Matrix<T, Y, X>::operator*(int a)
{
    Matrix result = *this;

    for(int i=1;i<=Y;i++)
    {
        for(int j=1;j<=X;j++)
        {
            result[i][j] *= a;
        }
    }

    return result;
}

template<typename T, int Y, int X> Matrix<T,Y,X>& Matrix<T,Y,X>::operator*=(int a)
{
    for(int i=1;i<=Y;i++)
    {
        for(int j=1;j<=X;j++)
        {
            this[i][j] *= a;
        }
    }

    return *this;
}

template<typename T, int Y, int X> Matrix<T,Y,X> Matrix<T,Y,X>::operator+(Matrix a)
{
    if(this->Y_size() != a.Y_size())
        throw TB_Dont_compatible{"Number of lines dont match!"};
    if(this->X_size() != a.X_size())
        throw TB_Dont_compatible{"Number of columns dont match!"};

    Matrix result = a;

    for(int i=1;i<=Y;i++)
    {
        for(int j=1;j<=X;j++)
        {
            result[i][j] += a[i][j];
        }
    }

    return result;
}

template<typename T, int Y, int X> Matrix<T,Y,X>& Matrix<T,Y,X>::operator+=(Matrix a)
{
    if(this->Y_size() != a.Y_size())
        throw TB_Dont_compatible{"Number of lines dont match!"};
    if(this->X_size() != a.X_size())
        throw TB_Dont_compatible{"Number of columns dont match!"};

    for(int i=1;i<=Y;i++)
    {
        for(int j=1;j<=X;j++)
        {
            *this[i][j] += a[i][j];
        }
    }

    return *this;
}

template<typename T, int Y, int X> Matrix<T,X,Y> Matrix<T,Y,X>::Transform()
{
    Matrix<T,X,Y> result;

    for(int i=1;i<=Y;i++)
    {
        for(int j=1;j<=X;j++)
        {
            result[j][i] = *this[i][j];
        }
    }
}

}

#endif
