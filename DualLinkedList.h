#pragma once

#include <string>

struct ListNode {
    std::string data; // Изменено на string
    ListNode* prev;
    ListNode* next;
};

struct LinkedList {
    ListNode* head;
    ListNode* tail;

    void init();
    void addToHead(const std::string& value); // Изменено на string
    void addToTail(const std::string& value); // Изменено на string
    void removeFromHead();
    void removeFromTail();
    void removeByValue(const std::string& value); // Изменено на string
    bool search(const std::string& value); // Изменено на string
    void print();
    void printReverse();
    void saveToFile(const std::string& fileName);
    void loadFromFile(const std::string& fileName);
    void destroy();
};

void runLinkedList(int argc, char* argv[]);