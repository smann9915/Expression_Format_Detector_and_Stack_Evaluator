#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

#include <optional>
#include <vector>
#include <stdexcept>

template <typename T>
class ArrayStack {
private:
    std::vector<T> data;

public:
    void push(const T& value) {
        data.push_back(value);

    }

    void pop() {
        if (empty()) {
            std::cerr << "Nothing to pop" << std::endl;
            std::exit(1);
        }

        return data.pop_back();
    }

    T top() const {
        if (empty()) {
            std::cerr << "The stack is empty." << std::endl;
            std::exit(1);
        }
        return data[data.size() - 1];
    }

    bool empty() const {
        return data.empty();
    }

    int size() const {
        return data.size();
    }
};

#endif
