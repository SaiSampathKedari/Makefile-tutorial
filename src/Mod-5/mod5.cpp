#include <iostream>
#include "mod2.h"
#include "mod4.h"

int main()
{
    std::cout << " I am mod 5 calling fun 2 of mod2.so \n";
    fun2();
    std::cout << " Calling mod4.a - static library function f4() \n";
    f4();

    return EXIT_SUCCESS;
}