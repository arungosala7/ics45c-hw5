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


Node* copy(Node* head) {
    Node* new_head = nullptr;
    Node* tail = nullptr;

    for (Node* cur = head; cur != nullptr; cur = cur->next) {
        Node* node = new Node{cur->data, nullptr};

        if (new_head == nullptr) {
            new_head = node;
        } else {
            tail->next = node;
        }

        tail = node;
    }

    return new_head;
}

int compare(Node* lhs, Node* rhs) {
    while (lhs != nullptr && rhs != nullptr) {
        if (lhs->data != rhs->data) {
            return lhs->data - rhs->data;
        }

        lhs = lhs->next;
        rhs = rhs->next;
    }

    if (lhs == nullptr && rhs == nullptr) {
        return 0;
    }

    return lhs == nullptr ? -1 : 1;
}

int compare(Node* lhs, Node* rhs, int n) {
    while (n > 0 && lhs != nullptr && rhs != nullptr) {
        if (lhs->data != rhs->data) {
            return lhs->data - rhs->data;
        }

        lhs = lhs->next;
        rhs = rhs->next;
        --n;
    }

    if (n <= 0 || (lhs == nullptr && rhs == nullptr)) {
        return 0;
    }

    return lhs == nullptr ? -1 : 1;
}

Node* reverse(Node* head) {
    Node* result = nullptr;

    for (Node* cur = head; cur != nullptr; cur = cur->next) {
        result = new Node{cur->data, result};
    }

    return result;
}

Node* append(Node* lhs, Node* rhs) {
    Node* left = copy(lhs);
    Node* right = copy(rhs);

    if (left == nullptr) {
        return right;
    }

    last(left)->next = right;
    return left;
}

Node* last(Node* head) {
    while (head->next != nullptr) {
        head = head->next;
    }

    return head;
}

int index(Node* head, Node* node) {
    int result = 0;

    while (head != node) {
        head = head->next;
        ++result;
    }

    return result;
}

Node* find_char(Node* head, char c) {
    for (Node* cur = head; cur != nullptr; cur = cur->next) {
        if (cur->data == c) {
            return cur;
        }
    }

    return nullptr;
}

Node* find_list(Node* haystack, Node* needle) {
    if (needle == nullptr) {
        return haystack;
    }

    int needle_length = length(needle);

    for (Node* cur = haystack; cur != nullptr; cur = cur->next) {
        if (compare(cur, needle, needle_length) == 0) {
            return cur;
        }
    }

    return nullptr;
}

Node* nth(Node* head, int n) {
    if (n < 0) {
        return nullptr;
    }

    while (head != nullptr && n > 0) {
        head = head->next;
        --n;
    }

    return head;
}

}