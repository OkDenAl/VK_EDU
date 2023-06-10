// 3.1 Очередь с динамическим буфером
// Реализовать очередь с динамическим зацикленным буфером.
// Обрабатывать команды push back и pop front.


#include <iostream>

class Queue
{
private:
    int tail;
    int head;
    int size;
    int capacity;
    int *arr;

public:
    Queue();
    ~Queue();
    Queue(const Queue &other);

    void push(int a);
    int pop();
};

Queue::Queue()
    : head(0), tail(0), size(0), capacity(1)
{
    arr = new int[0];
}

Queue::~Queue()
{
    delete[] arr;
}

Queue::Queue(const Queue &other)
{
    arr = new int[other.capacity];
    for (int i = 0; i < other.capacity; i++)
    {
        arr[i] = other.arr[i];
    }
}

void Queue::push(int a)
{
    if (size == capacity)
    {
        int *newArr = new int[capacity * 2];
        for (int i = 0; i < tail; i++)
        {
            newArr[i] = arr[i];
        }
        for (int i = capacity - 1; i >= head; i--)
        {
            newArr[i + capacity] = arr[i];
        }
        delete[] arr;
        head += capacity;
        arr = newArr;
        capacity *= 2;
    }
    arr[tail++] = a;
    if (tail == capacity)
    {
        tail = 0;
    }
    size++;
}

int Queue::pop()
{
    if (size == 0)
    {
        return -1;
    }
    size--;
    int ans = arr[head++];
    if (head == capacity)
    {
        head = 0;
    }
    return ans;
}

int main()
{
    int N;
    std::cin >> N;
    Queue que;
    bool isCorrect = true;
    for (int i = 0; i < N; i++)
    {
        int a, b;
        std::cin >> a >> b;
        if (!isCorrect)
        {
            continue;
        }
        switch (a)
        {
        case 2:
            if (que.pop() != b)
            {
                isCorrect = false;
            }
            break;
        case 3:
            que.push(b);
            break;
        }
    }
    if (isCorrect)
    {
        std::cout << "YES";
    }
    else
    {
        std::cout << "NO";
    }
    return 0;
}
