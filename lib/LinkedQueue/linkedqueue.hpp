#ifndef LINKEDQUEUE_HPP
#define LINKEDQUEUE_HPP

#include <iostream>

template<typename T>
struct Node {
    T value;
    Node* next;
    Node* prev;
};

template<typename T>
class LinkedQueue {
    friend std::ostream& operator<<(std::ostream& out, const LinkedQueue<T>& linkedqueue) {
        for (Node<T>* temp = linkedqueue._top; temp != nullptr; temp = temp->next)
            out << temp->value << "\n";
        return out;
    }

private:
    Node<T>* _top;
    Node<T>* _back;
    T undefined;
    int _size;

public:
    //default constructor
    LinkedQueue() : _top(nullptr), _back(nullptr), undefined(T()), _size(0) {};
    LinkedQueue(T undefined) : _top(nullptr), _back(nullptr), undefined(undefined), _size(0) {};

    //copy constructor
    LinkedQueue(const LinkedQueue& linkedqueue) {
        copy(linkedqueue);
    }
    
    //copy assignment operator
    LinkedQueue& operator=(const LinkedQueue& linkedqueue) {
        if (this != &linkedqueue) {
            this->~LinkedQueue();
            this->copy(linkedqueue);
        }
        return *this;
    }

    ~LinkedQueue() {
        while (!empty()) {
            pop();
        }
    }

    void copy(const LinkedQueue& linkedqueue) {
        _top = linkedqueue._top;
        _back = linkedqueue._back;
        undefined = linkedqueue.undefined;
        _size = 0;

        Node<T>* temp = linkedqueue._top;
        while (temp != nullptr) {
            push(temp->value);
            temp = temp->next;
        }
    }

    int empty() const {
        if (_size == 0)
            return 1;
        return 0;
    }

    int size() const {
        return _size;
    }

    T top() const {
        if (_size > 0)
            return _top->value;
        return undefined;
    }

    T back() const {
        if (_size > 0)
            return _back->value;
        return undefined;
    }

    T pop() {
        T value = undefined;
        if (_size == 1) {
            value = _top->value;
            delete _top;
            _top = _back = nullptr;
            _size--;
        }
        else if (_size > 1) {
            value = _top->value;
            Node<T>* newTop = _top->next;
            delete _top;
            _top = newTop;
            _top->prev = nullptr;
            _size--;
        }
        return value;
    }

    void push(T x) {
        Node<T>* newNode = new Node<T>;
        newNode->value = x;

        if (_size == 0) {
            newNode->prev = newNode->next = nullptr;
            _top = _back = newNode;
        }
        else if (_size > 0) {
            _back->next = newNode;
            newNode->prev = _back;
            newNode->next = nullptr;
            _back = newNode;
        }
        _size++;
    }
};

#endif
