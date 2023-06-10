// 7.2. LSD для long long

// Дан массив неотрицательных целых 64-битных чисел. Количество чисел не больше
// 1000000. Отсортировать массив методом поразрядной сортировки LSD по байтам.

#include <iostream>

#define ull unsigned long long
#define BYTES_COUNT 8
#define ALPHABET_POWER 255

void radixSort(ull *arr, int n) {
  for (int i = 0; i < BYTES_COUNT; i++) {
    int *alphabet = new int[ALPHABET_POWER + 1]();
    for (int j = 0; j < n; j++) {
      auto curByte = (arr[j] >> (8 * i)) & 255;
      alphabet[curByte]++;
    }
    for (int j = 1; j <= ALPHABET_POWER; j++) {
      alphabet[j] += alphabet[j - 1];
    }
    ull *tmpBuf = new ull[n]();
    for (int j = n - 1; j >= 0; j--) {
      auto pos = (arr[j] >> (8 * i)) & 255;
      alphabet[pos]--;
      tmpBuf[alphabet[pos]] = arr[j];
    }
    for (int j = 0; j < n; j++) {
      arr[j] = tmpBuf[j];
    }
    delete[] tmpBuf;
    delete[] alphabet;
  }
}

int main() {
  int n = 0;
  std::cin >> n;
  ull *arr = new ull[n];
  for (int i = 0; i < n; i++) {
    std::cin >> arr[i];
  }
  radixSort(arr, n);
  for (int i = 0; i < n; i++) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
  delete[] arr;
}