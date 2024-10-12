#include "stack.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

void Stack::init() {
    top = nullptr;
}

void Stack::push(int value) {
    StackNode* newStackNode = new StackNode;
    newStackNode->data = value;
    newStackNode->next = top;
    top = newStackNode;
}

void Stack::pop() {
    if (top == nullptr) {
        cout << "Стек пуст." << endl;
        return;
    }

    StackNode* temp = top;
    top = top->next;
    delete temp;
}

void Stack::print() {
    if (top == nullptr) {
        cout << "Стек пуст." << endl;
        return;
    }

    StackNode* temp = top;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

void Stack::saveToFile(const string& fileName) {
    ofstream fout(fileName);
    StackNode* temp = top;
    while (temp != nullptr) {
        fout << temp->data << endl;
        temp = temp->next;
    }
    fout.close();
}

void Stack::loadFromFile(const string& fileName) {
    ifstream fin(fileName);
    int value;
    while (fin >> value) {
        push(value);
    }
    fin.close();
}

void Stack::destroy() {
    while (top != nullptr) {
        pop();
    }
}

void runStack(int argc, char* argv[]) {
    Stack stack;
    stack.init();

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

    stack.loadFromFile(fileName);

    string command;
    size_t pos = query.find(' ');
    if (pos != string::npos) {
        command = query.substr(0, pos);
        query = query.substr(pos + 1);
    } else {
        command = query;
    }

    if (command == "SPUSH") {
        try {
            int value = stoi(query);
            stack.push(value);
            cout << "Значение " << value << " добавлено в стек." << endl;
        } catch (const invalid_argument& e) {
            cout << "Ошибка: некорректное значение для команды SPUSH" << endl;
        }
    } else if (command == "SPOP") {
        stack.pop();
        cout << "Элемент с вершины стека удалён." << endl;
    } else if (command == "PRINT") {
        cout << "Стек: ";
        stack.print();
    } else {
        cout << "Ошибка: неизвестная команда " << command << endl;
    }

    stack.saveToFile(fileName);
    stack.destroy();
}