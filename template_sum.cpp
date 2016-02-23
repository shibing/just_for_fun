#include <iostream>

template <typename T>
T sum(const T& val)
{
    return val;
}

template <typename T, typename ... Args>
T sum(const T&val, const Args& ... valList)
{
    return val + sum(valList...);
}

int main()
{
    std::cout << sum(1, 2, 4, 5, 6, 7, 8, 9, 10) << std::endl;
}