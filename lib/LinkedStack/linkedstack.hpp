#ifndef LINKEDSTACK_HPP
#define LINKEDSTACK_HPP

#include <iostream>

template<typename T>
struct Node {
    T value;
    Node* next;
    Node* prev;
};

template<typename T>
class LinkedStack {
    friend std::ostream& operator<<(std::ostream& out, const LinkedStack<T>& linkedstack) {
        for (Node<T>* temp = linkedstack._top; temp != nullptr; temp = temp->next)
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
    LinkedStack() : _top(nullptr), _back(nullptr), undefined(T()), _size(0) {};
    LinkedStack(T undefined) : _top(nullptr), _back(nullptr), undefined(undefined), _size(0) {};

    //copy constructor
    LinkedStack(const LinkedStack& linkedstack) {
        copy(linkedstack);
    }
    
    //copy assignment operator
    LinkedStack& operator=(const LinkedStack& linkedstack) {
        if (this != &linkedstack) {
            this->~LinkedStack();
            this->copy(linkedstack);
        }
        return *this;
    }

    ~LinkedStack() {
        while (!empty()) {
            pop();
        }
    }

    void copy(const LinkedStack& linkedstack) {
        _top = linkedstack._top;
        _back = linkedstack._back;
        undefined = linkedstack.undefined;
        _size = 0;

        Node<T>* temp = linkedstack._back;
        while (temp != nullptr) {
            push(temp->value);
            temp = temp->prev;
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
            _top->prev = newNode;
            newNode->prev = nullptr;
            newNode->next = _top;
            _top = newNode;
        }
        _size++;
    }
};

#endif
