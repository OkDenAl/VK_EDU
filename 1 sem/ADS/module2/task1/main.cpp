// 1. Хеш-таблица

// Реализуйте структуру данных типа “множество строк” на основе динамической
// хеш-таблицы с открытой адресацией.
//  Хранимые строки непустые и состоят из строчных латинских букв.
// Хеш-функция строки должна быть реализована с помощью вычисления значения
// многочлена методом Горнера.
//  Начальный размер таблицы должен быть равным 8-ми.
//  Перехеширование выполняйте при добавлении элементов в случае, когда
//  коэффициент заполнения таблицы достигает 3/4.
// Структура данных должна поддерживать операции добавления строки в множество,
//  удаления строки из множества и проверки принадлежности данной строки
//  множеству.
//
// Вариант 2. Для разрешения коллизий используйте двойное хеширование.

#include <iostream>
#include <string>
#include <vector>

const size_t DEFAULT_SIZE = 8;
const double MAX_ALPHA = 0.75;
const std::string DEL = "DEL";
const std::string NIL = "NIL";

class StringHasher {
 public:
  explicit StringHasher(size_t prime = 71);

  size_t operator()(const std::string &str) const;

 private:
  size_t prime_;
};

StringHasher::StringHasher(size_t prime) : prime_(prime) {}

size_t StringHasher::operator()(const std::string &str) const {
  size_t hash = 0;
  for (int i = 0; i < str.size(); i++) {
    hash = hash * prime_ + str[i];
  }
  return hash;
}

template <typename Hasher>
class HashTable {
 public:
  explicit HashTable(size_t initial_size = DEFAULT_SIZE);

  bool Has(const std::string &key);

  bool Add(const std::string &key);

  bool Delete(const std::string &key);

 private:
  void grow();

  std::vector<std::string> table_;
  Hasher hasher_;
  Hasher helpHasher_{101};
  size_t usedSize_;
};

template <typename Hasher>
HashTable<Hasher>::HashTable(size_t initial_size)
    : usedSize_(0), table_(initial_size, NIL) {}

template <typename Hasher>
bool HashTable<Hasher>::Has(const std::string &key) {
  for (int i = 0; i < table_.size(); i++) {
    size_t hash =
        (hasher_(key) + (2 * helpHasher_(key) + 1) * i) % table_.size();
    if (table_[hash] == NIL) {
      return false;
    }
    if (table_[hash] == key) {
      return true;
    }
  }
  return false;
}

template <typename Hasher>
bool HashTable<Hasher>::Add(const std::string &key) {
  if (usedSize_ != 0 &&
      static_cast<double>(usedSize_) / table_.size() >= MAX_ALPHA) {
    grow();
  }
  size_t firstDel = 0;
  bool fisrtDelIsSet = false;
  for (int i = 0; i < table_.size(); i++) {
    size_t hash =
        (hasher_(key) + (2 * helpHasher_(key) + 1) * i) % table_.size();
    if (table_[hash] == NIL) {
      table_[hash] = key;
      usedSize_++;
      return true;
    }
    if (table_[hash] == key) {
      return false;
    }
    if (!fisrtDelIsSet && table_[hash] == DEL) {
      fisrtDelIsSet = true;
      firstDel = hash;
    }
  }
  table_[firstDel] = key;
  usedSize_++;
  return true;
}

template <typename Hasher>
bool HashTable<Hasher>::Delete(const std::string &key) {
  for (int i = 0; i < table_.size(); i++) {
    size_t hash =
        (hasher_(key) + (2 * helpHasher_(key) + 1) * i) % table_.size();
    if (table_[hash] == NIL) {
      return false;
    }
    if (table_[hash] == key) {
      usedSize_--;
      table_[hash] = DEL;
      return true;
    }
  }
  return false;
}

template <typename Hasher>
void HashTable<Hasher>::grow() {
  std::vector<std::string> newTable(table_.size() * 2, NIL);
  for (int i = 0; i < table_.size(); i++) {
    if (table_[i] != DEL && table_[i] != NIL) {
      std::string key = table_[i];
      for (int j = 0; j < newTable.size(); j++) {
        size_t hash =
            (hasher_(key) + (2 * helpHasher_(key) + 1) * j) % newTable.size();
        if (newTable[hash] == NIL) {
          newTable[hash] = key;
          break;
        }
      }
    }
  }

  table_ = std::move(newTable);
}

int main() {
  HashTable<StringHasher> table{};

  char op;
  std::string key;

  while (std::cin >> op >> key) {
    switch (op) {
      case '?': {
        std::cout << (table.Has(key) ? "OK" : "FAIL") << std::endl;
        break;
      }
      case '+': {
        std::cout << (table.Add(key) ? "OK" : "FAIL") << std::endl;
        break;
      }
      case '-': {
        std::cout << (table.Delete(key) ? "OK" : "FAIL") << std::endl;
        break;
      }
      default: {
        return 0;
      }
    }
  }
  return 0;
}
