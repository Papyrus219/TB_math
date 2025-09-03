#include<iostream>
#include"matrix.hpp"

int main()
{
    try
    {
        tbmath::Matrix<3,2> test1{2,3,5,6,0,1};
        tbmath::Matrix<2,4> test2{1,2,3,0,1,2,0,1};

        tbmath::Matrix<3,4> test3 = test1 * test2;

        std::cout << test3[2][2] << '\n';
    }
    catch(tbmath::TB_Exeption x)
    {
        std::cerr << x.reason << '\n';
    }

    return 0;
}
