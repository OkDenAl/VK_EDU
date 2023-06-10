// A. Поиск позиции вставки

// Дан отсортированный по возрастанию массив попарно различных целых чисел
// A[0..n-1]. На вход также подается некоторое целое число k. Необходимо вернуть
// индекс элемента k в массиве A, если он там присутствует, либо вернуть
// позицию, куда его следовало бы вставить, чтобы массив остался
// отсортированным.

// Требование: сложность O(logN)

#include <iostream>

int binsearch(int l, int r, int *arr, int insElem) {
  while (r - l > 1) {
    int m = (r + l) / 2;
    if (arr[m] < insElem) {
      l = m;
    } else {
      r = m;
    }
  }
  return r;
}

int main() {
  int N = 0;
  std::cin >> N;
  int *arr = new int[N];
  for (int i = 0; i < N; i++) {
    std::cin >> arr[i];
  }
  int elem;
  std::cin >> elem;
  std::cout << binsearch(-1, N, arr, elem) << std::endl;
  return 0;
}