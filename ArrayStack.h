 #ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

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
            std::cout << "Nothing to pop" << std::endl;
            return;
        }

        return data.pop_back();
    }

    T top() const {
        // TODO
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
