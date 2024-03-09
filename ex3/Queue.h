#ifndef QUEUE
#define QUEUE

template<class T>
class Queue {

    class Node {
    
        friend class Queue;
        T data;
        Node* next;
    
        Node(const T& givenData);
        Node(const Node& node) = delete;
        Node& operator=(const Node& node) = delete;
        ~Node() = default;
    };

    Node* m_head;
    Node* m_tail;
    int m_size;

public:
    Queue();
    Queue(const Queue& queue);
    ~Queue();
    Queue& operator=(const Queue& queue);
    void pushBack(const T& data);
    T& front();
    const T& front() const;
    void popFront();
    int size() const;

    class Iterator;
    Iterator begin();
    Iterator end();

    class ConstIterator;
    ConstIterator begin() const;
    ConstIterator end() const;

    class EmptyQueue{};
};

template<class T>
Queue<T>::Node::Node(const T& givenData) : 
    data(givenData), next(nullptr)
{}

template<class T>
Queue<T>::Queue() :
    m_head(nullptr), m_tail(m_head), m_size(0)
{}

template<class T>
Queue<T>::Queue(const Queue& queue) : 
    m_head(nullptr), m_tail(m_head), m_size(0)
{
    if(queue.m_size == 0) {
        m_head = nullptr;
        m_tail = m_head;
        m_size = 0;
    }
    else {
        m_head = new Node(queue.m_head->data);
        Node* tempPointerOne = m_head;
        Node* tempPointerTwo = queue.m_head->next;
        try {
            while (tempPointerTwo != nullptr) {
                tempPointerOne->next = new Node(tempPointerTwo->data);
                tempPointerOne = tempPointerOne->next;
                tempPointerTwo = tempPointerTwo->next;
            }
            m_tail = tempPointerOne;
            m_size = queue.m_size;
        }
        catch(const std::bad_alloc&) {
            while(m_head != nullptr) {
                Node* nodeToRemove = m_head;
                m_head = m_head->next;
                delete nodeToRemove;
            }
            throw;
        }
    }
}

