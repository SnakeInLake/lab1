#pragma once

#include <string>

struct DynamicArray {
    int* data;
    int size;
    int capacity;

    void init(int initialCapacity);
    void resize(int newCapacity);
    void add(int value);
    void insert(int index, int value);
    void remove(int index);
    int get(int index);
    void set(int index, int value);
    int length();
    void print();
    void destroy();
    void loadFromFile(const std::string& fileName);
    void saveToFile(const std::string& fileName);
};

void runDynamicArray(int argc, char* argv[]);