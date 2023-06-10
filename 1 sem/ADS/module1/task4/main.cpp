// 4.1. Слияние массивов

// Напишите программу, которая использует кучу для слияния K отсортированных
// массивов суммарной длиной N.

// Требования:

// Время работы O(N * logK)
// Куча должна быть реализована в виде шаблонного класса.
// Решение должно поддерживать передачу функции сравнения снаружи.
// Куча должна быть динамической.

#include <iostream>

template <typename T, typename Comparator>
class Heap {
 public:
  explicit Heap(Comparator cmp);
  ~Heap();
  void insert(T &obj);
  T extract();
  bool empty();

 private:
  int specifySwapElemInd(const T &a, const T &b, int aInd, int bInd);
  T *arr;
  Comparator cmp;
  int capacity;
  int len;
};

template <typename T, typename Comparator>
Heap<T, Comparator>::Heap(Comparator cmp) : capacity(1), len(0), cmp(cmp) {
  arr = new T[capacity];
}

template <typename T, typename Comparator>
Heap<T, Comparator>::~Heap() {
  delete[] arr;
}

template <typename T, typename Comparator>
bool Heap<T, Comparator>::empty() {
  return len == 0;
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::insert(T &obj) {
  if (len == capacity) {
    capacity *= 2;
    T *newArr = new T[capacity];
    for (int i = 0; i < len; i++) {
      newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
  }
  int pos = len;
  arr[len++] = obj;
  while (pos > 0 && cmp(arr[(pos - 1) / 2], arr[pos])) {
    T tmp = arr[pos];
    arr[pos] = arr[(pos - 1) / 2];
    arr[(pos - 1) / 2] = tmp;
    pos = (pos - 1) / 2;
  }
}

template <typename T, typename Comparator>
int Heap<T, Comparator>::specifySwapElemInd(const T &a, const T &b, int aInd,
                                            int bInd) {
  if (cmp(a, b)) {
    return bInd;
  } else {
    return aInd;
  }
}

template <typename T, typename Comparator>
T Heap<T, Comparator>::extract() {
  T ans = arr[0];
  arr[0] = arr[len - 1];
  int pos = 0;
  while (pos * 2 + 2 < len) {
    int maxPos = specifySwapElemInd(arr[pos * 2 + 1], arr[pos * 2 + 2],
                                    pos * 2 + 1, pos * 2 + 2);
    if (cmp(arr[pos], arr[maxPos])) {
      T tmp = arr[pos];
      arr[pos] = arr[maxPos];
      arr[maxPos] = tmp;
      pos = maxPos;
    } else {
      break;
    }
  }
  len--;
  return ans;
}

struct ArrayIterator {
  int *array;
  int size;
  int curPos;
};

class ArrayComparator {
 public:
  bool operator()(const ArrayIterator &l, const ArrayIterator &r) {
    return l.array[l.curPos] > r.array[r.curPos];
  }
};

int main() {
  Heap<ArrayIterator, ArrayComparator> heap((ArrayComparator()));
  int K;
  std::cin >> K;
  int lenOfResArray = 0;
  for (int i = 0; i < K; i++) {
    int curArrSize;
    std::cin >> curArrSize;
    lenOfResArray += curArrSize;
    ArrayIterator curArr;
    curArr.size = curArrSize;
    curArr.curPos = 0;
    curArr.array = new int[curArrSize];

    for (int j = 0; j < curArrSize; j++) {
      std::cin >> curArr.array[j];
    }
    heap.insert(curArr);
  }
  int *res = new int[lenOfResArray];
  int ind = 0;
  while (!heap.empty()) {
    ArrayIterator arrFromHeap = heap.extract();
    res[ind] = (arrFromHeap.array[arrFromHeap.curPos]);
    arrFromHeap.curPos++;
    if (arrFromHeap.size != arrFromHeap.curPos) {
      heap.insert(arrFromHeap);
    } else {
      delete[] arrFromHeap.array;
    }
    ind++;
  }
  for (int i = 0; i < lenOfResArray; i++) {
    std::cout << res[i] << " ";
  }
  delete[] res;
  return 0;
}