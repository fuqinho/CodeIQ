#include "dicti.h"
#include <iostream>
#include <sstream>
 
/////////////////////////////////////////////////////////
// テスト用辞書プログラム
// Usage: g++ main.cpp && ./a.out < testdata.txt
int main() {
    long long sum = 0;
    std::string line;
    while (std::getline(std::cin, line)) {
        if (!line.empty()) {
            if (line[0] == 's') {
                std::stringstream ss(line.substr(2));
                unsigned int key, value;
                ss >> key >> value;
                set_entry(key, value);
            }
            if (line[0] == 'f') {
                std::stringstream ss(line.substr(2));
                unsigned int key;
                ss >> key;
                sum += find_entry(key);
            }
        }
    }
    std::cout << sum << std::endl;
}
