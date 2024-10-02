#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <iostream>

template<typename T>
class SinglyLinkedList {
public:
    // Constructor: Initialize an empty list
    SinglyLinkedList();

    // Destructor: Clean up memory
    ~SinglyLinkedList();

    // Insert a value at the end of the list
    void insert(const T& value);

    // Remove a node with the given value
    bool remove(const T& value);

    // Find a value in the list
    bool find(const T& value) const;

    // Print the list
    void print() const;

    void changeValue(int index, T newData);

    auto* getHead();

private:

    // Node structure for the singly linked list
    struct Node {
        T data;          // Data of the node
        Node* next;      // Pointer to the next node
        Node(const T& value) : data(value), next(nullptr) {}  // Constructor
    };
    Node* head;  // Pointer to the first node (head) of the list

    // Helper function to delete all nodes in the list
    void clear();
};

// Constructor
template<typename T>
SinglyLinkedList<T>::SinglyLinkedList() : head(nullptr) {}

// Destructor
template<typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    clear();  // Delete all nodes
}

// Helper function to delete all nodes
template<typename T>
void SinglyLinkedList<T>::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
}

// Insert a value at the end of the list
template<typename T>
void SinglyLinkedList<T>::insert(const T& value) {
    Node* newNode = new Node(value);
    if (head == nullptr) {
        head = newNode;  // List is empty, new node becomes the head
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;  // Append the new node at the end
    }
}

// Remove a node with the given value
template<typename T>
bool SinglyLinkedList<T>::remove(const T& value) {
    if (head == nullptr) {
        return false;  // List is empty
    }

    // Special case: removing the head
    if (head->data == value) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    // Search for the node to remove
    Node* current = head;
    while (current->next != nullptr && current->next->data != value) {
        current = current->next;
    }

    if (current->next == nullptr) {
        return false;  // Value not found
    }

    // Remove the node
    Node* temp = current->next;
    current->next = current->next->next;
    delete temp;
    return true;
}

// Find a value in the list
template<typename T>
bool SinglyLinkedList<T>::find(const T& value) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Print the list
template<typename T>
void SinglyLinkedList<T>::print() const {
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->data << " -> ";
        current = current->next;
    }
    std::cout << "null" << std::endl;
}

template<typename T>
auto* SinglyLinkedList<T>::getHead() {
    return this->head;
}

template<typename T>
void SinglyLinkedList<T>::changeValue(int index, T newData){
    Node* current = head;
    int counter = 0;
    while (current != nullptr) {
        if (counter == index) {
            current->data = newData;
        }
        current = current->next;
        ++counter;
    }
}

#endif // SINGLY_LINKED_LIST_H
