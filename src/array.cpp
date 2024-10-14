#include "array.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

void DynamicArray::init(int initialCapacity) {
    data = new string[initialCapacity];
    size = 0;
    capacity = initialCapacity;
}

void DynamicArray::resize(int newCapacity) {
    string* newData = new string[newCapacity];
    memcpy(newData, data, size * sizeof(string));
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

void DynamicArray::add(const string& value) {
    if (size == capacity) {
        resize(capacity * 2);
    }
    data[size++] = value;
}

void DynamicArray::insert(int index, const string& value) {
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

string DynamicArray::get(int index) {
    if (index < 0 || index >= size) {
        cout << "Ошибка: индекс вне диапазона" << endl;
        return "";
    }
    return data[index];
}

void DynamicArray::set(int index, const string& value) {
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
    string value;
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
        arr.add(query);
        arr.saveToFile(fileName);
        cout << "Значение " << query << " добавлено в конец массива." << endl;
    } else if (command == "MINSERT") {
        size_t pos = query.find(' ');
        int index = stoi(query.substr(0, pos));
        string value = query.substr(pos + 1);
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
        string value = query.substr(pos + 1);
        arr.set(index, value);
        arr.saveToFile(fileName);
        cout << "Элемент по индексу " << index << " заменён на " << value << "." << endl;
    } else if (command == "MLEN") {
        cout << "Длина массива: " << arr.length() << endl;
    } else if (command == "PRINT") {
        cout << "Массив: ";
        arr.print();
    } else if (command == "MGET") {
    int index = stoi(query);
    string value = arr.get(index);
    if (!value.empty()) {
        cout << "Элемент по индексу " << index << ": " << value << endl;
    }
    } else {
        cout << "Ошибка: неизвестная команда " << command << endl;
    }

    arr.destroy();
}
