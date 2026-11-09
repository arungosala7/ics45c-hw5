#include "string.hpp"

#include <iostream>

String::String(const char* s) : head(list::from_string(s)) {}

String::String(const String& s) : head(list::copy(s.head)) {}

String::String(list::Node* node) : head(node) {}

void String::swap(String& s) {
    list::Node* temp = head;
    head = s.head;
    s.head = temp;
}

String& String::operator=(const String& s) {
    if (this != &s) {
        list::Node* copied = list::copy(s.head);
        list::free(head);
        head = copied;
    }

    return *this;
}

bool String::in_bounds(int index) const {
    return index >= 0 && index < size();
}

char String::operator[](int index) const {
    list::Node* node = list::nth(head, index);
    return node == nullptr ? '\0' : node->data;
}

int String::size() const {
    return list::length(head);
}

String String::reverse() const {
    return String(list::reverse(head));
}

int String::indexOf(char c) const {
    list::Node* found = list::find_char(head, c);
    return found == nullptr ? -1 : list::index(head, found);
}

int String::indexOf(const String& s) const {
    list::Node* found = list::find_list(head, s.head);
    return found == nullptr ? -1 : list::index(head, found);
}

bool String::operator==(const String& s) const {
    return list::compare(head, s.head) == 0;
}

std::strong_ordering String::operator<=>(const String& s) const {
    return list::compare(head, s.head) <=> 0;
}

String String::operator+(const String& s) const {
    return String(list::append(head, s.head));
}

String& String::operator+=(const String& s) {
    list::Node* added = list::copy(s.head);

    if (head == nullptr) {
        head = added;
    } else {
        list::last(head)->next = added;
    }

    return *this;
}

void String::print(std::ostream& out) const {
    list::print(out, head);
}

void String::read(std::istream& in) {
    char buffer[1024] = "";
    in >> buffer;

    list::Node* word = list::from_string(buffer);
    list::free(head);
    head = word;
}

std::ostream& operator<<(std::ostream& out, const String& s) {
    s.print(out);
    return out;
}

std::istream& operator>>(std::istream& in, String& s) {
    s.read(in);
    return in;
}

String::~String() {
    list::free(head);
}

String::String(String&& s) : head(s.head) {
    s.head = nullptr;
}