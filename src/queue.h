#pragma once

#include <string>


struct QueueNode {
    std::string data;
    QueueNode* next;
};

struct Queue {
    QueueNode* front;
    QueueNode* rear;

    void init();
    void enqueue(const std::string& value); 
    void dequeue();
    void print();
    void saveToFile(const std::string& fileName);
    void loadFromFile(const std::string& fileName);
    void destroy();
};

void runQueue(int argc, char* argv[]);