#include "header.h"
#include "queue.cpp"
#include "Stack.cpp"
#include "Array.cpp"
#include "hashTable.cpp"
#include <getopt.h>


Data loadData(const string& filename) {
    Data data;
    ifstream file(filename);
    if (file.is_open()) {
        getline(file, data.name); // Считываем имя структуры
        string line;
        data.elementCount = 0;
        while (getline(file, line) && data.elementCount < MAX_ELEMENTS) {
            data.elements[data.elementCount++] = line; // Добавляем элементы
        }
        file.close();
    } else {
        // Если файл не найден, создаем его
        ofstream newFile(filename);
        if (newFile.is_open()) {
            cout << "Файл " << filename << " создан. Перезапустите программу" << endl;
            newFile.close();
        } else {
            cerr << "Ошибка создания файла: " << filename << endl;
        }
        exit(0);
    }
    return data;
}

void saveData(const string& filename, const Data& data) {
    ofstream file(filename);
    if (file.is_open()) {
        file << data.name << endl; // Записываем имя структуры
        for (int i = 0; i < data.elementCount; ++i) {
            file << data.elements[i] << endl; // Записываем элементы
        }
        file.close();
    } else {
        cerr << "Ошибка открытия файла: " << filename << endl;
    }
}

// Очистка файла
void clearFile(const string& filename) {
    ofstream file(filename, ofstream::trunc); // Перезаписываем файл
    file.close();
}

// Функция для копирования элементов из массива в очередь
template<typename T>
void copyElementsToQueue(Queue<T>& ourQueue, const string elements[], int count) {
    for (int i = 0; i < count; ++i) {
        ourQueue.push(elements[i]);
    }
}

// Функция для копирования элементов из очереди в массив
template<typename T>
void copyElementsFromQueue(Queue<T>& ourQueue, string elements[], int& count) {
    while (!ourQueue.isEmpty()) {
        elements[count++] = ourQueue.peek();
        ourQueue.pop();
    }
}

// Функция для копирования элементов из массива в стек
template<typename T>
void copyElementsToStack(Stack<T>& ourStack, const string elements[], int count) {
    for (int i = count - 1; i >= 0; --i) { // Обратный порядок для стека
        ourStack.push(elements[i]);
    }
}

// Функция для копирования элементов из стека в массив
template<typename T>
void copyElementsFromStack(Stack<T>& ourStack, string elements[], int& count) {
    while (!ourStack.isEmpty()) {
        elements[count++] = ourStack.top();
        ourStack.pop();
    }
}

// Функция для копирования элементов из массива в односвязный список
void copyElementsToList(forwardList& list, const string elements[], int count) {
    for (int i = 0; i < count; ++i) {
        list.pushBack(elements[i]);
    }
}

// Функция для копирования элементов из односвязного списка в массив
void copyElementsFromList(forwardList& list, string elements[], int& count) {
    Node* current = list.getHead();
    while (current != nullptr) {
        elements[count++] = current->data;
        current = current->next;
    }
}

// Функция для копирования элементов из массива в двусвязный список
void copyElementsToDoubleList(DoublyLinkedList& doubleList, const string elements[], int count) {
    for (int i = 0; i < count; ++i) {
        doubleList.pushBack(elements[i]);
    }
}

// Функция для копирования элементов из двусвязного списка в массив
void copyElementsFromDoubleList(DoublyLinkedList& doubleList, string elements[], int& count) {
    NodeDouble* current = doubleList.getHead();
    while (current != nullptr) {
        elements[count++] = current->data;
        current = current->next;
    }
}


// Функция для копирования элементов из массива в массив MyArray
template<typename T>
void CopyElementsToArray(MyArray<T>& myArray, const string elements[], int count) {
    for (int i = 0; i < count; ++i) {
        myArray.push_back(elements[i]);
    }
}

// Функция для копирования элементов из массива MyArray в массив
template<typename T>
void CopyElementsFromArray(MyArray<T>& myArray, string elements[], int& count) {
    for (int i = 0; i < myArray.length(); ++i) {
        elements[count++] = myArray[i];
    }
}

// Функция для преобразования массива строк в хеш-таблицу
void convertArrayToHashTable(const string elements[], int elementCount, HashTable<string, string>& ht) {
    for (int i = 0; i < elementCount; ++i) {
        stringstream ss(elements[i]);
        string key;
        string value;
        if (ss >> key >> value) {
            ht.insert(key, value);
        } else {
            cerr << "Ошибка формата данных в массиве." << endl;
        }
    }
}

