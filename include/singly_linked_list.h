#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <iostream>

template<typename T>
class SinglyLinkedList {
public:

    SinglyLinkedList();


    ~SinglyLinkedList();


    void insert(const T& value);

    void insertFirst(const T& value);


    bool remove(const T& value);


    bool find(const T& value) const;


    void print() const;

    void changeValue(int index, T newData);

    auto* getHead();

    T getValue(int nodeIndex);

    int getSize();
    void clear();
private:


    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };
    Node* head = nullptr;

    int size = 0;

};

template<typename T>
SinglyLinkedList<T>::SinglyLinkedList() : head(nullptr) {}

template<typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    clear();
}

template<typename T>
void SinglyLinkedList<T>::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
    this->size = 0;
}

template<typename T>
void SinglyLinkedList<T>::insert(const T& value) {
    Node* newNode = new Node(value);
    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    ++this->size;
}

template<typename T>
void SinglyLinkedList<T>::insertFirst(const T &value)
{
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
    ++this->size;
}

template<typename T>
bool SinglyLinkedList<T>::remove(const T& value) {
    if (head == nullptr) {
        return false;
    }

    if (head->data == value) {
        Node* temp = head;
        head = head->next;
        delete temp;
        --this->size;
        return true;
    }

    Node* current = head;
    while (current->next != nullptr && current->next->data != value) {
        current = current->next;
    }

    if (current->next == nullptr) {
        return false;
    }

    Node* temp = current->next;
    current->next = current->next->next;
    delete temp;
    --this->size;
    return true;
}

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
            return;
        }
        current = current->next;
        ++counter;
    }
}

template<typename T>
T SinglyLinkedList<T>::getValue(int nodeIndex) {
    Node* current = head;
    int counter = 0;
    while (current->next != nullptr && counter < nodeIndex) {
        current = current->next;
        ++counter;
    }
    return current->data;

}

template<typename T>
int SinglyLinkedList<T>::getSize() {
    return this->size;
}

#endif // SINGLY_LINKED_LIST_H
