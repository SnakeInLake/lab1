#include "DualLinkedList.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

void LinkedList::init() {
    head = nullptr;
    tail = nullptr;
}

void LinkedList::addToHead(const string& value) {
    ListNode* newListNode = new ListNode{value, nullptr, head};
    if (head != nullptr) {
        head->prev = newListNode;
    }
    head = newListNode;
    if (tail == nullptr) {
        tail = head;
    }
}

void LinkedList::addToTail(const string& value) {
    ListNode* newListNode = new ListNode{value, tail, nullptr};
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
    if (head != nullptr) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }
    delete temp;
}

void LinkedList::removeFromTail() {
    if (tail == nullptr) {
        cout << "Список пуст." << endl;
        return;
    }

    ListNode* temp = tail;
    tail = tail->prev;
    if (tail != nullptr) {
        tail->next = nullptr;
    } else {
        head = nullptr;
    }
    delete temp;
}

void LinkedList::removeByValue(const string& value) {
    if (head == nullptr) {
        cout << "Список пуст." << endl;
        return;
    }

    ListNode* temp = head;
    while (temp != nullptr && temp->data != value) {
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Элемент " << value << " не найден." << endl;
        return;
    }

    if (temp->prev != nullptr) {
        temp->prev->next = temp->next;
    } else {
        head = temp->next;
    }

    if (temp->next != nullptr) {
        temp->next->prev = temp->prev;
    } else {
        tail = temp->prev;
    }

    delete temp;
}

bool LinkedList::search(const string& value) {
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

void LinkedList::printReverse() {
    ListNode* temp = tail;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->prev;
    }
    cout << endl;
}

void LinkedList::saveToFile(const std::string& fileName) {
    ofstream fout(fileName);
    ListNode* temp = head;
    while (temp != nullptr) {
        fout << temp->data << endl;
        temp = temp->next;
    }
    fout.close();
}

void LinkedList::loadFromFile(const std::string& fileName) {
    ifstream fin(fileName);
    string value; // Изменено на string
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
        list.addToHead(query);
        cout << "Значение " << query << " добавлено в голову списка." << endl;
    } else if (command == "LAPPEND") {
        list.addToTail(query);
        cout << "Значение " << query << " добавлено в хвост списка." << endl;
    } else if (command == "LREMOVEHEAD") {
        list.removeFromHead();
        cout << "Элемент с головы списка удалён." << endl;
    } else if (command == "LREMOVETAIL") {
        list.removeFromTail();
        cout << "Элемент с хвоста списка удалён." << endl;
    } else if (command == "LREMOVE") {
        list.removeByValue(query);
        cout << "Элемент " << query << " удалён из списка." << endl;
    } else if (command == "LSEARCH") {
        if (list.search(query)) {
            cout << "Элемент " << query << " найден в списке." << endl;
        } else {
            cout << "Элемент " << query << " не найден в списке." << endl;
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