#pragma once

#include <string>

struct DynamicArray {
    std::string* data; 
    int size;
    int capacity;

    void init(int initialCapacity);
    void resize(int newCapacity);
    void add(const std::string& value); 
    void insert(int index, const std::string& value); 
    void remove(int index);
    std::string get(int index); 
    void set(int index, const std::string& value); 
    int length();
    void print();
    void destroy();
    void loadFromFile(const std::string& fileName);
    void saveToFile(const std::string& fileName);
};

void runDynamicArray(int argc, char* argv[]);