#pragma once
#include <vector>

namespace ds
{

template <typename T>
class Stack
{
public:
    Stack() { container = new std::vector<T>(); }
    Stack(const Stack& other)
    {
        container = new std::vector<T>();
        *container = *other.container;
    }
    ~Stack() { delete container; }

    T& top() const { return container->back(); }
    
    bool empty() const { return container->empty(); }
    size_t size() const { return container->size(); }

    void push(const T& value) { container->push_back(value); }
    void push(T&& value) { container->push_back(value); }
    void pop() { container->pop_back(); }

private:
    std::vector<T>* container;
};

}  // namespace ds