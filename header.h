#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

#ifndef HEADER_H
#define HEADER_H

// Максимальное количество элементов
const int MAX_ELEMENTS = 100;

// Структура для хранения данных о структуре
struct Data {
    string name;
    string elements[MAX_ELEMENTS]; // Массив для хранения элементов
    int elementCount; // Количество элементов в массиве
};

//Односвязный список
// Структура узла односвязного списка
struct Node {
    string data;
    Node* next;
};

// Класс для представления односвязного списка
class forwardList {
private:


    Node* head;

public:
    // Конструктор
    forwardList();

    // Добавление элемента в голову списка
    void pushFront(string data);

    // Добавление элемента в хвост списка
    void pushBack(string data);

    // Удаление элемента с головы
    bool removeFirst();

    // Удаление элемента с хвоста
    bool removeLast();

    // Удаление элемента по значению
    bool remove(string data);

    // Поиск элемента по значению
    Node* find(string data);

    Node* getHead();

    // Вывод списка
    void print();
};


// Двусвязный список
// Структура для узла двусвязного списка
struct NodeDouble {
    string data;
    NodeDouble* prev;
    NodeDouble* next;
};

// Класс для реализации двусвязного списка
class DoublyLinkedList {
private:
    NodeDouble* head;
    NodeDouble* tail;

public:
    // Конструктор
    DoublyLinkedList();

    // Добавление элемента в голову списка
    void pushFront(string data);

    // Добавление элемента в хвост списка
    void pushBack(string data);

    // Удаление элемента с головы списка
    bool popFront();

    // Удаление элемента с хвоста списка
    bool popBack();

    // Удаление элемента по значению
    bool remove(string data);

    // Поиск элемента по значению
    NodeDouble* find(string data);

    NodeDouble* getHead();

    // Чтение списка
    void print();
};

// Очередь
template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(T value) : data(value), next(nullptr) {}
    };

    Node* front; // Указатель на первый элемент очереди
    Node* rear;  // Указатель на последний элемент очереди

public:
    Queue();
    ~Queue();
    bool isEmpty() const;
    void push(T value);
    void pop();
    T peek() const;
    void display() const;
};

//Стек
template<typename T>
class Stack {
public:
    Stack();
    ~Stack();

    bool isEmpty() const;
    void push(T value);
    void pop();
    T top() const;
    void print() const;

private:
    struct Node;
    Node* topNode;
};

//Массив

template <typename T>
class MyArray {
private:
    T* data;
    int size;
    int capacity;

public:
    // Конструктор по умолчанию
    MyArray();

    // Конструктор с указанием начальной емкости
    MyArray(int capacity);

    // Копирующий конструктор
    MyArray(const MyArray& other);

    // Оператор присваивания
    MyArray& operator=(const MyArray& other);

    // Деструктор
    ~MyArray();

    // Добавление элемента в конец массива
    void push_back(const T& value);

    // Добавление элемента по индексу
    void insert(int index, const T& value);

    // Получение элемента по индексу
    T& operator[](int index);

    // Получение элемента по индексу (константный)
    const T& operator[](int index) const;

    // Удаление элемента по индексу
    void erase(int index);

    // Замена элемента по индексу
    void replace(int index, const T& value);

    // Длина массива
    int length() const;

    // Чтение массива (для вывода на экран)
    friend ostream& operator<<(ostream& out, const MyArray& array) {
        out << "[";
        for (int i = 0; i < array.size; i++) {
            out << array.data[i];
            if (i < array.size - 1) {
                out << ", ";
            }
        }
        out << "]";
        return out;
    }

private:
    // Изменение размера массива
    void resize(int newCapacity);
};

//Хеш-таблица

template <typename KeyType, typename ValueType>
class HashNode {
public:
    KeyType key;
    ValueType value;
    HashNode* next;

    HashNode(const KeyType& key, const ValueType& value);
};

template <typename KeyType, typename ValueType>
class HashTable {
private:
    size_t size;
    HashNode<KeyType, ValueType>** table;

    size_t hash(const KeyType& key) const;

public:
    HashTable(size_t initialSize = 10);
    ~HashTable();

    void insert(const KeyType& key, const ValueType& value);
    ValueType get(const KeyType& key) const;
    void remove(const KeyType& key);
    bool contains(const KeyType& key) const;
    size_t getSize() const;
    HashNode<KeyType, ValueType>* getNodeAtIndex(size_t index) const;
    void print() const;
};

#endif

