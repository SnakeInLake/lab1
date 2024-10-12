#include "LinkedList.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

void LinkedList::init() {
    head = nullptr;
    tail = nullptr;
}

void LinkedList::addToHead(int value) {
    ListNode* newListNode = new ListNode;
    newListNode->data = value;
    newListNode->next = head;
    head = newListNode;

    if (tail == nullptr) {
        tail = head;
    }
}

void LinkedList::addToTail(int value) {
    ListNode* newListNode = new ListNode;
    newListNode->data = value;
    newListNode->next = nullptr;

    if (tail != nullptr) {
        tail->next = newListNode;
    }
    tail = newListNode;

    if (head == nullptr) {
        head = tail;
    }
}

void LinkedList::removeFromHead() {
    if (head == nullptr) {
        cout << "Список пуст." << endl;
        return;
    }

    ListNode* temp = head;
    head = head->next;
    delete temp;

    if (head == nullptr) {
        tail = nullptr;
    }
}

void LinkedList::removeFromTail() {
    if (head == nullptr) {
        cout << "Список пуст." << endl;
        return;
    }

    if (head == tail) {
        delete head;
        head = nullptr;
        tail = nullptr;
        return;
    }

    ListNode* temp = head;
    while (temp->next != tail) {
        temp = temp->next;
    }

    delete tail;
    tail = temp;
    tail->next = nullptr;
}

void LinkedList::removeByValue(int value) {
    if (head == nullptr) {
        cout << "Список пуст." << endl;
        return;
    }

    if (head->data == value) {
        removeFromHead();
        return;
    }

    ListNode* temp = head;
    while (temp->next != nullptr && temp->next->data != value) {
        temp = temp->next;
    }

    if (temp->next == nullptr) {
        cout << "Элемент " << value << " не найден." << endl;
        return;
    }

    ListNode* toDelete = temp->next;
    temp->next = temp->next->next;

    if (toDelete == tail) {
        tail = temp;
    }

    delete toDelete;
}

bool LinkedList::search(int value) {
    ListNode* temp = head;
    while (temp != nullptr) {
        if (temp->data == value) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void LinkedList::print() {
    ListNode* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

void LinkedList::saveToFile(const string& fileName) {
    ofstream fout(fileName);
    ListNode* temp = head;
    while (temp != nullptr) {
        fout << temp->data << endl;
        temp = temp->next;
    }
    fout.close();
}

void LinkedList::loadFromFile(const string& fileName) {
    ifstream fin(fileName);
    int value;
    while (fin >> value) {
        addToTail(value);
    }
    fin.close();
}

void LinkedList::destroy() {
    while (head != nullptr) {
        removeFromHead();
    }
}

void runLinkedList(int argc, char* argv[]) {
    LinkedList list;
    list.init();

    string fileName;
    string query;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--file") == 0 && i + 1 < argc) {
            fileName = argv[i + 1];
            i++;
        } else if (strcmp(argv[i], "--query") == 0 && i + 1 < argc) {
            query = argv[i + 1];
            i++;
        }
    }

    if (fileName.empty()) {
        cout << "Ошибка: не указан файл (--file)" << endl;
        return;
    }

    if (query.empty()) {
        cout << "Ошибка: не указан запрос (--query)" << endl;
        return;
    }

    list.loadFromFile(fileName);

    string command;
    size_t pos = query.find(' ');
    if (pos != string::npos) {
        command = query.substr(0, pos);
        query = query.substr(pos + 1);
    } else {
        command = query;
    }

    if (command == "LPUSH") {
        try {
            int value = stoi(query);
            list.addToHead(value);
            cout << "Значение " << value << " добавлено в голову списка." << endl;
        } catch (const invalid_argument& e) {
            cout << "Ошибка: некорректное значение для команды LPUSH" << endl;
        }
    } else if (command == "LAPPEND") {
        try {
            int value = stoi(query);
            list.addToTail(value);
            cout << "Значение " << value << " добавлено в хвост списка." << endl;
        } catch (const invalid_argument& e) {
            cout << "Ошибка: некорректное значение для команды LAPPEND" << endl;
        }
    } else if (command == "LREMOVEHEAD") {
        list.removeFromHead();
        cout << "Элемент с головы списка удалён." << endl;
    } else if (command == "LREMOVETAIL") {
        list.removeFromTail();
        cout << "Элемент с хвоста списка удалён." << endl;
    } else if (command == "LREMOVE") {
        try {
            int value = stoi(query);
            list.removeByValue(value);
            cout << "Элемент " << value << " удалён из списка." << endl;
        } catch (const invalid_argument& e) {
            cout << "Ошибка: некорректное значение для команды LREMOVE" << endl;
        }
    } else if (command == "LSEARCH") {
        try {
            int value = stoi(query);
            if (list.search(value)) {
                cout << "Элемент " << value << " найден в списке." << endl;
            } else {
                cout << "Элемент " << value << " не найден в списке." << endl;
            }
        } catch (const invalid_argument& e) {
            cout << "Ошибка: некорректное значение для команды LSEARCH" << endl;
        }
    } else if (command == "PRINT") {
        cout << "Список: ";
        list.print();
    } else {
        cout << "Ошибка: неизвестная команда " << command << endl;
    }

    list.saveToFile(fileName);
    list.destroy();
}