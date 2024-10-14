#include <iostream>
#include <cstring>
#include "HashTable.h"
#include "AVLTree.h"
#include "array.h"
#include "LinkedList.h"
#include "DualLinkedList.h"
#include "queue.h"
#include "stack.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Ошибка: не указана программа для запуска (hash, tree, array, list, queue, stack)" << endl;
        return 1;
    }

    if (strcmp(argv[1], "hash") == 0) {
        runHashTable(argc - 1, argv + 1);
    } else if (strcmp(argv[1], "tree") == 0) {
        runAVLTree(argc - 1, argv + 1);
    } else if (strcmp(argv[1], "array") == 0) {
        runDynamicArray(argc - 1, argv + 1);
    } else if (strcmp(argv[1], "list") == 0) {
        runLinkedList(argc - 1, argv + 1);
    } else if (strcmp(argv[1], "list") == 0) {
        runDualLinkedList(argc - 1, argv + 1);
    } else if (strcmp(argv[1], "dlist") == 0) {
        runStack(argc - 1, argv + 1);
    } else if (strcmp(argv[1], "queue") == 0) {
        runQueue(argc - 1, argv + 1);
    } else if (strcmp(argv[1], "stack") == 0) {
        runStack(argc - 1, argv + 1);
    } else {
        cout << "Ошибка: неизвестная программа " << argv[1] << endl;
        return 1;
    }

    return 0;
}
