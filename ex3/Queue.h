#ifndef QUEUE
#define QUEUE

#include "Node.h"

template<class T>
class Queue {

    Node<T>* m_head;
    Node<T>* m_tail;
    int m_size;

public:
    Queue();
    Queue(const Queue& queue);
    ~Queue();
    Queue& operator=(const Queue& queue);
    void pushBack(T data);
    T& front() const;
    void popFront();
    int size() const;

    class Iterator;
    Iterator begin() const;
    Iterator end() const;

    class EmptyQueue{};
};

template<class T>
Queue<T>::Queue() :
    m_head(nullptr), m_tail(m_head), m_size(0)
{}

template<class T>
Queue<T>::Queue(const Queue& queue) : {
    if(queue.m_size == 0) {
        m_head(nullptr);
        m_tail(m_head);
        m_size = 0;
    }
    else {
        m_head = new Node<T>(queue.m_head->data);
        m_size = 1;
        Node<T>* tempPointerOne = m_head;
        Node<T>* tempPointerTwo = queue.m_head->next;
        while (tempPointerTwo != nullptr) {
            try {
                tempPointerOne->next = new Node<T>(tempPointerTwo->data);
            }
            catch(const std::bad_alloc&) {
                while(m_head != nullptr) {
                    Node<T>* nodeToRemove = m_head;
                    m_head = m_head->next;
                    delete nodeToRemove;
                }
            }
            m_size++;
            tempPointerOne = tempPointerOne->next;
            tempPointerTwo = tempPointerTwo->next;
        }
        m_tail = tempPointerOne;
    }
}

template<class T>
Queue<T>::~Queue() {
    while(m_head != nullptr) {
        Node<T>* tempPointer = m_head;
        m_head = m_head->next;
        delete tempPointer;
    }
}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue& queue) {
    if(queue.m_size == 0) {
        m_head = nullptr;
        m_tail = m_head;
        m_size = queue.m_size;
        return *this;
    }
    Node<T>* headHolder = new Node<T>(queue.m_head->data);
    Node<T>* tempPointerOne = headHolder;
    Node<T>* tempPointerTwo = queue.m_head->next;
    try {
        while(tempPointerTwo != nullptr) {
            Node<T>* newNode = new Node<T>(tempPointerTwo->data);
            tempPointerOne->next = newNode;
            tempPointerOne = tempPointerOne->next;
            tempPointerTwo = tempPointerTwo->next;
        }
        Node<T>* tailHolder = tempPointerOne;
        Node<T>* tempPointerOne = m_head;
        while(tempPointerOne != nullptr) {
            Node<T>* tempPointerTwo = m_head->next;
            delete tempPointerOne;
            tempPointerOne = tempPointerTwo;
        }
        m_head = headHolder;
        m_tail = tailHolder;
    }
    catch(const std::bad_alloc&) {
        while(headHolder != nullptr) {
            tempPointerOne = headHolder->next;
            delete headHolder;
            headHolder = tempPointerOne;
        }
    }
    return *this;
}

template<class T>
void Queue<T>::pushBack(T data) {
    if(m_size == 0) {
        m_tail->data = data;
        m_head = m_tail;
        m_size++;
        return;
    }
    Node<T>* newNode = new List<T>(data);
    m_tail->next = newNode;
    m_tail = newNode;
    m_size++;
}

template<class T>
T& Queue<T>::front() const {
    return m_head->data;
}

template<class T> 
void Queue<T>::popFront() {
    if(m_size == 0) {
        throw EmptyQueue();
    }
    Node<T>* tempPoiter = m_head;
    m_head = m_head->next;
    delete tempPoiter;
    m_size--;
}

template<class T>
int Queue<T>::size() const {
    return size;
}

template<class T>
class Queue<T>::Iterator {

    const Queue<T>* queue;
    Node<T>* node;
    Iterator(const Queue<T>* queue, Node<T>* node);
    friend class Queue<T>;

public:
    bool operator==(const Iterator& iterator) const;
    bool operator!=(const Iterator& iterator) const;
    Iterator& operator++();
    const T& operator*() const;

    Iterator(const Iterator& iterator) = default;
};

template<class T>
Queue<T>::Iterator::Iterator(const Queue<T>* queue, Node<T>* node) : 
    queue(queue), node(node)
{}

template<class T>
Queue<T>::Iterator Queue<T>::begin() const {
    return Iterator(this, m_head);
}

template<class T>
Queue<T>::Iterator Queue<T>::end() const {
    return Iterator(this, nullptr);
}

template<class T>
bool Queue<T>::Iterator::operator==(const Iterator& iterator) const {
    return node == iterator.node;
}

template<class T>
bool Queue<T>::Iterator::operator!=(const Iterator& iterator) const {
    return !(*this == iterator);
}

template<class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++() {
    if(node != nullptr) { //CHECK IF NECCESSERY
        node = node->next;
    }
    return *this;
}

template<class T>
const T& Queue<T>::Iterator::operator*() const {
    return node->data;
}

#endif