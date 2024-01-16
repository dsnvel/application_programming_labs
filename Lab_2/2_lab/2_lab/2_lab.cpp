#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <map>

class MyMap {
protected:
    int find_position_of_key(std::string key) {
        int position = -1;
        for (int i = 0; i < keys.size(); i++) {
            if (keys[i] == key) {
                position = i;
                break;
            }
        }
        return position;
    }

    int check_empty_pos() {
        int size = keys.size();
        int position = size;
        for (int i = 0; i < size; i++) {
            if (keys[i].empty()) {
                position = i;
                break;
            }
        }
        return position;
    }
public:
    MyMap() {
        std::vector<std::string> keys = { "" };
        std::vector<std::vector<int>> elems_by_keys = { { } };
    }
    // ~MyMap();

    void add_elems_by_key(std::string key, int elem) {
        int position = find_position_of_key(key);
        elems_by_keys[position].push_back(elem);
    }

    void add_elems_by_key(std::string key, std::vector<int> elems) {
        int position = find_position_of_key(key);
        for (int i = 0; i < elems.size(); i++) {
            elems_by_keys[position].push_back(elems[i]);
        }
    }

    void add_key(std::string key, std::vector<int> elems = { }) {
        int position = check_empty_pos();
        if (position == keys.size())
            keys.push_back(key);
        else 
            keys[position] = key;
        elems_by_keys.push_back({});
        for (int i = 0; i < elems.size(); i++) {
            elems_by_keys[position].push_back(elems[i]);
        }
    }

    void delete_key(std::string key) {
        int position = find_position_of_key(key);
        keys[position].clear();
        elems_by_keys[position].clear();
    }

    void delete_elem_by_key(std::string key, int index=-1) {
        int position = find_position_of_key(key);
        int size = elems_by_keys[position].size();
        if (index >= size) {
            std::cout << "[-] Index out of array" << std::endl;
        }
        else {
            if (index == -1) {
                index = size - 1;
            }
            elems_by_keys[position].erase(elems_by_keys[position].begin() + index);
        } 
    }

    std::vector<int> get_elems_by_key(std::string key) {
        return elems_by_keys[find_position_of_key(key)];
    }

    void print_elems_by_key(std::string key) {
        std::vector<int> origin = get_elems_by_key(key);
        for (int i = 0; i < origin.size(); i++) {
            std::cout << origin[i] << " ";
        }
        std::cout << "\n";
    }

    void print() {
        for (int i = 0; i < keys.size(); i++) {
            std::string key = keys[i];
            std::cout << key << ": ";
            for (int j = 0; j < elems_by_keys[i].size(); j++) {
                std::cout << elems_by_keys[i][j] << ", ";
            }
            std::cout << "\n";
        }
    }
private:
    std::vector<std::string> keys;
    std::vector<std::vector<int>> elems_by_keys;
};

std::map<std::string, std::vector<int>> for_test;

int main()
{
    MyMap map;
    std::string key = "hello";
    auto start = std::chrono::steady_clock::now();
    map.add_key(key);
    map.add_key("test", { 1, 2, 3, 4 });

    /*map.print_elems_by_key(key);
    map.print();*/

    map.add_elems_by_key(key, 1);
    map.add_elems_by_key(key, {2, 3, 4});

    /*map.print_elems_by_key(key);*/

    map.delete_elem_by_key(key);
    map.delete_elem_by_key(key, 0);

    /*map.print_elems_by_key(key);
    map.print();*/

    map.delete_key(key);

    /*map.print();*/

    map.add_key("Danil", { 10, 11, 25});
    auto end = std::chrono::steady_clock::now();
    /*map.print();*/
    long duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Time used for MyMap: " << duration << " mcs" << std::endl;

    start = std::chrono::steady_clock::now();
    for_test[key];
    for_test["test"] = { 1, 2, 3, 4 };
    for_test[key].push_back(1);
    for_test[key].push_back(2);
    for_test[key].push_back(3);
    for_test[key].push_back(4);
    for_test[key].push_back(5);
    for_test[key].emplace_back();
    for_test[key].emplace(for_test[key].begin());
    for_test["Danil"] = { 10, 11, 25 };
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Time used for OriginalMap: " << duration << " mcs" << std::endl;
}
