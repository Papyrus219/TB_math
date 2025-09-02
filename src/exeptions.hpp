#ifndef TB_MATH_EXEPTIONS
#define TB_MATH_EXEPTIONS

#include<string>

namespace tbmath
{

struct TB_Exeption
{
    TB_Exeption(std::string reason): reason{reason} {};
    std::string reason{};
};

struct TB_Out_of_range: public TB_Exeption
{
    TB_Out_of_range(std::string reason): TB_Exeption{reason} {};
};

struct TB_Dont_compatible: public TB_Exeption
{
    TB_Dont_compatible(std::string reason): TB_Exeption{reason} {};
};

}

#endif
