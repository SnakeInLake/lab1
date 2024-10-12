#pragma once

#include <string>

struct ListNode {
    int data;
    ListNode* prev;
    ListNode* next;
};

struct LinkedList {
    ListNode* head;
    ListNode* tail;

    void init();
    void addToHead(int value);
    void addToTail(int value);
    void removeFromHead();
    void removeFromTail();
    void removeByValue(int value);
    bool search(int value);
    void print();
    void printReverse();
    void saveToFile(const std::string& fileName);
    void loadFromFile(const std::string& fileName);
    void destroy();
};

void runLinkedList(int argc, char* argv[]);