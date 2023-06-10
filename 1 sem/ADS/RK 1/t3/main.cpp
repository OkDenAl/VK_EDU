// На склад привезли много пустых ящиков. Все ящики пронумерованы по порядку поступления от 0.
// Известно, что их все можно сложить один в один (то есть так, что каждый следующий помещается в предыдущий). Один ящик можно вложить в другой, если его можно перевернуть так, что размеры одного ящика по всем осям станут строго меньше размеров другого ящика по соответствующим осям.
// Требуется определить, в какой последовательности они будут вложены друг в друга. Вывести номера ящиков.
// Для сортировки точек реализуйте алгоритм сортировки вставками.
// Максимальное кол-во 10000.

#include <iostream>


struct Box {
  long long  x;
  long long  y;
  long long  z;
  int number;

  bool operator<(const Box &other) const;
};

bool Box::operator<(const Box &other) const {
  return x * y * z < other.x * other.y * other.z;
}

class BoxComparator {
 public:
  bool operator()(const Box &l, const Box &r);
};

bool BoxComparator::operator()(const Box &l, const Box &r) { return l < r; }

template <typename T, typename Comparator = BoxComparator>
void insertSort(T *arr, int n, Comparator cmp = Comparator()) {
  for (int i = 1; i < n; i++) {
    T tmp = arr[i];
    int j = i - 1;
    for (; j >= 0 && cmp(tmp, arr[j]); j--) {
      arr[j + 1] = arr[j];
    }
    arr[j + 1] = tmp;
  }
}

int main() {
  int N = 0;
  std::cin >> N;
  Box *arr = new Box[N];
  for (int i = 0; i < N; i++) {
    Box curBox;
    std::cin >> curBox.x >> curBox.y >> curBox.z;
    curBox.number = i;
    arr[i] = curBox;
  }
  insertSort(arr, N);
  for (int i = 0; i < N; i++) {
    std::cout << arr[i].number << " ";
  }
  std::cout << std::endl;

  delete[] arr;

  return 0;
}