#include <iostream>

#include "matrix.hpp"

void print() { std::cout << std::endl; }

template <typename T, typename... TArgs>
void print(T arg, TArgs... args) {
    if (sizeof...(args) == 0) {
        std::cout << arg << std::endl;
    } else {
        std::cout << arg << " ";
        print(args...);
    }
}

int main() {
    print("### Set up matrix ###");
    nvec::Matrix<int> a({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    print(a.to_string());
    print("### Set up ended ###");

    print("> Test #1");

    print("Index assess");
    print("Value at pos (1, 1): ");
    print(a(1, 1));
    print("Value at pos [1][1]: ");
    print(a[1][1]);
    print("Change value at pos (1, 1): ");
    a(1, 1) = 10;
    print(a(1, 1));
    print("Change value at pos [1][1] is not allowed");
    auto c = a[1][1];
    c = 11;
    print(a[1][1]);
    print("Subelements assess");
    print(a.to_string());
    print("Diagonal assess");
    print(a.get_diagonal().to_string());
    print("Row n assess");
    print(a[1].to_string());
    print("Vector n assess");
    print(a.get_Vector(1).to_string());

    print("> Test #2");
    print("Type transformation");
    print(nvec::Vector<int>({1, 2, 3, 4}).to_string());
    // print(nvec::Matrix({nvec::Row({1, 2}), nvec::Row({1, 2})}).to_string());
    // ToDo

    print("> Test #3");

    print("Math in same size objects");
    nvec::Matrix<int> first_({{1, 2}, {3, 4}});
    print(first_.to_string());

    nvec::Matrix<int> second_({{5, 6}, {7, 8}});
    print(second_.to_string());

    print("> first + second");
    print((first_ + second_).to_string());

    print("> first - second");
    print((first_ - second_).to_string());

    print("> Test #4");
    print("> Test #5");
    print("> Test #6");
    print("> Test #7");
    print("> Test #8");
    print("> Test #9");

    print("somethn");
    /*
    print(a.to_string());
    print(a[1][2]);
    auto b = a[1][2];
    b = 10;
    print(b);
    print(a[1][2]);
    auto c = a(1, 2);
    c = 10;
    print(a[1][2]);
    a(1, 2) = 10;
    print(a[1][2]); return Vector(subarray(data, col_num*row, col_num*(row+1)));
    print(a.to_string() << std::endl;*/
    return 0;
}