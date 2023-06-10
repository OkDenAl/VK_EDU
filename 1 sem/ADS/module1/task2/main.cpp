// 2.2 Унимодальная последовательность
// Дан массив целых чисел А[0..n-1]. Известно, что на интервале [0, m] значения массива строго возрастают,
// а на интервале [m, n-1] строго убывают. Найти m за O( log m ).
// 2 ≤ n ≤ 10000.

#include <iostream>

int binsearch(int l, int r, int *arr)
{
    while (r - l > 1)
    {
        int mid = (r + l) / 2;
        if (arr[mid] > arr[l])
        {
            l = mid;
        }
        else
        {
            r = mid;
        }
    }
    return l;
}

void expSearch(int *l, int *r, int N, int *arr)
{
    for (int i = 1; i < N; i *= 2)
    {
        *l = i / 2;
        *r = i;
        if (arr[*r] <= arr[*l])
        {
            break;
        }
        else
        {
            *r = N;
        }
    }
}

int solve(int *arr, int N)
{
    int l = 0, r = 1;
    expSearch(&l, &r, N, arr);
    return binsearch(l, r, arr);
}

int main()
{
    int N;
    std::cin >> N;
    int *arr = new int[N];
    for (int i = 0; i < N; i++)
    {
        std::cin >> arr[i];
    }
    std::cout << solve(arr, N) << std::endl;
    delete[] arr;
    return 0;
}