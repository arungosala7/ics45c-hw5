#include <gtest/gtest.h>

#include "list.hpp"

using namespace std;
using list::Node;

TEST(ListTests, FromStringBasic) {
    Node* const foo_list_head = list::from_string("foo");
    Node* foo_list = foo_list_head;

    EXPECT_EQ(foo_list->data, 'f');
    // ASSERT instead of EXPECT means: end the test here if this fails, do not try to continue
    // running. This is useful to prevent early crashes.
    ASSERT_NE(foo_list->next, nullptr);

    foo_list = foo_list->next;
    EXPECT_EQ(foo_list->data, 'o');
    ASSERT_NE(foo_list->next, nullptr);

    foo_list = foo_list->next;
    EXPECT_EQ(foo_list->data, 'o');
    ASSERT_EQ(foo_list->next, nullptr);

    list::free(foo_list_head);
}

TEST(ListTests, Length) {
    Node* const head = list::from_string("foo");
    EXPECT_EQ(list::length(head), 3);
    list::free(head);
}

// Add remaining tests below. All tests should follow
// the format of `TEST(ListTests, <TestName>){}`.

TEST(ListTests, FromStringEmpty) {
    list::Node* head = list::from_string("");
    EXPECT_EQ(head, nullptr);
}

TEST(ListTests, FromStringOneNode) {
    list::Node* head = list::from_string("a");
    ASSERT_NE(head, nullptr);
    EXPECT_EQ(head->data, 'a');
    EXPECT_EQ(head->next, nullptr);
    list::free(head);
}

TEST(ListTests, FromStringTwoNodes) {
    list::Node* head = list::from_string("ab");
    ASSERT_NE(head, nullptr);
    ASSERT_NE(head->next, nullptr);
    EXPECT_EQ(head->data, 'a');
    EXPECT_EQ(head->next->data, 'b');
    EXPECT_EQ(head->next->next, nullptr);
    list::free(head);
}

TEST(ListTests, FromStringKeepsOrder) {
    const char* text = "hello";
    list::Node* head = list::from_string(text);
    list::Node* cur = head;

    for (int i = 0; i < 5; ++i) {
        ASSERT_NE(cur, nullptr);
        EXPECT_EQ(cur->data, text[i]);
        cur = cur->next;
    }

    EXPECT_EQ(cur, nullptr);
    list::free(head);
}

TEST(ListTests, LengthEmpty) {
    EXPECT_EQ(list::length(nullptr), 0);
}

TEST(ListTests, LengthOneNode) {
    list::Node* head = list::from_string("a");
    EXPECT_EQ(list::length(head), 1);
    list::free(head);
}

TEST(ListTests, LengthTwoNodes) {
    list::Node* head = list::from_string("ab");
    EXPECT_EQ(list::length(head), 2);
    list::free(head);
}

TEST(ListTests, LengthManyNodes) {
    list::Node* head = list::from_string("hello world");
    EXPECT_EQ(list::length(head), 11);
    list::free(head);
}

TEST(ListTests, PrintEmpty) {
    std::stringstream out;
    list::print(out, nullptr);
    EXPECT_EQ(out.str(), "");
}

TEST(ListTests, PrintOneNode) {
    list::Node* head = list::from_string("a");
    std::stringstream out;
    list::print(out, head);
    EXPECT_EQ(out.str(), "a");
    list::free(head);
}

TEST(ListTests, PrintManyNodes) {
    list::Node* head = list::from_string("hello");
    std::stringstream out;
    list::print(out, head);
    EXPECT_EQ(out.str(), "hello");
    list::free(head);
}

TEST(ListTests, FreeEmpty) {
    list::free(nullptr);
}
