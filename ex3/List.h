#ifndef NODE
#define NODE

template<class T>
class List {
    
    T data;
    List<T>* next;
    friend class Queue<T>;
    ~List() = default; //check this
public:
    List(T givenData);
    List();
    ~List() = default;
};

template<class T>
List<T>::List(T givenData) : 
    data(givenData), next(nullptr)
{}

template<class T>
List<T>::List() :
    data(), next(nullptr)
{}

#endif