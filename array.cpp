#include "array.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

void DynamicArray::init(int initialCapacity) {
    data = new int[initialCapacity];
    size = 0;
    capacity = initialCapacity;
}

void DynamicArray::resize(int newCapacity) {
    int* newData = new int[newCapacity];
    memcpy(newData, data, size * sizeof(int));
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

void DynamicArray::add(int value) {
    if (size == capacity) {
        resize(capacity * 2);
    }
    data[size++] = value;
}

void DynamicArray::insert(int index, int value) {
    if (index < 0 || index > size) {
        cout << "Ошибка: индекс вне диапазона" << endl;
        return;
    }
    if (size == capacity) {
        resize(capacity * 2);
    }
    for (int i = size; i > index; i--) {
        data[i] = data[i - 1];
    }
    data[index] = value;
    size++;
}

void DynamicArray::remove(int index) {
    if (index < 0 || index >= size) {
        cout << "Ошибка: индекс вне диапазона" << endl;
        return;
    }
    for (int i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
}

int DynamicArray::get(int index) {
    if (index < 0 || index >= size) {
        cout << "Ошибка: индекс вне диапазона" << endl;
        return -1;
    }
    return data[index];
}

void DynamicArray::set(int index, int value) {
    if (index < 0 || index >= size) {
        cout << "Ошибка: индекс вне диапазона" << endl;
        return;
    }
    data[index] = value;
}

int DynamicArray::length() {
    return size;
}

void DynamicArray::print() {
    for (int i = 0; i < size; i++) {
        cout << data[i] << " ";
    }
    cout << endl;
}

void DynamicArray::destroy() {
    delete[] data;
}

void DynamicArray::loadFromFile(const string& fileName) {
    ifstream file(fileName);
    int value;
    while (file >> value) {
        add(value);
    }
}

void DynamicArray::saveToFile(const string& fileName) {
    ofstream file(fileName, ios::trunc);
    for (int i = 0; i < size; i++) {
        file << data[i] << endl;
    }
}

void runDynamicArray(int argc, char* argv[]) {
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

    DynamicArray arr;
    arr.init(10);
    arr.loadFromFile(fileName);

    string command;
    size_t pos = query.find(' ');
    command = (pos != string::npos) ? query.substr(0, pos) : query;
    query = (pos != string::npos) ? query.substr(pos + 1) : "";

    if (command == "MPUSH") {
        int value = stoi(query);
        arr.add(value);
        arr.saveToFile(fileName);
        cout << "Значение " << value << " добавлено в конец массива." << endl;
    } else if (command == "MINSERT") {
        size_t pos = query.find(' ');
        int index = stoi(query.substr(0, pos));
        int value = stoi(query.substr(pos + 1));
        arr.insert(index, value);
        arr.saveToFile(fileName);
        cout << "Значение " << value << " добавлено по индексу " << index << "." << endl;
    } else if (command == "MDEL") {
        int index = stoi(query);
        arr.remove(index);
        arr.saveToFile(fileName);
        cout << "Элемент по индексу " << index << " удалён." << endl;
    } else if (command == "MSET") {
        size_t pos = query.find(' ');
        int index = stoi(query.substr(0, pos));
        int value = stoi(query.substr(pos + 1));
        arr.set(index, value);
        arr.saveToFile(fileName);
        cout << "Элемент по индексу " << index << " заменён на " << value << "." << endl;
    } else if (command == "MLEN") {
        cout << "Длина массива: " << arr.length() << endl;
    } else if (command == "PRINT") {
        cout << "Массив: ";
        arr.print();
    } else {
        cout << "Ошибка: неизвестная команда " << command << endl;
    }

    arr.destroy();
}