#include "list.hpp"

#include <iostream>

namespace list {

Node* from_string(const char* s) {
    Node* head = nullptr;
    Node* tail = nullptr;

    for (; *s != '\0'; ++s) {
        Node* node = new Node{*s, nullptr};

        if (head == nullptr) {
            head = node;
        } else {
            tail->next = node;
        }

        tail = node;
    }

    return head;
}

void free(Node* head) {
    while (head != nullptr) {
        Node* next = head->next;
        delete head;
        head = next;
    }
}

void print(std::ostream& out, Node* head) {
    for (Node* cur = head; cur != nullptr; cur = cur->next) {
        out << cur->data;
    }
}

int length(Node* head) {
    int count = 0;

    for (Node* cur = head; cur != nullptr; cur = cur->next) {
        ++count;
    }

    return count;
}

}  