template<class T>
Queue<T>::~Queue() {
    while(m_head != nullptr) {
        Node* tempPointer = m_head;
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
    Node* headHolder = new Node(queue.m_head->data);
    Node* tempPointerOne = headHolder;
    Node* tempPointerTwo = queue.m_head->next;
    try {
        while(tempPointerTwo != nullptr) {
            Node* newNode = new Node(tempPointerTwo->data);
            tempPointerOne->next = newNode;
            tempPointerOne = tempPointerOne->next;
            tempPointerTwo = tempPointerTwo->next;
        }
        Node* tailHolder = tempPointerOne;
        tempPointerOne = m_head;
        while(tempPointerOne != nullptr) {
            tempPointerTwo = m_head->next;
            delete tempPointerOne;
            tempPointerOne = tempPointerTwo;
        }
        m_head = headHolder;
        m_tail = tailHolder;
        m_size = queue.m_size;
    }
    catch(const std::bad_alloc&) {
        while(headHolder != nullptr) {
            tempPointerOne = headHolder->next;
            delete headHolder;
            headHolder = tempPointerOne;
        }
        throw;
    }
    return *this;
}

template<class T>
void Queue<T>::pushBack(const T& data) {
    if(m_size == 0) {
        Node* newNode = new Node(data);
        m_tail = newNode;
        m_head = m_tail;
        m_size++;
        return;
    }
    Node* newNode = new Node(data);
    m_tail->next = newNode;
    m_tail = m_tail->next;
    m_size++;
}

template<class T>
T& Queue<T>::front() {
    if(m_size == 0) {
        throw EmptyQueue();
    }
    return m_head->data;
}

template<class T>
const T& Queue<T>::front() const {
    if(m_size == 0) {
        throw EmptyQueue();
    }
    return m_head->data;
}

template<class T> 
void Queue<T>::popFront() {
    if(m_size == 0) {
        throw EmptyQueue();
    }
    Node* tempPointer = m_head;
    m_head = m_head->next;
    delete tempPointer;
    m_size--;
}

template<class T>
int Queue<T>::size() const {
    return m_size;
}

template<class T>
class Queue<T>::Iterator {

    Queue* m_queue;
    Node* m_node;
    Iterator(Queue* queue, Node* node);
    friend class Queue;

public:
    bool operator==(const Iterator& iterator) const;
    bool operator!=(const Iterator& iterator) const;
    Iterator& operator++();
    T& operator*();

    ~Iterator() = default;
    Iterator(const Iterator& iterator) = default;
    Iterator& operator=(const Iterator& iterator) = default;

    class InvalidOperation{};
};

template<class T>
Queue<T>::Iterator::Iterator(Queue* queue, Node* node) : 
    m_queue(queue), m_node(node)
{}

template<class T>
bool Queue<T>::Iterator::operator==(const Iterator& iterator) const {
    return m_node == iterator.m_node;
}

template<class T>
bool Queue<T>::Iterator::operator!=(const Iterator& iterator) const { 
    return !(*this == iterator);
}

template<class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++() {
    if(*this == m_queue->end()) {
        throw InvalidOperation();
    }
    m_node = m_node->next;
    return *this;
}

template<class T>
T& Queue<T>::Iterator::operator*() {
    if(*this == m_queue->end()) {
        throw InvalidOperation();
    }
    return m_node->data;
}

template<class T>
typename Queue<T>::Iterator Queue<T>::begin() {
    return Iterator(this, m_head);
}

template<class T>
typename Queue<T>::Iterator Queue<T>::end() {
    return Iterator(this, nullptr);
}

template<class T>
class Queue<T>::ConstIterator {

    const Queue* m_queue;
    const Node* m_node;
    ConstIterator(const Queue* m_queue, const Node* node);
    friend class Queue;

public:
    bool operator==(const ConstIterator& iterator) const;
    bool operator!=(const ConstIterator& iterator) const;
    ConstIterator& operator++();
    const T& operator*() const;

    ~ConstIterator() = default;
    ConstIterator(const ConstIterator& constIterator) = default;
    ConstIterator& operator=(const ConstIterator& constIterator) = default;

    class InvalidOperation{};
};

template<class T>
Queue<T>::ConstIterator::ConstIterator(const Queue* queue, const Node* node) : 
    m_queue(queue), m_node(node)
{}

template<class T>
bool Queue<T>::ConstIterator::operator==(const ConstIterator& constIterator) const {
    return m_node == constIterator.m_node;
}

template<class T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator& constIterator) const {
    return !(*this == constIterator);
}

template<class T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++() {
    if(*this == m_queue->end()) {
        throw InvalidOperation();
    }
    m_node = m_node->next;
    return *this;
}

template<class T>
const T& Queue<T>::ConstIterator::operator*() const {
    if(*this == m_queue->end()) {
        throw InvalidOperation();
    }
    return m_node->data;
}

template<class T>
typename Queue<T>::ConstIterator Queue<T>::begin() const {
    return ConstIterator(this ,m_head);
}

template<class T>
typename Queue<T>::ConstIterator Queue<T>::end() const {
    return ConstIterator(this, nullptr);
}

template<class T, class Function>
Queue<T> filter(const Queue<T>& queue, Function function) {
    Queue<T> newQueue;
    for(typename Queue<T>::ConstIterator it = queue.begin(); it != queue.end(); ++it) {
        if(function(*it)) {
            newQueue.pushBack(*it);
        }
    }
    return newQueue;
}

template<class T, class Function>
void transform(Queue<T>& queue, Function function) {
    for(typename Queue<T>::Iterator it = queue.begin(); it != queue.end(); ++it) {
        *it = function(*it);
    }
}

template<class T, class Function>
T reduce(const Queue<T>& queue, const T& value, Function function) {
    T producedValue = value;
    for(typename Queue<T>::ConstIterator it = queue.begin(); it != queue.end(); ++it) {
        producedValue = function(*it, producedValue);
    }
    return producedValue;
}

#endif