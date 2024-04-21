#ifndef LISTTYPE_H
#define LISTTYPE_H

#include <iostream>

// Node structure to represent a node in the linked list
template <typename T>
struct nodeType {
    T info;
    nodeType<T>* next;
};

// Templated class to represent a linked list
template <typename T>
class listType {
protected:
    nodeType<T>* head;
    int length;

public:
    listType() {
        head = nullptr;
        length = 0;
    }

    ~listType() {
        nodeType<T>* temp;
        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool isEmpty() const {
        return (head == nullptr);
    }

    int lengthIs() const {
        return length;
    }

    void print() const {
        nodeType<T>* temp = head;
        while (temp != nullptr) {
            std::cout << temp->info << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    void insertFirst(const T& newItem) {
        nodeType<T>* newNode = new nodeType<T>;
        newNode->info = newItem;
        newNode->next = head;
        head = newNode;
        length++;
    }

    void insertLast(const T& newItem) {
        nodeType<T>* newNode = new nodeType<T>;
        newNode->info = newItem;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
        }
        else {
            nodeType<T>* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        length++;
    }

    void deleteNode(const T& deleteItem) {
        nodeType<T>* current = head;
        nodeType<T>* trailCurrent = nullptr;

        while (current != nullptr) {
            if (current->info == deleteItem) {
                break;
            }
            trailCurrent = current;
            current = current->next;
        }

        if (current == nullptr) {
            std::cout << "Item not found in the list." << std::endl;
        }
        else {
            if (trailCurrent == nullptr) {
                head = head->next;
            }
            else {
                trailCurrent->next = current->next;
            }
            delete current;
            length--;
        }
    }

    const listType<T>& operator=(const listType<T>& otherList) {
        if (this != &otherList) {
            while (head != nullptr) {
                nodeType<T>* temp = head;
                head = head->next;
                delete temp;
            }
            length = 0;

            nodeType<T>* current = otherList.head;
            while (current != nullptr) {
                insertLast(current->info);
                current = current->next;
            }
        }
        return *this;
    }
};

#endif