#include "header.h"


template <typename KeyType, typename ValueType>
HashNode<KeyType, ValueType>::HashNode(const KeyType& key, const ValueType& value)
    : key(key), value(value), next(nullptr) {}


template <typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::HashTable(size_t initialSize)
    : size(initialSize), table(new HashNode<KeyType, ValueType>*[size]) {
    for (size_t i = 0; i < size; ++i) {
        table[i] = nullptr;
    }
}


template <typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::~HashTable() {
    for (size_t i = 0; i < size; ++i) {
        HashNode<KeyType, ValueType>* current = table[i];
        while (current != nullptr) {
            HashNode<KeyType, ValueType>* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] table;
}


template <typename KeyType, typename ValueType>
size_t HashTable<KeyType, ValueType>::hash(const KeyType& key) const {
    return std::hash<KeyType>()(key) % size;
}

template <typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value) {
    size_t index = hash(key);
    HashNode<KeyType, ValueType>* newNode = new HashNode<KeyType, ValueType>(key, value);
    newNode->next = table[index];
    table[index] = newNode;
}

template <typename KeyType, typename ValueType>
ValueType HashTable<KeyType, ValueType>::get(const KeyType& key) const {
    size_t index = hash(key);
    HashNode<KeyType, ValueType>* current = table[index];
    while (current != nullptr) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    throw std::out_of_range("Ключ не найден в хеш-таблице");
}
template <typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::remove(const KeyType& key) {
    size_t index = hash(key);
    HashNode<KeyType, ValueType>* current = table[index];
    HashNode<KeyType, ValueType>* previous = nullptr;
    while (current != nullptr) {
        if (current->key == key) {
            if (previous == nullptr) {
                // Удаление первого элемента
                table[index] = current->next;
            } else {
                // Удаление не первого элемента
                previous->next = current->next;
            }
            delete current;
            return;
        }
        previous = current;
        current = current->next;
    }
    // Если элемент не найден, ничего не делаем
}

template <typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::contains(const KeyType& key) const {
    size_t index = hash(key);
    HashNode<KeyType, ValueType>* current = table[index];
    while (current != nullptr) {
        if (current->key == key) {
            return true;
        }
        current = current->next;
    }
    return false;
}

template <typename KeyType, typename ValueType>
size_t HashTable<KeyType, ValueType>:: getSize() const {
    return size;
}

template <typename KeyType, typename ValueType>
HashNode<KeyType, ValueType>* HashTable<KeyType, ValueType>::getNodeAtIndex(size_t index) const {
    if (index >= size) {
        return nullptr; // или выбросить исключение
    }
    return table[index]; // возвращаем указатель на первый узел в ячейке
}


template <typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::print() const {
    for (size_t i = 0; i < size; ++i) {
        cout << "Индекс " << i << ": ";
        HashNode<KeyType, ValueType>* current = table[i];
        while (current != nullptr) {
            cout << "(" << current->key << ", " << current->value << ") ";
            current = current->next;
        }
        cout << endl;
    }
}


