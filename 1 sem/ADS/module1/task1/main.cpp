// 1.4
// Инвертируйте значение бита в числе N по его номеру K.
// Необходимо использование битовых операций.
// Использование арифметических операций запрещено.

#include <iostream>

unsigned int solve(unsigned int N, unsigned int K)
{
    return N ^ (1 << K);
}

int main()
{
    unsigned int N, K;
    std::cin >> N >> K;
    std::cout << solve(N, K);
    return 0;
}