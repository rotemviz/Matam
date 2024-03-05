#ifndef NODE
#define NODE

template<class T>
class Node {
    
    T data;
    Node<T>* next;
    friend class Queue<T>;
    ~Node() = default; //check this
public:
    Node(T givenData);
    Node();
    ~Node() = default;
};

template<class T>
Node<T>::Node(T givenData) : 
    data(givenData), next(nullptr)
{}

template<class T>
Node<T>::Node() :
    data(), next(nullptr)
{}

#endif