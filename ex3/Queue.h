#ifndef QUEUE
#define QUEUE

template<class T>
class Queue {

    class Node {
    
        friend class Queue;
        T m_data;
        Node* m_next;

        Node(const T& givenData);
        Node(const Node& node) = delete;
        Node& operator=(const Node& node) = delete;
        ~Node() = default;
    };

    Node* m_head;
    Node* m_tail;
    int m_size;
    static const int EMPTY_QUEUE_SIZE = 0;

public:
    /*
     * C'tor of Queue class
     *
     * @return
     *      A new instance of Queue.
    */
    Queue();

    /*
     * Copy constructor of Queue class
     *
     * @param name - The Queue to be copy.
     * @return
     *      A new instance of Queue.
    */
    Queue(const Queue& queue);

    /*
     * Destructor of Queue class
    */
    ~Queue();

    /*
     * Assignment operator of Queue class:
     *
     * @param queue - The Queue that is assign
     * @return
     *      A reference to the assign Queue
    */
    Queue& operator=(const Queue& queue);

    /*
     * Adds a new element to the queue, at the end of the queue:
     *
     * @param data - the new element to be added
     * @return
     *      void
    */
    void pushBack(const T& data);

    /*
     * Returns the first element of the queue:
     *
     * @return
     *      The first element of the queue
    */
    T& front();

    /*
     * Returns the first element of the const queue:
     *
     * @return
     *      The first element of the const queue
    */
    const T& front() const;

    /*
     * Removes the first element of the queue:
     *
     * @return
     *      void
    */
    void popFront();

    /*
     * Returns the size of the queue:
     *
     * @return
     *      The size of the queue
    */
    int size() const;

    /*
     * Class Iterator to go through the elements of the Queue
    */
    class Iterator;

    /*
     * Returns an iterator to the first element of the queue:
     *
     * @return
     *      Iterator to the first element of the queue
    */
    Iterator begin();

    /*
     * Returns an iterator to the end of the queue:
     *
     * @return
     *      Iterator to the end of the queue
    */
    Iterator end();

    /*
     * Class ConstIterator to go through the elements of the const Queue
    */
    class ConstIterator;

    /*
     * Returns an iterator to the first element of the const queue:
     *
     * @return
     *      Iterator to the first element of the const queue
    */
    ConstIterator begin() const;

    /*
     * Returns an iterator to end of the const queue:
     *
     * @return
     *      Iterator to the end of the const queue
    */
    ConstIterator end() const;

    /*
     * Class EmptyQueue to use as exception to indicate an empty Queue
    */
    class EmptyQueue{};
};

template<class T>
class Queue<T>::Iterator {

    Queue* m_queue;
    Node* m_node;
    Iterator(Queue<T>* queue, Node* node);
    friend class Queue;

public:

    /*
    * Checks if the given iterator is equal to the current iterator:
    * 
    * @param healthPointsOne - The given iterator.
    * @return
    *      True if the given iterator is equal to current iterator
    *      False otherwise
    */
    bool operator==(const Iterator& iterator) const;

    /*
    * Checks if the given iterator is not equal to the current iterator:
    * 
    * @param healthPointsOne - The given iterator.
    * @return
    *      True if the given iterator is not equal to current iterator
    *      False otherwise
    */
    bool operator!=(const Iterator& iterator) const;

    /*
    * Promotes the iterator to the next element of the queue:
    * 
    * @return
    *      A reference to the iterator
    */
    Iterator& operator++();

    /*
    * Returns the current element which the iterator is pointing to:
    * 
    * @return
    *      A reference to the element of the queue which the iterator is pointing to
    */
    T& operator*();

    /*
     * Explicitly telling the compiler to use the defualt methods of destructor, copy constuctor, and operator=
    */
    ~Iterator() = default;
    Iterator(const Iterator& iterator) = default;
    Iterator& operator=(const Iterator& iterator) = default;

    /*
     * Class InvalidOperation to use as exception to indicate an invalid operation
    */
    class InvalidOperation{};
};

template<class T>
class Queue<T>::ConstIterator {

    const Queue* m_queue;
    const Node* m_node;
    ConstIterator(const Queue<T>* m_queue, const Node* node);
    friend class Queue;

public:
    /*
    * Checks if the given ConstIterator is equal to the current ConstIterator:
    * 
    * @param healthPointsOne - The given ConstIterator.
    * @return
    *      True if the given ConstIterator is equal to current ConstIterator
    *      False otherwise
    */
    bool operator==(const ConstIterator& iterator) const;

    /*
    * Checks if the given ConstIterator is not equal to the current ConstIterator:
    * 
    * @param healthPointsOne - The given ConstIterator.
    * @return
    *      True if the given ConstIterator is not equal to current ConstIterator
    *      False otherwise
    */
    bool operator!=(const ConstIterator& iterator) const;

    /*
    * Promotes the iterator to the next element of the const queue:
    * 
    * @return
    *      A reference to the iterator
    */
    ConstIterator& operator++();

    /*
    * Returns the current element which the ConstIterator is pointing to:
    * 
    * @return
    *      A reference to the element of the const queue which the ConstIterator is pointing to
    */
    const T& operator*() const;

    /*
     * Explicitly telling the compiler to use the defualt methods of destructor, copy constuctor, and operator=
    */
    ~ConstIterator() = default;
    ConstIterator(const ConstIterator& constIterator) = default;
    ConstIterator& operator=(const ConstIterator& constIterator) = default;

    /*
     * Class InvalidOperation to use as exception to indicate an invalid operation
    */
    class InvalidOperation{};
};

template<class T>
Queue<T>::Node::Node(const T& givenData) : 
    m_data(givenData), m_next(nullptr)
{}

