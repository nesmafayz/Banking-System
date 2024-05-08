#ifndef NODE_H
#define NODE_H
#pragma once
template <typename T>
class Node {
public:
    T data;
    Node* next;

    Node(T value) : data(value), next(nullptr) {}
};

#endif // NODE_H
