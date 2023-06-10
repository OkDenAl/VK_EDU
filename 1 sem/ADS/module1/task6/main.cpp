// 6.4
// Реализуйте стратегию выбора опорного элемента “случайный элемент”. 
// Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.

// Дано множество целых чисел из [0..109] размера n.
// Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:
// 10% перцентиль
// медиана
// 90% перцентиль

#include <iostream>

#define TEN_PERC 10
#define MEDIAN_PERC 50
#define NINETY_PERC 90


template <typename T, typename Comparator = std::less<T>>
int partition(T *arr, int l, int r, Comparator cmp = Comparator()) {
  int pivot = l+std::rand()%(r-l+1);
  int i = r, j = r;
  std::swap(arr[l], arr[pivot]);
  while (j != l) {
    if (cmp(arr[l],arr[j])) {
      std::swap(arr[j], arr[i]);
      i--;
      j--;
    } else {
      j--;
    }
  }
  std::swap(arr[j], arr[i]);
  return i;
}

template <typename T, typename Comparator = std::less<T>>
T findKthStatistic(T *arr, int l, int r, int targetInd,
                   Comparator cmp = Comparator()) {
  while (1) {
    int pivotInd = partition(arr, l, r);
    if (pivotInd == targetInd) {
      return arr[pivotInd];
    }
    if (pivotInd < targetInd) {
      l = pivotInd+1;
    } else {
      r = pivotInd-1;
    }
  }
}

int main() {
  int N;
  std::cin >> N;
  int *arr = new int[N];
  for (size_t i = 0; i < N; i++) {
    std::cin >> arr[i];
  }
  std::cout << findKthStatistic(arr, 0, N - 1, TEN_PERC * N / 100) << std::endl;
  std::cout << findKthStatistic(arr, 0, N - 1, MEDIAN_PERC * N / 100)
            << std::endl;
  std::cout << findKthStatistic(arr, 0, N - 1, NINETY_PERC * N / 100)
            << std::endl;
  delete[] arr;
}