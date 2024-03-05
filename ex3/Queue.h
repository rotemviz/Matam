#ifndef QUEUE
#define QUEUE

#include "Node.h"

template<class T>
class Queue {

    Node<T>* m_head;
    Node<T>* m_tail;
    int m_size;

public:
    Queue(const T& data);
    Queue();
    Queue(const Queue& queue) = default; //CHANG !!
    ~Queue();
    operator=(const Queue& queue) = default; //CHANG !!
    void pushBack(T data);
    T& front();
    void popFront();
    int size() const;

    class EmptyQueue{};
};

template<class T>
Queue<T>::Queue(const T& data) :
    m_head(new Node<T>(data)), m_tail(m_head), m_size(1)
{}

template<class T>
Queue<T>::Queue() :
    m_head(new Node<T>()), m_tail(m_head), m_size(0)
{}

template<class T>
Queue<T>::~Queue() {
    while(m_head != nullptr) {
        Node<T>* tempPointer = m_head;
        m_head = m_head->next;
        delete tempPointer;
    }
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
    if(!newNode) {
        throw std::bad_alloc();
    }
    m_tail->next = newNode;
    m_tail = newNode;
    m_size++;
}

template<class T>
T& Queue<T>::front() {
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



#endif