#ifndef NODE
#define NODE

template<class T>
class Node {
    
    T data;
    Node<T>* next;
    friend class Queue<T>;

public:
    Node(const T& givenData);
    ~Node() = default;
};

template<class T>
Node<T>::Node(const T& givenData) : 
    data(givenData), next(nullptr)
{}

#endif