#pragma once

#include <string>

struct ListNode {
    std::string data; 
    ListNode* next;
};

struct LinkedList {
    ListNode* head;
    ListNode* tail;

    void init();
    void addToHead(const std::string& value); 
    void addToTail(const std::string& value); 
    void removeFromHead();
    void removeFromTail();
    void removeByValue(const std::string& value); 
    bool search(const std::string& value); 
    void print();
    void saveToFile(const std::string& fileName);
    void loadFromFile(const std::string& fileName);
    void destroy();
};

void runLinkedList(int argc, char* argv[]);