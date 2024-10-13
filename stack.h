#pragma once

#include <string>

struct StackNode {
    std::string data; 
    StackNode* next;
};

struct Stack {
    StackNode* top;

    void init();
    void push(const std::string& value); 
    void pop();
    void print();
    void saveToFile(const std::string& fileName);
    void loadFromFile(const std::string& fileName);
    void destroy();
};

void runStack(int argc, char* argv[]);