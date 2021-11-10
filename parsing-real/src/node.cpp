#include "../include/node.h"

namespace Parser {
    
    template <class T>
    Node<T>::Node(T data) {
        num_nodes++;
        id_ = num_nodes;
        data_ = data;
    }

    template <class T>
    uint Node<T>::getID() {
        return id_;
    }

    template <class T>
    T Node<T>::getData() {
        return data_;
    }
}