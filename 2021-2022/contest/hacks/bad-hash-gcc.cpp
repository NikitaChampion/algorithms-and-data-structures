#include <iostream>
#include <unordered_set>
#include <string>
#include <ctime>
#include <cctype>
#include <random>
#include <cstdlib>

using std::string;

bool checkUserName(const std::string& user) {
    for (char c : user) {
        if (!isalpha(c) && !isdigit(c) && c != '_') {
            return false;
        }
    }
    return true;
}

bool getLine(std::string* line, size_t max_length) {
    line->clear();
    while (std::cin && line->size() <= max_length) {
        int symbol = std::cin.get();
        if (symbol == '\n') {
            return true;
        }
        line->push_back(symbol);
    }
    return false;
}

std::vector<std::string> getUsers(size_t max_count) {
    std::vector<std::string> users;
    std::string cur_line;
    while (users.size() < max_count) {
        bool is_valid = getLine(&cur_line, 15u);
        if (std::cin.eof()) {
            break;
        }
        if (!is_valid) {
            std::cout << "Too long username " << cur_line << '\n';
            exit(0);
        }
        if (checkUserName(cur_line)) {
            users.push_back(cur_line);
        } else {
            std::cout << "Incorrect username " << cur_line << '\n';
            exit(0);
        }
    }
    return users;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::mt19937 gen(time(nullptr));
    std::uniform_int_distribution<int> dist(30'000, 1'000'000);
    size_t init_size = dist(gen);
    std::unordered_set<string> users(init_size);

    auto users_list = getUsers(15'000u);
    auto start_time = std::clock();

    for (const auto& user : users_list) {
        users.insert(user);
    }

    auto end_time = std::clock();
    double spent = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
    std::cout << "Spent " << spent << " seconds\n";
    if (spent > 1.5) {
        std::cout << "Shit happens\n";
        return 1;
    }
    return 0;
}
