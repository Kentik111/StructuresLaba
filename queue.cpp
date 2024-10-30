#include "header.h"

template <typename T>
Queue<T>::Queue() : front(nullptr), rear(nullptr) {}

template <typename T>
Queue<T>::~Queue() {
    while (!isEmpty()) {
        pop();
    }
}

template <typename T>
bool Queue<T>::isEmpty() const {
    return front == nullptr;
}

template <typename T>
void Queue<T>::push(T value) {
    Node* newNode = new Node(value);
    if (isEmpty()) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

template <typename T>
void Queue<T>::pop() {
    if (isEmpty()) {
        cerr << "Очередь пуста. Невозможно удалить элемент." << endl;
        return;
    }
    Node* temp = front;
    front = front->next;
    delete temp;
    if (front == nullptr) {
        rear = nullptr;
    }
}

template <typename T>
T Queue<T>::peek() const {
    if (isEmpty()) {
        throw runtime_error("Очередь пуста. Невозможно прочитать элемент.");
    }
    return front->data;
}

template <typename T>
void Queue<T>::display() const {
    Node* current = front;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}
