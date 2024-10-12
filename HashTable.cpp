#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

// Структура для хранения пары ключ-значение
struct HashNode {
    string key;
    string value;
    HashNode* next;  // Указатель на следующий узел в цепочке
};

// Максимальный размер хеш-таблицы
const int TABLE_SIZE = 10;

// Хеш-таблица — это массив указателей на узлы
HashNode* hashTable[TABLE_SIZE];

// Инициализация хеш-таблицы
void initTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = nullptr;
    }
}

// Хеш-функция: преобразует ключ в индекс массива
int hashFunction(const string& key) {
    int hash = 0;
    for (char ch : key) {
        hash += ch;
    }
    return hash % TABLE_SIZE;
}

// Добавление элемента в хеш-таблицу
void insert(const string& key, const string& value) {
    int index = hashFunction(key);
    HashNode* newNode = new HashNode{key, value, nullptr};

    // Если в ячейке еще нет элементов
    if (hashTable[index] == nullptr) {
        hashTable[index] = newNode;
    } else {
        HashNode* current = hashTable[index];
        while (current != nullptr) {
            // Если ключ уже существует, обновляем его значение
            if (current->key == key) {
                current->value = value;
                delete newNode;
                return;
            }
            current = current->next;
        }
        // Добавляем новый узел в начало цепочки
        newNode->next = hashTable[index];
        hashTable[index] = newNode;
    }
}

// Получение значения по ключу
string get(const string& key) {
    int index = hashFunction(key);
    HashNode* current = hashTable[index];

    while (current != nullptr) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return "Ключ не найден";
}

// Удаление элемента по ключу
void remove(const string& key) {
    int index = hashFunction(key);
    HashNode* current = hashTable[index];
    HashNode* prev = nullptr;

    while (current != nullptr) {
        if (current->key == key) {
            if (prev == nullptr) {
                hashTable[index] = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
    cout << "Ключ не найден для удаления" << endl;
}

// Печать всей хеш-таблицы
void printTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << "Индекс " << i << ": ";
        HashNode* current = hashTable[i];
        while (current != nullptr) {
            cout << "[" << current->key << ": " << current->value << "] ";
            current = current->next;
        }
        cout << endl;
    }
}

// Запись хеш-таблицы в файл
void saveToFile(const string& fileName) {
    ofstream file(fileName);
    if (!file.is_open()) {
        cout << "Ошибка: не удалось открыть файл для записи." << endl;
        return;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode* current = hashTable[i];
        while (current != nullptr) {
            file << current->key << " " << current->value << endl;
            current = current->next;
        }
    }
    file.close();
}

// Чтение хеш-таблицы из файла
void loadFromFile(const string& fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Ошибка: не удалось открыть файл для чтения." << endl;
        return;
    }

    string key, value;
    while (file >> key >> value) {
        insert(key, value);
    }
    file.close();
}

// Освобождение памяти для всей хеш-таблицы
void freeTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode* current = hashTable[i];
        while (current != nullptr) {
            HashNode* temp = current;
            current = current->next;
            delete temp;
        }
        hashTable[i] = nullptr;
    }
}

void runHashTable(int argc, char* argv[]) {
    initTable();

    string fileName;
    string query;

    // Разбираем параметры командной строки
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--file") == 0 && i + 1 < argc) {
            fileName = argv[i + 1];
            i++;
        }
        else if (strcmp(argv[i], "--query") == 0 && i + 1 < argc) {
            query = argv[i + 1];
            i++;
        }
    }

    // Если файл задан, загружаем данные из файла
    if (!fileName.empty()) {
        loadFromFile(fileName);
    }

    if (query.empty()) {
        cout << "Ошибка: не указан запрос (--query)" << endl;
        return;
    }

    // Обработка команды
    string command;
    size_t pos = query.find(' ');
    if (pos != string::npos) {
        command = query.substr(0, pos);
        query = query.substr(pos + 1);
    } else {
        command = query;
    }

    if (command == "HSET") {
        size_t pos = query.find(' ');
        if (pos != string::npos) {
            string key = query.substr(0, pos);
            string value = query.substr(pos + 1);
            insert(key, value);
            cout << "Пара '" << key << ": " << value << "' добавлена в хеш-таблицу." << endl;
        } else {
            cout << "Ошибка: некорректный формат для команды HSET" << endl;
        }
    } else if (command == "HGET") {
        string key = query;
        cout << "Значение по ключу '" << key << "': " << get(key) << endl;
    } else if (command == "HDEL") {
        string key = query;
        remove(key);
        cout << "Ключ '" << key << "' удалён." << endl;
    } else if (command == "PRINT") {
        printTable();
    } else {
        cout << "Ошибка: неизвестная команда " << command << endl;
    }

    // Если файл задан, сохраняем данные в файл
    if (!fileName.empty()) {
        saveToFile(fileName);
    }

    // Освобождаем память
    freeTable();
}