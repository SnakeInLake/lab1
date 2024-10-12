#include "queue.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

void Queue::init() {
    front = nullptr;
    rear = nullptr;
}

void Queue::enqueue(int value) {
    QueueNode* newQueueNode = new QueueNode;
    newQueueNode->data = value;
    newQueueNode->next = nullptr;

    if (rear != nullptr) {
        rear->next = newQueueNode;
    }
    rear = newQueueNode;

    if (front == nullptr) {
        front = rear;
    }
}

void Queue::dequeue() {
    if (front == nullptr) {
        cout << "Очередь пуста." << endl;
        return;
    }

    QueueNode* temp = front;
    front = front->next;
    delete temp;

    if (front == nullptr) {
        rear = nullptr;
    }
}

void Queue::print() {
    if (front == nullptr) {
        cout << "Очередь пуста." << endl;
        return;
    }

    QueueNode* temp = front;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

void Queue::saveToFile(const string& fileName) {
    ofstream fout(fileName);
    QueueNode* temp = front;
    while (temp != nullptr) {
        fout << temp->data << endl;
        temp = temp->next;
    }
    fout.close();
}

void Queue::loadFromFile(const string& fileName) {
    ifstream fin(fileName);
    int value;
    while (fin >> value) {
        enqueue(value);
    }
    fin.close();
}

void Queue::destroy() {
    while (front != nullptr) {
        dequeue();
    }
}

void runQueue(int argc, char* argv[]) {
    Queue queue;
    queue.init();

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

    queue.loadFromFile(fileName);

    string command;
    size_t pos = query.find(' ');
    if (pos != string::npos) {
        command = query.substr(0, pos);
        query = query.substr(pos + 1);
    } else {
        command = query;
    }

    if (command == "QPUSH") {
        try {
            int value = stoi(query);
            queue.enqueue(value);
            cout << "Значение " << value << " добавлено в очередь." << endl;
        } catch (const invalid_argument& e) {
            cout << "Ошибка: некорректное значение для команды QPUSH" << endl;
        }
    } else if (command == "QPOP") {
        queue.dequeue();
        cout << "Элемент из начала очереди удалён." << endl;
    } else if (command == "PRINT") {
        cout << "Очередь: ";
        queue.print();
    } else {
        cout << "Ошибка: неизвестная команда " << command << endl;
    }

    queue.saveToFile(fileName);
    queue.destroy();
}