template<class T>
Queue<T>::Queue() :
    m_head(nullptr), m_tail(nullptr), m_size(EMPTY_QUEUE_SIZE)
{}

template<class T>
Queue<T>::Queue(const Queue& queue) : 
    m_head(nullptr), m_tail(nullptr), m_size(EMPTY_QUEUE_SIZE)
{
    if(queue.m_size > EMPTY_QUEUE_SIZE) {
        Node* tempPointer = queue.m_head;
        try {
            while (tempPointer != nullptr) {
                this->pushBack(tempPointer->m_data);
                tempPointer = tempPointer->m_next;
            }
        }
        catch(const std::bad_alloc&) {
            while(m_head != nullptr) {
                this->popFront();
            }
            throw;
        }
    }
}

template<class T>
Queue<T>::~Queue() {
    while(m_head != nullptr) {
        this->popFront();
    }
}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue& queue) {
    if(this == &queue) {
        return *this;
    }
    if(queue.m_size == EMPTY_QUEUE_SIZE) {
        m_head = nullptr;
        m_tail = nullptr;
        m_size = queue.m_size;
        return *this;
    }
    Queue tempQueue;
    Node* tempPointer = queue.m_head;
    while(tempPointer != nullptr) {
        tempQueue.pushBack(tempPointer->m_data);
        tempPointer = tempPointer->m_next;
    }
    while(m_head != nullptr) {
        this->popFront();
    }
    m_head = tempQueue.m_head;
    m_tail = tempQueue.m_tail;
    m_size = tempQueue.m_size;
    tempQueue.m_head = nullptr;
    return *this;
}

template<class T>
void Queue<T>::pushBack(const T& data) {
    if(m_size == EMPTY_QUEUE_SIZE) {
        Node* newNode = new Node(data);
        m_tail = newNode;
        m_head = m_tail;
        m_size++;
        return;
    }
    Node* newNode = new Node(data);
    m_tail->m_next = newNode;
    m_tail = m_tail->m_next;
    m_size++;
}

template<class T>
T& Queue<T>::front() {
    if(m_size == EMPTY_QUEUE_SIZE) {
        throw EmptyQueue();
    }
    return m_head->m_data;
}

template<class T>
const T& Queue<T>::front() const {
    if(m_size == EMPTY_QUEUE_SIZE) {
        throw EmptyQueue();
    }
    return m_head->m_data;
}

template<class T> 
void Queue<T>::popFront() {
    if(m_size == EMPTY_QUEUE_SIZE) {
        throw EmptyQueue();
    }
    Node* tempPointer = m_head;
    m_head = m_head->m_next;
    delete tempPointer;
    m_size--;
    if(m_size == EMPTY_QUEUE_SIZE) {
        m_tail = nullptr;
    }
}

template<class T>
int Queue<T>::size() const {
    return m_size;
}

template<class T>
Queue<T>::Iterator::Iterator(Queue<T>* queue, Node* node) : 
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
    m_node = m_node->m_next;
    return *this;
}

template<class T>
T& Queue<T>::Iterator::operator*() {
    if(*this == m_queue->end()) {
        throw InvalidOperation();
    }
    return m_node->m_data;
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
Queue<T>::ConstIterator::ConstIterator(const Queue<T>* queue, const Node* node) : 
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
    m_node = m_node->m_next;
    return *this;
}

template<class T>
const T& Queue<T>::ConstIterator::operator*() const {
    if(*this == m_queue->end()) {
        throw InvalidOperation();
    }
    return m_node->m_data;
}

template<class T>
typename Queue<T>::ConstIterator Queue<T>::begin() const {
    return ConstIterator(this ,m_head);
}

template<class T>
typename Queue<T>::ConstIterator Queue<T>::end() const {
    return ConstIterator(this, nullptr);
}

/*
 * Filter the elements of a queue by a certain condition which is examine by a 
 * pointer to an bool function or an function object and returns a new queue with 
 * the elements who passed the conditin:
 * 
 * @param queue - The queue which the its elements are examine by the condition.
 * @param condition - The given function pointer or function object.
 * @return
 *      A new queue which contains only the elements of the given queue who passed the condition, 
 *      in the original order
*/
template<class T, class Condition>
Queue<T> filter(const Queue<T>& queue, Condition condition) {
    Queue<T> newQueue;
    for(typename Queue<T>::ConstIterator it = queue.begin(); it != queue.end(); ++it) {
        if(condition(*it)) {
            newQueue.pushBack(*it);
        }
    }
    return newQueue;
}

/*
 * Transform a queue elements by using a given pointer to a function or an function object:
 * 
 * @param queue - The queue which is transformed.
 * @param function - The given function pointer or function object.
 * @return
 *      void
*/
template<class T, class Function>
void transform(Queue<T>& queue, Function function) {
    for(typename Queue<T>::Iterator it = queue.begin(); it != queue.end(); ++it) {
        *it = function(*it);
    }
}

/*
 * Reduces the queue to a single value by using a given pointer to a function or a function object that gets as
 * parameters an element of the queue and a value,
 * the operation start with the first element of the queue and the given value and for each element of the queue
 * it does the same operation with the next element and the last returned value from the function:
 * 
 * @param queue - The queue which his elements are reduces.
 * @param value - The given value.
 * @param function - The given function pointer or function object.
 * @return
 *      A single value which the given queue is reduces to
*/
template<class T, class V, class Function>
V reduce(const Queue<T>& queue, const V& value, Function function) {
    V producedValue = value;
    for(typename Queue<T>::ConstIterator it = queue.begin(); it != queue.end(); ++it) {
        producedValue = function(*it, producedValue);
    }
    return producedValue;
}

#endif