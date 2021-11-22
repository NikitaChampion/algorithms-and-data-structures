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
        bool is_valid = getLine(&cur_line, 30u);
        if (std::cin.eof()) {
            break;
        }
        if (!is_valid) {
            std::cerr << "Too long username " << cur_line << "\n";
            exit(0);
        }
        if (checkUserName(cur_line)) {
            users.push_back(cur_line);
        } else {
            std::cerr << "Incorrect username " << cur_line << "\n";
            exit(0);
        }
    }
    return users;
}

struct Hasher {
    const int p = 31;
    size_t operator()(const string& s) const {
        size_t hash = 0, p_pow = 1;
        for (size_t i = 0; i < s.size(); ++i) {
            hash += (s[i] - 'a' + 1) * p_pow;
            p_pow *= p;
        }
        return hash;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::mt19937 gen(time(nullptr));
    std::uniform_int_distribution<int> dist(30'000, 1'000'000);
    size_t init_size = dist(gen);
    Hasher hasher;
    std::unordered_set<string, Hasher> users(init_size, hasher);

    auto users_list = getUsers(9'000u);
    auto start_time = std::clock();

    for (const auto& user : users_list) {
        users.insert(user);
    }

    auto end_time = std::clock();
    double spent = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
    std::cerr << "Spent " << spent << " seconds\n";
    if (spent > 0.75) {
        std::cerr << "Shit happens\n";
        return 1;
    }

    return 0;
}
