//B. Стековые анаграммы

// ВНИМАНИЕ! Для решения данной задачи нужно использовать структуру данных стек!

// Пара слов называется стековой анаграмой, если одно слово можно получить из другого, 
// проведя последовательность стековых операций с его буквами 
// (взять очередную букву исходного слова и поместить ее в стек; взять букву из стека и добавить ее в конец выходного слова). 
// Для заданной пары слов требуется определить, можно ли выполнить последовательность стековых операций, переводящую первое слово во второе. 
// Все буквы в слове различные. Длина анаграммы ≤ 10000.

#include <iostream>

class Stack {
 private:
  int capacity;
  int size;
  int head;
  char *arr;

 public:
  Stack();
  ~Stack();
  void push(char letter);
  char pop();
  char back();
  bool empty();
};

Stack::Stack() {
  size = 0;
  head = 0;
  capacity = 1;
  arr = new char[capacity];
}

Stack::~Stack() { delete[] arr; }

void Stack::push(char letter) {
  if (size == capacity) {
    capacity *= 2;
    char *newArr = new char[capacity];
    for (int i = 0; i < size; i++) {
      newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
  }
  arr[head] = letter;
  head++;
  size++;
}

char Stack::pop() {
  size--;
  head--;
  return arr[head];
}

char Stack::back() { return arr[head - 1]; }

bool Stack::empty() { return size == 0; }

int main() {
  std::string input, expect;
  std::cin >> input >> expect;
  Stack stack{};
  int j = 0;
  for (int i = 0; i < input.length(); i++) {
    stack.push(input[i]);
    while (j < expect.length() && stack.back() == expect[j]) {
      stack.pop();
      j++;
    }
  }
  if (stack.empty()) {
    std::cout << "YES" << std::endl;
  } else {
    std::cout << "NO" << std::endl;
  }
  return 0;
}