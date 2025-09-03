#ifndef TB_MATH_MATRIX_HPP
#define TB_MATH_MATRIX_HPP

#include<initializer_list>
#include"exeptions.hpp"

namespace tbmath
{

template<int Y, int X>
class Matrix
{
private:
    class Row
    {
    public:
        double& operator[](int b);

        ~Row() {if(row) delete[] row;}

    private:
        double* row{};
        int size_of_row{};

        friend class Matrix;
    };

    Row* matrix{};

public:
    Matrix(std::initializer_list<double> content = {});
    Matrix(const Matrix &orginal);
    Matrix(Matrix &&orginal);

    int Size() {return X * Y;};
    int Y_size() {return Y;};
    int X_size() {return X;};

    Row& operator[](int a);

    Matrix operator*(double a) const;
    Matrix& operator*=(double a);
    Matrix operator+(const Matrix &a) const;
    Matrix& operator+=(const Matrix &a);
    Matrix operator-(const Matrix &a) const;
    Matrix& operator-=(const Matrix &a);

    template<int M, int N>
    Matrix<Y,N> operator*(Matrix<M,N> &a);

    Matrix<X,Y> Transform();

    ~Matrix() {if(matrix) delete[] matrix;}
};

template<int Y, int X>
Matrix<Y,X> operator*(double b, Matrix<Y,X> a)
{
    for(int i=0;i<Y;i++)
    {
        for(int j=1;j<=X;j++)
        {
            a.matrix[i][j] *= b;
        }
    }

    return a;
}

template<int Y, int X>
Matrix<Y,X>::Matrix(const Matrix &orginal)
{
    this->matrix = new Row[Y];

    for(int i=0;i<Y;i++)
    {
        this->matrix[i].row = new double[X];
        this->matrix[i].size_of_row = X;
    }

    for(int i=1;i<=Y;i++)
    {
        for(int j=1;j<=X;j++)
        {
            *this[i][j] = orginal[i][j];
        }
    }
}

template<int Y, int X>
Matrix<Y,X>::Matrix(Matrix &&orginal)
{
    this->matrix = orginal.matrix;

    orginal.matrix = nullptr;
}

template<int Y, int X>
Matrix<Y, X>::Matrix(std::initializer_list<double> content)
{
    this->matrix = new Row[Y];

    for(int i=0;i<Y;i++)
    {
        this->matrix[i].row = new double[X];
        this->matrix[i].size_of_row = X;
    }

    int i{},j{},k{};
    for(auto el : content)
    {
        if(k >= Y*X)
            throw TB_Out_of_range{"Too much value to inicializate!"};

        this->matrix[i].row[j] = el;

        j++;
        if(j == X)
        {
            i++;
            j = 0;
        }
        k++;
    }
}

template<int Y, int X> typename Matrix<Y,X>::Row& Matrix<Y, X>::operator[](int a)
{
    if(a < 1)
        throw TB_Out_of_range{"The first [] value is too low!"};
    else if(a > Y)
        throw TB_Out_of_range{"The first [] value is too high!"};

    return matrix[a-1];
}

template<int Y, int X>
double& Matrix<Y, X>::Row::operator[](int b)
{
    if(b < 1)
        throw TB_Out_of_range{"The second [] value is too low!"};
    else if(b > X)
        throw TB_Out_of_range{"The second [] value is too high!"};

    return row[b-1];
}

template<int Y, int X>
Matrix<Y, X> Matrix<Y, X>::operator*(double a) const
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

template<int Y, int X>
Matrix<Y,X>& Matrix<Y,X>::operator*=(double a)
{
    for(int i=1;i<=Y;i++)
    {
        for(int j=1;j<=X;j++)
        {
            (*this)[i][j] *= a;
        }
    }

    return *this;
}

template<int Y, int X>
Matrix<Y,X> Matrix<Y,X>::operator+(const Matrix &a) const
{
    if(this->Y_size() != a.Y_size())
        throw TB_Dont_compatible{"Number of lines dont match!"};
    if(this->X_size() != a.X_size())
        throw TB_Dont_compatible{"Number of columns dont match!"};

    Matrix result = *this;

    for(int i=1;i<=Y;i++)
    {
        for(int j=1;j<=X;j++)
        {
            result[i][j] += a[i][j];
        }
    }

    return result;
}

template<int Y, int X>
Matrix<Y,X>& Matrix<Y,X>::operator+=(const Matrix &a)
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

template<int Y, int X>
Matrix<Y,X> Matrix<Y,X>::operator-(const Matrix &a) const
{
    if(this->Y_size() != a.Y_size())
        throw TB_Dont_compatible{"Number of lines dont match!"};
    if(this->X_size() != a.X_size())
        throw TB_Dont_compatible{"Number of columns dont match!"};

    Matrix result = *this;

    for(int i=1;i<=Y;i++)
    {
        for(int j=1;j<=X;j++)
        {
            result[i][j] += a[i][j];
        }
    }

    return result;
}

template<int Y, int X>
Matrix<Y,X>& Matrix<Y,X>::operator-=(const Matrix &a)
{
    if(this->Y_size() != a.Y_size())
        throw TB_Dont_compatible{"Number of lines dont match!"};
    if(this->X_size() != a.X_size())
        throw TB_Dont_compatible{"Number of columns dont match!"};

    for(int i=1;i<=Y;i++)
    {
        for(int j=1;j<=X;j++)
        {
            *this[i][j] -= a[i][j];
        }
    }

    return *this;
}

template<int Y, int X>
template<int M, int N>
Matrix<Y,N> Matrix<Y,X>::operator*(Matrix<M,N> &a)
{
    if(X != M)
        throw TB_Dont_compatible{"Number of lines don't match number of columns!"};

    Matrix<Y,N> result{};

    for(int i=1;i<Y;i++)
    {
        for(int j=1;j<=N;j++)
        {
            for(int k=1;k<=X;k++)
            {
                result[i][j] += ( ((*this)[i])[k] * (a[k])[j] );
            }
        }
    }

    return result;
}

template<int Y, int X>
Matrix<X,Y> Matrix<Y,X>::Transform()
{
    Matrix<X,Y> result;

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
