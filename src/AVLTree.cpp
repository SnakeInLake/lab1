#include "AVLTree.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

int height(Node* node) {
    return node ? node->height : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node* createNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    return node;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Получение баланс-фактора узла
int getBalance(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

Node* insert(Node* node, int key) {
    // Если текущий узел пуст, создаем новый узел с заданным ключом
    if (node == nullptr)
        return createNode(key);

    // Если ключ меньше, чем ключ текущего узла, продолжаем вставку в левое поддерево
    if (key < node->key)
        node->left = insert(node->left, key);
    // Если ключ больше, чем ключ текущего узла, продолжаем вставку в правое поддерево
    else if (key > node->key)
        node->right = insert(node->right, key);
    // Если ключ равен ключу текущего узла, ничего не делаем (дубликаты не допускаются)
    else
        return node;

    // Обновляем высоту текущего узла
    node->height = 1 + max(height(node->left), height(node->right));

    // Получаем баланс-фактор текущего узла
    int balance = getBalance(node);

    // Если баланс-фактор положительный и ключ меньше, чем ключ левого дочернего узла, 
    // выполняем правый поворот
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Если баланс-фактор отрицательный и ключ больше, чем ключ правого дочернего узла, 
    // выполняем левый поворот
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Если баланс-фактор положительный и ключ больше, чем ключ левого дочернего узла, 
    // сначала выполняем левый поворот, а затем правый
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);  // Левый поворот на левом дочернем узле
        return rightRotate(node);              // Правый поворот на текущем узле
    }

    // Если баланс-фактор отрицательный и ключ меньше, чем ключ правого дочернего узла, 
    // сначала выполняем правый поворот, а затем левый
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right); // Правый поворот на правом дочернем узле
        return leftRotate(node);                 // Левый поворот на текущем узле
    }

    // Возвращаем (возможно, обновленный) текущий узел
    return node;
}


Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, int key) {
    // Если дерево пустое, возвращаем nullptr
    if (root == nullptr)
        return root;

    // Если ключ меньше, чем ключ текущего узла, продолжаем поиск в левом поддереве
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    // Если ключ больше, чем ключ текущего узла, продолжаем поиск в правом поддереве
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else { // Узел с ключом найден
        // Если у узла один или нет дочерних узлов
        if ((root->left == nullptr) || (root->right == nullptr)) {
            Node* temp = root->left ? root->left : root->right; // Получаем единственного дочернего узла или nullptr

            // Если дочерний узел отсутствует, просто удаляем узел
            if (temp == nullptr) {
                temp = root; // Сохраняем текущий узел для удаления
                root = nullptr; // Удаляем текущий узел
            } else { // Если есть дочерний узел, заменяем текущий узел его значением
                *root = *temp; // Копируем данные дочернего узла в текущий
            }
            delete temp; // Удаляем временный узел
        } else { // У узла два дочерних узла
            Node* temp = minValueNode(root->right); // Находим минимальное значение в правом поддереве

            root->key = temp->key; // Копируем ключ из минимального узла в текущий

            // Удаляем минимальный узел из правого поддерева
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // Если дерево стало пустым, возвращаем nullptr
    if (root == nullptr)
        return root;

    // Обновляем высоту текущего узла
    root->height = 1 + max(height(root->left), height(root->right));

    // Получаем баланс-фактор текущего узла
    int balance = getBalance(root);

    // Проверяем балансировку и выполняем соответствующие повороты
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root); // Правый поворот

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left); // Левый поворот на левом дочернем узле
        return rightRotate(root); // Правый поворот
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root); // Левый поворот

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right); // Правый поворот на правом дочернем узле
        return leftRotate(root); // Левый поворот
    }

    // Возвращаем (возможно, обновленный) корень
    return root;
}


bool search(Node* root, int key) {
    if (root == nullptr)
        return false;
    if (key == root->key)
        return true;
    if (key < root->key)
        return search(root->left, key);
    return search(root->right, key);
}

void saveTree(Node* root, ofstream& file) {
    if (root != nullptr) {
        saveTree(root->left, file);
        file << root->key << " ";
        saveTree(root->right, file);
    }
}

void printTree(Node* root, int space = 0) {
    if (root == nullptr) return;

    space += 5;

    printTree(root->right, space);

    cout << endl;
    for (int i = 5; i < space; i++)
        cout << " ";
    cout << root->key << "\n";

    printTree(root->left, space);
}

Node* loadTree(ifstream& file) {
    Node* root = nullptr;
    int key;
    while (file >> key) {
        root = insert(root, key);
    }
    return root;
}

void runAVLTree(int argc, char* argv[]) {
    if (argc < 5) {
        cout << "Ошибка: недостаточно аргументов." << endl;
        return;
    }

    string filename;
    string query;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--file") == 0 && i + 1 < argc) {
            filename = argv[i + 1];
            i++;
        }
        else if (strcmp(argv[i], "--query") == 0 && i + 1 < argc) {
            query = argv[i + 1];
            i++;
        }
    }

    if (filename.empty()) {
        cout << "Ошибка: не указан файл (--file)" << endl;
        return;
    }

    if (query.empty()) {
        cout << "Ошибка: не указан запрос (--query)" << endl;
        return;
    }

    Node* root = nullptr;

    ifstream infile(filename);
    if (infile.is_open()) {
        root = loadTree(infile);
        infile.close();
    } else {
        cout << "Не удалось открыть файл. Начинаем с пустого дерева." << endl;
    }

    string command;
    size_t pos = query.find(' ');
    if (pos != string::npos) {
        command = query.substr(0, pos);
        query = query.substr(pos + 1);
    } else {
        command = query;
    }

    if (command == "TINSERT") {
        try {
            int value = stoi(query);
            root = insert(root, value);
            cout << "Элемент " << value << " добавлен в дерево." << endl;
        } catch (const invalid_argument& e) {
            cout << "Ошибка: некорректное значение для команды INSERT" << endl;
        }
    } else if (command == "TSEARCH") {
        try {
            int value = stoi(query);
            if (search(root, value)) {
                cout << "Элемент " << value << " найден в дереве." << endl;
            } else {
                cout << "Элемент " << value << " не найден в дереве." << endl;
            }
        } catch (const invalid_argument& e) {
            cout << "Ошибка: некорректное значение для команды SEARCH" << endl;
        }
    } else if (command == "PRINT") {
        cout << "Дерево:" << endl;
        printTree(root);
    } else if (command == "TDEL") {
        try {
            int value = stoi(query);
            root = deleteNode(root, value);
            cout << "Элемент " << value << " удалён из дерева." << endl;
        } catch (const invalid_argument& e) {
            cout << "Ошибка: некорректное значение для команды DELETE" << endl;
        }
    } else {
        cout << "Ошибка: неизвестная команда '" << command << "'." << endl;
        return;
    }

    ofstream outfile(filename);
    if (outfile.is_open()) {
        saveTree(root, outfile);
        outfile.close();
    } else {
        cout << "Не удалось открыть файл для записи." << endl;
    }
}