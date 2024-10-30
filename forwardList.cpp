#include "header.h"


// Конструктор
forwardList::forwardList() {
    head = nullptr;
}


void forwardList::pushFront(string data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = head;
    head = newNode;
}


void forwardList::pushBack(string data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
        return;
    }

    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = newNode;
}


bool forwardList::removeFirst() {
    if (head == nullptr) {
        return false;
    }
    Node* temp = head;
    head = head->next;
    delete temp;
    return true;
}


bool forwardList::removeLast() {
    if (head == nullptr) {
        return false;
    }
    if (head->next == nullptr) {
        removeFirst();
        return true;
    }

    Node* current = head;
    while (current->next->next != nullptr) {
        current = current->next;
    }

    delete current->next;
    current->next = nullptr;
    return true;
}


bool forwardList::remove(string data) {
    if (head == nullptr) {
        return false;
    }

    if (head->data == data) {
        removeFirst();
        return true;
    }

    Node* current = head;
    while (current->next != nullptr && current->next->data != data) {
        current = current->next;
    }

    if (current->next != nullptr) {
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
        return true;
    }
    return false;
}


Node* forwardList::find(string data) {
    Node* current = head;
    while (current != nullptr && current->data != data) {
        current = current->next;
    }
    return current;
}

Node* forwardList::getHead() {
    return head;
}

void forwardList::print() {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}



