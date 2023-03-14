#include <iostream>
#include <list>
#include <random>
#include <vector>
#include <ctime>

using namespace std;

vector<int> get_digits(int num) {
    vector<int> digits;

    if (num == 0)
        return {0};

    while (num > 0) {
        digits.push_back(num % 10);
        num /= 10;
    }
    return digits;
};

template<typename V>
struct HashTable {
    HashTable();

    vector<list<pair<int, V>>> container;
    vector<int> rand_vars;

    void insert(int key, V value);
    pair<int, V> search(int key);

    int hash(int key);
};

template<typename V>
HashTable<V>::HashTable() {
    default_random_engine generator(time(nullptr));
    uniform_int_distribution<int> distribute(0, 6);

    for (int i = 0; i < 7; ++i)
        rand_vars.push_back(distribute(generator));

    container.resize(7);
}

template<typename V>
int HashTable<V>::hash(int key) {
    vector<int> digits = get_digits(key);
    int sum = 0;

    for (int i = 0; i < digits.size(); ++i)
        sum += rand_vars[i] * digits[i];

    return sum % 7;
}

template<typename V>
void HashTable<V>::insert(int key, V value) {
    int k = hash(key);

    auto it = find_if(container[k].begin(), container[k].end(), [&key](const auto &p){ return p.first == key; });
    if (it != container[k].end())
        it->second = value;
    else
        container[k].push_front({key, value});
}

template<typename V>
pair<int, V> HashTable<V>::search(int key) {
    int k = hash(key);

    auto it = find_if(container[k].begin(), container[k].end(), [&key](const auto &p){ return p.first == key; });
    if (it == container[k].end()) {
        cout << "Error: could not find element with key: " << key << '.';
        return {};
    }
    else
        return *it;
}

int main() {
    HashTable<float> hashTable;

    vector<int> keys = {
            43, 63, 73, 8, 48, 43, 88, 21, 88, 85, 58, 44, 30, 35, 19, 66, 96, 43, 2, 51, 73, 57, 
            2, 29, 11, 81, 15, 49, 82, 17, 13, 83, 32, 67, 99, 72, 73, 96, 55, 19, 18, 60, 74, 76, 
            3, 60, 75, 77, 81, 16, 31, 62, 18, 44, 23, 55, 64, 20, 86, 70, 100, 84, 99, 41, 68, 57
    };

    float value = 0.0f;
    for (auto key : keys) {
        hashTable.insert(key, value);
        value += 0.1f;
    }

    pair<int, float> p = hashTable.search(5);

    cout << p.first << ", " << p.second << endl;

    return 0;
}