// Функция для преобразования хеш-таблицы в массив строк
void convertHashTableToArray(const HashTable<string, string>& ht, string elements[], int& elementCount) {
    elementCount = 0;
    for (size_t i = 0; i < ht.getSize(); ++i) {
        auto current = ht.getNodeAtIndex(i);
        while (current != nullptr) {
            stringstream ss;
            ss << current->key << " " << current->value;
            elements[elementCount++] = ss.str();
            current = current->next;
        }
    }
}

int main(int argc, char** argv) {
    int option;
    string filename;
    string query;

    while ((option = getopt(argc, argv, "f:q:")) != -1) {
        switch (option) {
            case 'f':
                filename = optarg;
                break;
            case 'q':
                query = optarg;
                break;
            default:
                cerr << "Некорректные аргументы" << endl;
                return 1;
        }
    }

    // Загрузка данных из файла
    Data data = loadData(filename);

    // Парсинг запроса
    istringstream iss(query);
    string command;
    string structName;
    string item;
    int index;
    string key;
    string value;

    iss >> command >> structName;

    data.name = structName;

    if (command == "QPUSH") {
        iss >> item;
        Queue<string> myQueue;
        copyElementsToQueue(myQueue, data.elements, data.elementCount);
        myQueue.push(item); // Добавляем элемент
        data.elementCount = 0;
        copyElementsFromQueue(myQueue, data.elements, data.elementCount);
        saveData(filename, data); // Сохраняем обновленные данные
        cout << item << endl;
    } else if (command == "QPOP") {
        Queue<string> myQueue;
        copyElementsToQueue(myQueue, data.elements, data.elementCount);
        if (!myQueue.isEmpty()) {
            myQueue.pop(); // Удаляем элемент
            data.elementCount = 0;
            copyElementsFromQueue(myQueue, data.elements, data.elementCount);
            saveData(filename, data);
            cout << "Элемент удален." << endl;
        } else {
            cerr << "Очередь пуста. Невозможно удалить элемент." << endl;
        }
    } else if (command == "QTOP") {
        Queue<string> myQueue;
        copyElementsToQueue(myQueue, data.elements, data.elementCount);
        if (!myQueue.isEmpty()) {
            cout << "Начальный элемент: " << myQueue.peek() << endl;
        } else {
            cerr << "Очередь пуста. Нет начального элемента." << endl;
        }
    } else if (command == "QPRINT") {
        Queue<string> myQueue;
        copyElementsToQueue(myQueue, data.elements, data.elementCount);
        myQueue.display(); // Вывод элементов стека
    } else if (command == "SPUSH") {
        iss >> item;
        Stack<string> myStack;
        copyElementsToStack(myStack, data.elements, data.elementCount);
        myStack.push(item); // Добавляем элемент
        data.elementCount = 0;
        copyElementsFromStack(myStack, data.elements, data.elementCount);
        saveData(filename, data); // Сохраняем обновленные данные
        cout << item << endl;
    } else if (command == "SPOP") {
        Stack<string> myStack;
        copyElementsToStack(myStack, data.elements, data.elementCount);
        if (!myStack.isEmpty()) {
            myStack.pop(); // Удаляем элемент
            data.elementCount = 0;
            copyElementsFromStack(myStack, data.elements, data.elementCount);
            saveData(filename, data);
            cout << "Элемент удален." << endl;
        } else {
            cerr << "Стек пуст. Невозможно удалить элемент." << endl;
        }
    } else if (command == "STOP") {
        Stack<string> myStack;
        copyElementsToStack(myStack, data.elements, data.elementCount);
        if (!myStack.isEmpty()) {
            cout << "Верхний элемент: " << myStack.top() << endl;
        } else {
            cerr << "Стек пуст. Нет верхнего элемента." << endl;
        }
    } else if (command == "SPRINT") {
        Stack<string> myStack;
        copyElementsToStack(myStack, data.elements, data.elementCount);
        myStack.print(); // Вывод элементов стека
    } else if (command == "FPUSHF") {
        iss >> item;
        forwardList myList;
        copyElementsToList(myList, data.elements, data.elementCount);
        myList.pushFront(item); // Добавляем элемент в начало
        data.elementCount = 0;
        copyElementsFromList(myList, data.elements, data.elementCount);
        saveData(filename, data); // Сохраняем обновленные данные
        cout << item << endl;
    } else if (command == "FPUSHB") {
        iss >> item;
        forwardList myList;
        copyElementsToList(myList, data.elements, data.elementCount);
        myList.pushBack(item); // Добавляем элемент в конец
        data.elementCount = 0;
        copyElementsFromList(myList, data.elements, data.elementCount);
        saveData(filename, data);
        cout << item << endl;
    } else if (command == "FREM") {
        iss >> item;
        forwardList myList;
        copyElementsToList(myList, data.elements, data.elementCount);
        if (myList.remove(item)) { // Проверяем, был ли удален элемент
            data.elementCount = 0;
            copyElementsFromList(myList, data.elements, data.elementCount);
            saveData(filename, data);
            cout << "Элемент удален." << endl;
        } else {
            cerr << "Ошибка: элемент " << item << " не найден." << endl;
        }
    } else if (command == "FREMF") {
        forwardList myList;
        copyElementsToList(myList, data.elements, data.elementCount);
        if (myList.removeFirst()){ // Удаляем первый элемент
            data.elementCount = 0;
            copyElementsFromList(myList, data.elements, data.elementCount);
            saveData(filename, data);
            cout << "Первый элемент удален." << endl;
        } else{
            cerr << "Ошибка: список пуст." << endl;
        }
    } else if (command == "FREML") {
        forwardList myList;
        copyElementsToList(myList, data.elements, data.elementCount);
        if (myList.removeLast()){ // Удаляем последний элемент
            data.elementCount = 0;
            copyElementsFromList(myList, data.elements, data.elementCount);
            saveData(filename, data);
            cout << "Последний элемент удален." << endl;
        } else{
            cerr << "Ошибка: список пуст." << endl;
        }
    } else if (command == "FFIND") {
        iss >> item;
        forwardList myList;
        copyElementsToList(myList, data.elements, data.elementCount);
        Node* foundNode = myList.find(item);
        if (foundNode != nullptr) {
            cout << "Элемент найден: " << foundNode->data << endl;
        } else {
            cout << "Элемент не найден." << endl;
        }
    } else if (command == "FPRINT") {
        forwardList myList;
        copyElementsToList(myList, data.elements, data.elementCount);
        myList.print(); // Выводим элементы списка
    } else if (command == "DPUSHF") {
        iss >> item;
        DoublyLinkedList myList;
        copyElementsToDoubleList(myList, data.elements, data.elementCount);
        myList.pushFront(item);
        data.elementCount = 0;
        copyElementsFromDoubleList(myList, data.elements, data.elementCount);
        saveData(filename, data);
        cout << item << endl;
    } else if (command == "DPUSHB") {
        iss >> item;
        DoublyLinkedList myList;
        copyElementsToDoubleList(myList, data.elements, data.elementCount);
        myList.pushBack(item);
        data.elementCount = 0;
        copyElementsFromDoubleList(myList, data.elements, data.elementCount);
        saveData(filename, data);
        cout << item << endl;
    } else if (command == "DREM") {
        iss >> item;
        DoublyLinkedList myList;
        copyElementsToDoubleList(myList, data.elements, data.elementCount);
        if (myList.remove(item)){
            data.elementCount = 0;
            copyElementsFromDoubleList(myList, data.elements, data.elementCount);
            saveData(filename, data);
            cout << "Элемент удален." << endl;
        } else {
            cerr << "Ошибка: элемент " << item << " не найден." << endl;
        }
    } else if (command == "DPOPF") {
        DoublyLinkedList myList;
        copyElementsToDoubleList(myList, data.elements, data.elementCount);
        if (myList.popFront()){
            data.elementCount = 0;
            copyElementsFromDoubleList(myList, data.elements, data.elementCount);
            saveData(filename, data);
            cout << "Первый элемент удален." << endl;
        } else{
            cerr << "Ошибка: список пуст." << endl;
        }
    } else if (command == "DPOPB") {
        DoublyLinkedList myList;
        copyElementsToDoubleList(myList, data.elements, data.elementCount);
        if (myList.popBack()){
            data.elementCount = 0;
            copyElementsFromDoubleList(myList, data.elements, data.elementCount);
            saveData(filename, data);
            cout << "Последний элемент удален." << endl;
        } else {
            cerr << "Ошибка: список пуст." << endl;
        }
    } else if (command == "DFIND") {
        iss >> item;
        DoublyLinkedList myList;
        copyElementsToDoubleList(myList, data.elements, data.elementCount);
        NodeDouble* foundNode = myList.find(item);
        if (foundNode != nullptr) {
            cout << "Элемент найден: " << foundNode->data << endl;
        } else {
            cout << "Элемент не найден." << endl;
        }
    } else if (command == "DPRINT") {
        DoublyLinkedList myList;
        copyElementsToDoubleList(myList, data.elements, data.elementCount);
        myList.print();
    } else if (command == "MPUSH") {
        iss >> item;
        MyArray<string> myArray;
        CopyElementsToArray(myArray, data.elements, data.elementCount);
        myArray.push_back(item);
        data.elementCount = 0;
        CopyElementsFromArray(myArray, data.elements, data.elementCount);
        saveData(filename, data);
        cout << item << endl;
    } else if (command == "MINS") {
        iss >> item >> index;
        MyArray<string> myArray;
        CopyElementsToArray(myArray, data.elements, data.elementCount);
        if (index >= 0 && index <= myArray.length()) {
            myArray.insert(index, item); // Вставляем элемент
            data.elementCount = 0;
            CopyElementsFromArray(myArray, data.elements, data.elementCount);
            saveData(filename, data);
            cout << item << endl;
        } else {
            cerr << "Некорректный индекс" << endl;
        }
    } else if (command == "MGET") {
        iss >> index;
        MyArray<string> myArray;
        CopyElementsToArray(myArray, data.elements, data.elementCount);
        if (index >= 0 && index < myArray.length()) {
            cout << myArray[index] << endl; // Вывод элемента
        } else {
            cerr << "Некорректный индекс" << endl;
        }
    } else if (command == "MDEL") {
        iss >> index;
        MyArray<string> myArray;
        CopyElementsToArray(myArray, data.elements, data.elementCount);
        if (index >= 0 && index < myArray.length()) {
            myArray.erase(index);
            data.elementCount = 0;
            CopyElementsFromArray(myArray, data.elements, data.elementCount);
            saveData(filename, data);
            cout << "Элемент удален." << endl;
        } else {
            cerr << "Некорректный индекс" << endl;
        }
    } else if (command == "MREP") {
        iss >> item >> index;
        MyArray<string> myArray;
        CopyElementsToArray(myArray, data.elements, data.elementCount);
        if (index >= 0 && index < myArray.length()) {
            myArray.replace(index, item);
            data.elementCount = 0;
            CopyElementsFromArray(myArray, data.elements, data.elementCount);
            saveData(filename, data);
            cout << item << endl;
        } else {
            cerr << "Некорректный индекс" << endl;
        }
    } else if (command == "MLEN") {
        MyArray<string> myArray;
        CopyElementsToArray(myArray, data.elements, data.elementCount);
        cout << myArray.length() << endl;
    } else if (command == "MPRINT") {
        MyArray<string> myArray;
        CopyElementsToArray(myArray, data.elements, data.elementCount);
        cout << myArray << endl;
    } else if (command == "HSET") {
        iss >> key >> value;
        HashTable<string, string> ht(10); // Создаем хеш-таблицу
        convertArrayToHashTable(data.elements, data.elementCount, ht);
        ht.insert(key, value);
        data.elementCount = 0;
        convertHashTableToArray(ht, data.elements, data.elementCount);
        saveData(filename, data);
        cout << "Элемент добавлен." << endl;
    } else if (command == "HGET") {
        iss >> key;
        HashTable<string, string> ht(10);
        convertArrayToHashTable(data.elements, data.elementCount, ht);
        try {
            string getValue = ht.get(key);
            cout << "Значение: " << getValue << endl;
        } catch (out_of_range& e) {
            cerr << "Ошибка: Ключ не найден" << endl;
        }
    } else if (command == "HDEL") {
        iss >> key;
        HashTable<string, string> ht(10);
        convertArrayToHashTable(data.elements, data.elementCount, ht);
        ht.remove(key);
        data.elementCount = 0;
        convertHashTableToArray(ht, data.elements, data.elementCount);
        saveData(filename, data);
        cout << "Элемент удален." << endl;
    } else if (command == "HPRINT") {
        HashTable<string, string> ht(10);
        convertArrayToHashTable(data.elements, data.elementCount, ht);
        ht.print();
    } else if (command == "CLEAR") {
        clearFile(filename);
    } else {
        cerr << "Неизвестная команда" << endl;
    }
    return 0;
}


