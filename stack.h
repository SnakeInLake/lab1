#pragma once

#include <string>

struct StackNode {
    int data;
    StackNode* next;
};

struct Stack {
    StackNode* top;

    void init();
    void push(int value);
    void pop();
    void print();
    void saveToFile(const std::string& fileName);
    void loadFromFile(const std::string& fileName);
    void destroy();
};

void runStack(int argc, char* argv[]);