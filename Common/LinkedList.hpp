#pragma once
#include <exception>
#include <iostream>

namespace ds
{

template <typename T>
class Node
{
public:
    Node() : next(nullptr) {}
    Node(T value, Node* nextptr) : data(value), next(nextptr) {}

    T data;
    Node* next = nullptr;
};

template <typename T>
class LinkedList
{
public:
    LinkedList() : head(nullptr), tail(nullptr), _size(0) {}

    size_t size() const { return _size; }
    bool empty() const { return _size == 0; }

    Node<T>* begin() const { return head; }
    Node<T>* end() const { return tail; }
    Node<T>* locate(size_t pos) const;

    T& front() const;
    T& back() const;
    T& at(size_t pos) const;
    T& operator[](size_t pos) const;

    void push_back(T value);
    void insert(size_t pos, T value);
    void erase(size_t pos);

private:
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    size_t _size = 0;
};

template <typename T>
Node<T>* LinkedList<T>::locate(size_t pos) const
{
    try {
        if (pos >= _size) {  // range checking
            throw std::out_of_range("out of range");
        }
        Node<T>* elem = head;
        for (size_t i = 0; i < pos; i++) {
            elem = elem->next;
        }
        return elem;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "[ERROR] " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

template <typename T>
T& LinkedList<T>::front() const
{
    try {
        if (head == nullptr) {
            throw std::out_of_range("head is undefined");
        }
        return head->data;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "[ERROR] " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

template <typename T>
T& LinkedList<T>::back() const
{
    try {
        if (tail == nullptr) {
            throw std::out_of_range("tail is undefined");
        }
        return tail->data;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "[ERROR] " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

template <typename T>
T& LinkedList<T>::at(size_t pos) const
{
    try {
        if (pos >= _size) {  // range checking
            throw std::out_of_range("out of range");
        }
        return operator[](pos);
    }
    catch (const std::out_of_range& e) {
        std::cerr << "[ERROR] " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

template <typename T>
T& LinkedList<T>::operator[](size_t pos) const
{
    Node<T>* elem = head;
    for (size_t i = 0; i < pos; i++) {
        elem = elem->next;
    }
    return elem->data;
}

template <typename T>
void LinkedList<T>::push_back(T value)
{
    try {
        // Allocate memory and assign value
        Node<T>* newNode = new Node<T>(value, nullptr);
        // Handle list order
        if (tail == nullptr) {  // if list is empty
            head = newNode;
        }
        else {
            tail->next = newNode;
        }
        tail = newNode;
        _size++;
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "[ERROR] " << e.what() << std::endl;
    }
}

template <typename T>
void LinkedList<T>::insert(size_t pos, T value)
{
    try {
        if (pos >= _size) {  // range checking
            throw std::out_of_range("out of range");
        }

        // Allocate memory and assign value
        Node<T>* newNode = new Node<T>(value, nullptr);
        // Handle list order
        if (pos == 0) {
            if (_size == 0) {
                tail = newNode;
            }
            newNode->next = head;  // if size == 0, head == nullptr
            head = newNode;
        }
        else {
            Node<T>* prev = locate(pos - 1);
            newNode->next = prev->next;
            prev->next = newNode;
        }
        _size++;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "[ERROR] " << e.what() << std::endl;
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "[ERROR] " << e.what() << std::endl;
    }
}

template <typename T>
void LinkedList<T>::erase(size_t pos)
{
    try {
        if (pos >= _size) {  // range checking
            throw std::out_of_range("out of range");
        }
        if (pos == 0) {
            if (_size == 1) {
                tail = nullptr;
            }
            Node<T>* deleteNode = head;
            head = head->next;  // if size == 1, head->next == nullptr
            delete deleteNode;
        }
        else {
            Node<T>* prev = locate(pos - 1);
            Node<T>* deleteNode = prev->next;
            if (tail == deleteNode) {
                tail = prev;
            }
            prev->next = deleteNode->next;
            delete deleteNode;
        }
        _size--;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "[ERROR] " << e.what() << std::endl;
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "[ERROR] " << e.what() << std::endl;
    }
}

}  // namespace ds