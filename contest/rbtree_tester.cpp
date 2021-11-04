#include <iostream>

#include "rbtree.h"

struct LessThanOnly {
    int64_t value;

    bool operator<(const LessThanOnly& other) {
        return this->value < other.value;
    }
};

int main() {
    RBTree<LessThanOnly>* tree = nullptr;

    while (true) {
        std::string command;
        std::cin >> command;
        LessThanOnly val = { 0 };

        if (command == "new") {
            tree = new RBTree<LessThanOnly>();
            std::cout << "OK" << '\n';
        } else if (command == "copy") {
            tree = new RBTree<LessThanOnly>(*tree);
            std::cout << "OK" << '\n';
        } else if (command == "assign") {
            *tree = RBTree<LessThanOnly>();
            std::cout << "OK" << '\n';
        } else if (command == "delete") {
            delete tree;
            std::cout << "OK" << '\n';
        } else if (command == "size") {
            std::cout << tree->size() << '\n';
        } else if (command == "empty") {
            std::cout << (tree->empty() ? "YES" : "NO") << '\n';
        } else if (command == "insert") {
            std::cin >> val.value;
            tree->insert(val);
            std::cout << "OK" << '\n';
        } else if (command == "erase") {
            std::cin >> val.value;
            tree->erase(val);
            std::cout << "OK" << '\n';
        } else if (command == "find") {
            std::cin >> val.value;
            LessThanOnly* result = tree->find(val);
            std::cout << (result == nullptr ? "Not found" : "Found") << '\n';
        } else if (command == "lower_bound") {
            std::cin >> val.value;
            LessThanOnly* result = tree->lower_bound(val);
            if (result != nullptr) {
                std::cout << result->value << '\n';
            } else {
                std::cout << "None" << '\n';
            }
        } else if (command == "traversal") {
            LessThanOnly* result = tree->traversal();
            for (int i = 0; i < tree->size(); ++i) {
                std::cout << result[i].value;
            }
	    delete result;
            std::cout << '\n';
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "Internal tester error" << '\n';
        }
    }

    return 0;
}

