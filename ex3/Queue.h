#ifndef QUEUE
#define QUEUE

template<class T>
class Queue {

    class Node {
    
        friend class Queue<T>;
        T data;
        Node* next;
    
        Node(const T& givenData);
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
Queue<T>::Queue(const Queue<T>& queue) : {
    if(queue.m_size == 0) {
        m_head(nullptr);
        m_tail(m_head);
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
Queue<T>& Queue<T>::operator=(const Queue<T>& queue) {
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
        tempPointerOne->next = nullptr;
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
    m_tail = newNode;
    m_size++;
}

template<class T>
T& Queue<T>::front() {
    return m_head->data;
}

template<class T>
const T& Queue<T>::front() const {
    return m_head->data;
}

template<class T> 
void Queue<T>::popFront() {
    if(m_size == 0) {
        throw EmptyQueue();
    }
    Node* tempPoiter = m_head;
    m_head = m_head->next;
    delete tempPoiter;
    m_size--;
}

template<class T>
int Queue<T>::size() const {
    return m_size;
}

template<class T>
class Queue<T>::Iterator {

    Queue<T>* queue;
    Node* node;
    Iterator(const Queue<T>* queue, Node* node);
    friend class Queue<T>;

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
Queue<T>::Iterator::Iterator(const Queue<T>* queue, Node* node) : 
    queue(queue), node(node)
{}

template<class T>
bool Queue<T>::Iterator::operator==(const Iterator& iterator) const {
    if(*this == queue->end()) {
        throw InvalidOperation();
    }
    return node == iterator.node;
}

template<class T>
bool Queue<T>::Iterator::operator!=(const Iterator& iterator) const {
    if(*this == queue->end()) {
        throw InvalidOperation();
    }
    return !(*this == iterator);
}

template<class T>
Queue<T>::Iterator& Queue<T>::Iterator::operator++() {
    if(*this == queue->end()) {
        throw InvalidOperation();
    }
    node = node->next;
    return *this;
}

template<class T>
T& Queue<T>::Iterator::operator*() {
    if(*this == queue->end()) {
        throw InvalidOperation();
    }
    return node->data;
}

template<class T>
Queue<T>::Iterator Queue<T>::begin() {
    return Iterator(m_head);
}

template<class T>
Queue<T>::Iterator Queue<T>::end() {
    return Iterator(nullptr);
}

template<class T>
class Queue<T>::ConstIterator {

    const Node* node;
    ConstIterator(const Queue<T>* queue, const Node* node);
    friend class Queue<T>;

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
Queue<T>::ConstIterator::ConstIterator(const Queue<T>* queue, const Node* node) : 
    queue(queue), node(node)
{}

template<class T>
bool Queue<T>::ConstIterator::operator==(const ConstIterator& constIterator) const {
    if(*this == queue->end()) {
        throw InvalidOperation();
    }
    return node == constIterator.node;
}

template<class T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator& constIterator) const {
    if(*this == queue->end()) {
        throw InvalidOperation();
    }
    return !(*this == constIterator);
}

template<class T>
Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++() {
    if(*this == queue->end()) {
        throw InvalidOperation();
    }
    node = node->next;
    return *this;
}

template<class T>
const T& Queue<T>::ConstIterator::operator*() const {
    if(*this == queue->end()) {
        throw InvalidOperation();
    }
    return node->data;
}

template<class T>
Queue<T>::ConstIterator Queue<T>::begin() const {
    return ConstIterator(m_head);
}

template<class T>
Queue<T>::ConstIterator Queue<T>::end() const {
    return ConstIterator(nullptr);
}

template<class T, class Function>
Queue<T> filter(const Queue<T>& queue, Function function) {
    Queue<T> newQueue = new Queue<T>();
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