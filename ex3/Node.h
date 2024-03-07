#ifndef NODE
#define NODE

template<class T>
class Node {
    
    friend class Queue<T>;
    T data;
    Node<T>* next;
    
    Node(const T& givenData);
    ~Node() = default;
};

template<class T>
Node<T>::Node(const T& givenData) : 
    data(givenData), next(nullptr)
{}

#endif