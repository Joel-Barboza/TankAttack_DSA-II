#ifndef PAIRED_PRIORITY_QUEUE_H
#define PAIRED_PRIORITY_QUEUE_H

#include <iostream>
#include <include/data_pair.h>

class PairedPriorityQueue {
public:
    PairedPriorityQueue() {
        front = nullptr;
        rear = nullptr;
        size = 0;
    }

    void enqueue(pairNode dataPair) {
        Node* newNode = new Node(dataPair);
        if (front == nullptr) {
            front = newNode;
            rear = newNode;
        } else if (dataPair.distance < front->distance) {
            newNode->next = front;
            front = newNode;
        } else {
            Node* current = front;
            while (current->next != nullptr && current->next->distance <= dataPair.distance) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
            if (newNode->next == nullptr) {
                rear = newNode;
            }
        }
        ++size;
    }

    void dequeue() {
        if (front == nullptr) {
            std::cout <<"Queue Underflow" << std::endl;
            return;
        } else {
            int element = front->nodeNum;
            front = front->next;
        }
        --size;
    }

    auto* getFront() {
        if (front != nullptr) {
            return front;
        }

        std::cout << "Queue Underflow" << std::endl;
        Node* nullPtr = nullptr;
        return nullPtr;
    }
    void printQueue() {
        Node* current = front;
        std::cout << "Priority Queue:\n";
        while (current != nullptr) {
            std::cout << "Node: " << current->nodeNum << ", Distance: " << current->distance << "\n";
            current = current->next;
        }
    }
    int size;
private:
    struct Node {
        int nodeNum;
        Node* next;
        int distance;

        Node(pairNode dataPair): nodeNum(dataPair.nodeIndex), next(nullptr), distance(dataPair.distance){}
    };
    Node* front;
    Node* rear;
};








#endif // PAIRED_PRIORITY_QUEUE_H
