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
            return;
        }

        rear->next = new_node;
        rear = new_node;
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
private:
    struct Node
    {
        T data;
        Node* next;
        Node(int new_data): data(new_data), next(nullptr){}
    };
    Node* front;
    Node* rear;
};


#endif // QUEUE_H
