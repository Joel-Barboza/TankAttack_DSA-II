#ifndef QUEUE_H
#define QUEUE_H

#include <climits>
#include <iostream>

template<typename T>
class Queue {
public:
    Queue() { front = rear = nullptr; }

    bool isEmpty()
    {
        if (front == nullptr) {
            return true;
        }
        return false;
    }

    void enqueue(T new_data) {

        Node* new_node = new Node(new_data);

        if (this->isEmpty()) {
            front = rear = new_node;
            ++size;
            return;
        }

        rear->next = new_node;
        rear = new_node;
        ++size;
    }

    void dequeue() {

        if (this->isEmpty()) {
            std::cout << "Queue Underflow\n";
            return;
        }

        Node* temp = front;
        front = front->next;

        if (front == nullptr)
            rear = nullptr;

        delete temp;
        --size;
    }

    T getFront() {

        if (this->isEmpty()) {
            std::cout << "Queue is empty\n";
            return INT_MIN;
        }
        return front->data;
    }

    T getRear() {

        if (this->isEmpty()) {
            std::cout << "Queue is empty\n";
            return INT_MIN;
        }

        return rear->data;
    }

    int getSize() {
        return size;
    }
private:
    struct Node
    {
        T data;
        Node* next;
        Node(T new_data): data(new_data), next(nullptr){}
    };
    Node* front;
    Node* rear;
    int size = 0;
};


#endif // QUEUE_H
