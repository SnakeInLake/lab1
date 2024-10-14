#include "DualLinkedList.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

void DualLinkedList::init() {
    head = nullptr;
    tail = nullptr;
}

void DualLinkedList::addToHead(const string& value) {
    DualListNode* newDualListNode = new DualListNode{value, nullptr, head};
    if (head != nullptr) {
        head->prev = newDualListNode;
    }
    head = newDualListNode;
    if (tail == nullptr) {
        tail = head;
    }
}

void DualLinkedList::addToTail(const string& value) {
    DualListNode* newDualListNode = new DualListNode{value, tail, nullptr};
    if (tail != nullptr) {
        tail->next = newDualListNode;
    }
    tail = newDualListNode;
    if (head == nullptr) {
        head = tail;
    }
}

void DualLinkedList::removeFromHead() {
    if (head == nullptr) {
        cout << "Список пуст." << endl;
        return;
    }

    DualListNode* temp = head;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }
    delete temp;
}

void DualLinkedList::removeFromTail() {
    if (tail == nullptr) {
        cout << "Список пуст." << endl;
        return;
    }

    DualListNode* temp = tail;
    tail = tail->prev;
    if (tail != nullptr) {
        tail->next = nullptr;
    } else {
        head = nullptr;
    }
    delete temp;
}

void DualLinkedList::removeByValue(const string& value) {
    if (head == nullptr) {
        cout << "Список пуст." << endl;
        return;
    }

    DualListNode* temp = head;
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

bool DualLinkedList::search(const string& value) {
    DualListNode* temp = head;
    while (temp != nullptr) {
        if (temp->data == value) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void DualLinkedList::print() {
    DualListNode* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

void DualLinkedList::printReverse() {
    DualListNode* temp = tail;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->prev;
    }
    cout << endl;
}

void DualLinkedList::saveToFile(const std::string& fileName) {
    ofstream fout(fileName);
    DualListNode* temp = head;
    while (temp != nullptr) {
        fout << temp->data << endl;
        temp = temp->next;
    }
    fout.close();
}

void DualLinkedList::loadFromFile(const std::string& fileName) {
    ifstream fin(fileName);
    string value; 
    while (fin >> value) {
        addToTail(value);
    }
    fin.close();
}

void DualLinkedList::destroy() {
    while (head != nullptr) {
        removeFromHead();
    }
}

void runDualLinkedList(int argc, char* argv[]) {
    DualLinkedList list;
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
