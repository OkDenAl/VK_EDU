// 5.2 Современники

// Группа людей называется современниками если был такой момент, когда они могли
// собраться вместе. Для этого в этот момент каждому из них должно было уже
// исполниться 18 лет, но ещё не исполниться 80 лет. Дан список Жизни Великих
// Людей. Необходимо получить максимальное количество современников. В день
// 18летия человек уже может принимать участие в собраниях, а в день 80летия и в
// день смерти уже не может. Замечание. Человек мог не дожить до 18-летия, либо
// умереть в день 18-летия. В этих случаях принимать участие в собраниях он не
// мог.

#include <cstring>
#include <iostream>

#define BIRTH 1
#define DEATH -1

struct Date {
 public:
  Date() = default;
  explicit Date(int day, int month, int year);
  friend std::istream &operator>>(std::istream &in, Date &d);
  friend std::ostream &operator<<(std::ostream &out, Date &d);
  bool operator<(const Date &other) const;

  int day;
  int month;
  int year;
  int event;
  bool couldBeInMeeting;
};

Date::Date(int day, int month, int year) : day(day), month(month), year(year) {
  event = 0;
  couldBeInMeeting = false;
}

bool Date::operator<(const Date &other) const {
  if (year < other.year) {
    return true;
  } else if (year == other.year && month < other.month) {
    return true;
  } else if (year == other.year && month == other.month && day < other.day) {
    return true;
  }
  return false;
}

std::istream &operator>>(std::istream &in, Date &d) {
  in >> d.day >> d.month >> d.year;
  return in;
}

std::ostream &operator<<(std::ostream &out, Date &d) {
  out << d.day << " " << d.month << " " << d.year << " " << d.event << "\n";
  return out;
}

template <typename T>
class DateComparator {
 public:
  bool operator()(const T &l, const T &r) { return l < r; }
};

template <typename T, typename Comparator = DateComparator<T>>
void Merge(T *arr1, size_t firstLen, T *arr2, size_t secondLen, T *tmp,
           Comparator cmp) {
  int ind1 = 0, ind2 = 0, indTmp = 0;
  while (ind1 < firstLen && ind2 < secondLen) {
    if (cmp(arr2[ind2], arr1[ind1])) {
      tmp[indTmp] = arr2[ind2];
      ind2++;
    } else {
      tmp[indTmp] = arr1[ind1];
      ind1++;
    }
    indTmp++;
  }
  while (ind1 < firstLen) {
    tmp[indTmp] = arr1[ind1];
    ind1++;
    indTmp++;
  }
  while (ind2 < secondLen) {
    tmp[indTmp] = arr2[ind2];
    ind2++;
    indTmp++;
  }
}

template <typename T, typename Comparator = DateComparator<T>>
void MergeSort(T *arr, size_t arrLen, Comparator cmp = Comparator()) {
  if (arrLen <= 1) {
    return;
  }
  size_t firstLen = arrLen / 2;
  size_t secondLen = arrLen - firstLen;
  MergeSort(arr, firstLen);
  MergeSort(arr + firstLen, secondLen);
  T *tmp = new T[arrLen];
  Merge(arr, firstLen, arr + firstLen, secondLen, tmp, cmp);
  std::memcpy(arr, tmp, (sizeof(T) * arrLen));
  delete[] tmp;
}

int main() {
  int N;
  std::cin >> N;
  Date *dates = new Date[N * 2];
  for (int i = 0; i < N * 2; i += 2) {
    Date birth{}, death{};
    std::cin >> birth >> death;

    if (Date(birth.day, birth.month, birth.year + 80) < death) {
      death = Date(birth.day, birth.month, birth.year + 80);
    }

    if (Date(birth.day, birth.month, birth.year + 18) < death) {
      birth.couldBeInMeeting = death.couldBeInMeeting = true;
    } else {
      birth.couldBeInMeeting = death.couldBeInMeeting = false;
    }
    birth.year += 18;
    birth.event = BIRTH;
    death.event = DEATH;
    dates[i] = birth;
    dates[i + 1] = death;
  }

  MergeSort(dates, N * 2);
  int maxContemp = 0;
  int curContemp = 0;
  for (auto i = 0; i < N * 2; i++) {
    if (dates[i].couldBeInMeeting) {
      curContemp += dates[i].event;
      maxContemp = std::max(maxContemp, curContemp);
    }
  }
  std::cout << maxContemp << std::endl;
  delete[] dates;

  return 0;
}