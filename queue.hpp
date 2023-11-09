#include <vector>
#include <cassert>
#include <stdio.h>

template <typename T, int Size>
struct Queue {
    std::vector<T> data;
    int top, tail;

    Queue() {
        top = 0;
        tail = -1;
    }

    bool isEmpty() {
        return (tail == -1);
    }

    bool isFull() {
        return (tail == Size - 1);
    }

    void enqueue(const T& item) {
        if (isFull()) {
            printf("Queue is full. Cannot enqueue.");
            return;
        }
        data.push_back(item);
        tail = data.size() - 1;
    }

    T dequeue() {
        if (isEmpty()) {
            printf("Queue is empty. Cannot dequeue.");
            return T(); // Return a default-constructed T
        }
        T item = data[top];
        top++;
        return item;
    }
};

template <typename T, int Size>
Queue<T, Size> createQueue() {
    return Queue<T, Size>();
}
