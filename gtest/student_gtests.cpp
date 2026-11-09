#include <gtest/gtest.h>

#include "list.hpp"
#include <sstream>
#include <string>

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

static std::string to_text(list::Node* head) {
    std::stringstream out;
    list::print(out, head);
    return out.str();
}

static bool shares_nodes(list::Node* a, list::Node* b) {
    for (list::Node* x = a; x != nullptr; x = x->next) {
        for (list::Node* y = b; y != nullptr; y = y->next) {
            if (x == y) {
                return true;
            }
        }
    }

    return false;
}

TEST(ListTests, CopyEmpty) {
    EXPECT_EQ(list::copy(nullptr), nullptr);
}

TEST(ListTests, CopyOneNode) {
    list::Node* head = list::from_string("a");
    list::Node* result = list::copy(head);
    EXPECT_EQ(to_text(result), "a");
    EXPECT_FALSE(shares_nodes(head, result));
    list::free(head);
    list::free(result);
}

TEST(ListTests, CopyManyNodes) {
    list::Node* head = list::from_string("hello");
    list::Node* result = list::copy(head);
    EXPECT_EQ(to_text(result), "hello");
    EXPECT_EQ(to_text(head), "hello");
    EXPECT_FALSE(shares_nodes(head, result));
    list::free(head);
    list::free(result);
}

TEST(ListTests, CompareBothEmpty) {
    EXPECT_EQ(list::compare(nullptr, nullptr), 0);
}

TEST(ListTests, CompareOneEmpty) {
    list::Node* head = list::from_string("a");
    EXPECT_LT(list::compare(nullptr, head), 0);
    EXPECT_GT(list::compare(head, nullptr), 0);
    list::free(head);
}

TEST(ListTests, CompareEqual) {
    list::Node* a = list::from_string("abc");
    list::Node* b = list::from_string("abc");
    EXPECT_EQ(list::compare(a, b), 0);
    list::free(a);
    list::free(b);
}

TEST(ListTests, CompareFirstCharDiffers) {
    list::Node* a = list::from_string("abc");
    list::Node* b = list::from_string("xbc");
    EXPECT_LT(list::compare(a, b), 0);
    EXPECT_GT(list::compare(b, a), 0);
    list::free(a);
    list::free(b);
}

TEST(ListTests, CompareLastCharDiffers) {
    list::Node* a = list::from_string("abc");
    list::Node* b = list::from_string("abd");
    EXPECT_LT(list::compare(a, b), 0);
    EXPECT_GT(list::compare(b, a), 0);
    list::free(a);
    list::free(b);
}

TEST(ListTests, ComparePrefixIsSmaller) {
    list::Node* a = list::from_string("ab");
    list::Node* b = list::from_string("abc");
    EXPECT_LT(list::compare(a, b), 0);
    EXPECT_GT(list::compare(b, a), 0);
    list::free(a);
    list::free(b);
}

TEST(ListTests, CompareNZero) {
    list::Node* a = list::from_string("abc");
    list::Node* b = list::from_string("xyz");
    EXPECT_EQ(list::compare(a, b, 0), 0);
    EXPECT_EQ(list::compare(nullptr, nullptr, 0), 0);
    EXPECT_EQ(list::compare(a, nullptr, 0), 0);
    list::free(a);
    list::free(b);
}

TEST(ListTests, CompareNStopsAtN) {
    list::Node* a = list::from_string("abcd");
    list::Node* b = list::from_string("abxy");
    EXPECT_EQ(list::compare(a, b, 2), 0);
    EXPECT_LT(list::compare(a, b, 3), 0);
    EXPECT_GT(list::compare(b, a, 3), 0);
    list::free(a);
    list::free(b);
}

TEST(ListTests, CompareNLargerThanLists) {
    list::Node* a = list::from_string("abc");
    list::Node* b = list::from_string("abc");
    EXPECT_EQ(list::compare(a, b, 10), 0);
    list::free(a);
    list::free(b);
}

TEST(ListTests, CompareNOneListEndsFirst) {
    list::Node* a = list::from_string("ab");
    list::Node* b = list::from_string("abc");
    EXPECT_EQ(list::compare(a, b, 2), 0);
    EXPECT_LT(list::compare(a, b, 3), 0);
    EXPECT_GT(list::compare(b, a, 3), 0);
    list::free(a);
    list::free(b);
}

TEST(ListTests, CompareNOneEmpty) {
    list::Node* head = list::from_string("a");
    EXPECT_LT(list::compare(nullptr, head, 1), 0);
    EXPECT_GT(list::compare(head, nullptr, 1), 0);
    EXPECT_EQ(list::compare(nullptr, nullptr, 5), 0);
    list::free(head);
}

TEST(ListTests, ReverseEmpty) {
    EXPECT_EQ(list::reverse(nullptr), nullptr);
}

TEST(ListTests, ReverseOneNode) {
    list::Node* head = list::from_string("a");
    list::Node* result = list::reverse(head);
    EXPECT_EQ(to_text(result), "a");
    EXPECT_FALSE(shares_nodes(head, result));
    list::free(head);
    list::free(result);
}

TEST(ListTests, ReverseTwoNodes) {
    list::Node* head = list::from_string("ab");
    list::Node* result = list::reverse(head);
    EXPECT_EQ(to_text(result), "ba");
    EXPECT_EQ(to_text(head), "ab");
    EXPECT_FALSE(shares_nodes(head, result));
    list::free(head);
    list::free(result);
}

TEST(ListTests, ReverseManyNodes) {
    list::Node* head = list::from_string("hello");
    list::Node* result = list::reverse(head);
    EXPECT_EQ(to_text(result), "olleh");
    EXPECT_EQ(to_text(head), "hello");
    EXPECT_FALSE(shares_nodes(head, result));
    list::free(head);
    list::free(result);
}

TEST(ListTests, AppendBothEmpty) {
    EXPECT_EQ(list::append(nullptr, nullptr), nullptr);
}

TEST(ListTests, AppendLeftEmpty) {
    list::Node* rhs = list::from_string("abc");
    list::Node* result = list::append(nullptr, rhs);
    EXPECT_EQ(to_text(result), "abc");
    EXPECT_FALSE(shares_nodes(rhs, result));
    list::free(rhs);
    list::free(result);
}

TEST(ListTests, AppendRightEmpty) {
    list::Node* lhs = list::from_string("abc");
    list::Node* result = list::append(lhs, nullptr);
    EXPECT_EQ(to_text(result), "abc");
    EXPECT_FALSE(shares_nodes(lhs, result));
    list::free(lhs);
    list::free(result);
}

TEST(ListTests, AppendBothNonEmpty) {
    list::Node* lhs = list::from_string("foo");
    list::Node* rhs = list::from_string("bar");
    list::Node* result = list::append(lhs, rhs);
    EXPECT_EQ(to_text(result), "foobar");
    EXPECT_EQ(to_text(lhs), "foo");
    EXPECT_EQ(to_text(rhs), "bar");
    EXPECT_FALSE(shares_nodes(lhs, result));
    EXPECT_FALSE(shares_nodes(rhs, result));
    list::free(lhs);
    list::free(rhs);
    list::free(result);
}

TEST(ListTests, LastOneNode) {
    list::Node* head = list::from_string("a");
    EXPECT_EQ(list::last(head), head);
    list::free(head);
}

TEST(ListTests, LastTwoNodes) {
    list::Node* head = list::from_string("ab");
    EXPECT_EQ(list::last(head), head->next);
    list::free(head);
}

TEST(ListTests, LastManyNodes) {
    list::Node* head = list::from_string("abc");
    EXPECT_EQ(list::last(head), head->next->next);
    list::free(head);
}
TEST(ListTests, IndexFirstNode) {
    list::Node* head = list::from_string("abc");
    EXPECT_EQ(list::index(head, head), 0);
    list::free(head);
}

TEST(ListTests, IndexMiddleNode) {
    list::Node* head = list::from_string("abc");
    EXPECT_EQ(list::index(head, head->next), 1);
    list::free(head);
}

TEST(ListTests, IndexLastNode) {
    list::Node* head = list::from_string("abc");
    EXPECT_EQ(list::index(head, head->next->next), 2);
    list::free(head);
}

TEST(ListTests, IndexRepeatedCharsUsesNode) {
    list::Node* head = list::from_string("aaa");
    EXPECT_EQ(list::index(head, head->next->next), 2);
    list::free(head);
}

TEST(ListTests, FindCharEmpty) {
    EXPECT_EQ(list::find_char(nullptr, 'a'), nullptr);
}

TEST(ListTests, FindCharFirstNode) {
    list::Node* head = list::from_string("abc");
    EXPECT_EQ(list::find_char(head, 'a'), head);
    list::free(head);
}

TEST(ListTests, FindCharMiddleNode) {
    list::Node* head = list::from_string("abc");
    EXPECT_EQ(list::find_char(head, 'b'), head->next);
    list::free(head);
}

TEST(ListTests, FindCharLastNode) {
    list::Node* head = list::from_string("abc");
    EXPECT_EQ(list::find_char(head, 'c'), head->next->next);
    list::free(head);
}

TEST(ListTests, FindCharReturnsFirstMatch) {
    list::Node* head = list::from_string("abab");
    EXPECT_EQ(list::find_char(head, 'b'), head->next);
    list::free(head);
}

TEST(ListTests, FindCharMissing) {
    list::Node* head = list::from_string("abc");
    EXPECT_EQ(list::find_char(head, 'z'), nullptr);
    list::free(head);
}

TEST(ListTests, FindCharNullCharacter) {
    list::Node* head = list::from_string("abc");
    EXPECT_EQ(list::find_char(head, '\0'), nullptr);
    list::free(head);
}

TEST(ListTests, FindListBothEmpty) {
    EXPECT_EQ(list::find_list(nullptr, nullptr), nullptr);
}

TEST(ListTests, FindListEmptyNeedle) {
    list::Node* haystack = list::from_string("abc");
    EXPECT_EQ(list::find_list(haystack, nullptr), haystack);
    list::free(haystack);
}

TEST(ListTests, FindListEmptyHaystack) {
    list::Node* needle = list::from_string("a");
    EXPECT_EQ(list::find_list(nullptr, needle), nullptr);
    list::free(needle);
}

TEST(ListTests, FindListExactMatch) {
    list::Node* haystack = list::from_string("abc");
    list::Node* needle = list::from_string("abc");
    EXPECT_EQ(list::find_list(haystack, needle), haystack);
    list::free(haystack);
    list::free(needle);
}

TEST(ListTests, FindListAtStart) {
    list::Node* haystack = list::from_string("abcd");
    list::Node* needle = list::from_string("ab");
    EXPECT_EQ(list::find_list(haystack, needle), haystack);
    list::free(haystack);
    list::free(needle);
}

TEST(ListTests, FindListInMiddle) {
    list::Node* haystack = list::from_string("abcd");
    list::Node* needle = list::from_string("bc");
    EXPECT_EQ(list::find_list(haystack, needle), haystack->next);
    list::free(haystack);
    list::free(needle);
}

TEST(ListTests, FindListAtEnd) {
    list::Node* haystack = list::from_string("abcd");
    list::Node* needle = list::from_string("cd");
    EXPECT_EQ(list::find_list(haystack, needle), haystack->next->next);
    list::free(haystack);
    list::free(needle);
}

TEST(ListTests, FindListFailsPartwayThenMatches) {
    list::Node* haystack = list::from_string("aaab");
    list::Node* needle = list::from_string("aab");
    EXPECT_EQ(list::find_list(haystack, needle), haystack->next);
    list::free(haystack);
    list::free(needle);
}

TEST(ListTests, FindListReturnsFirstMatch) {
    list::Node* haystack = list::from_string("abab");
    list::Node* needle = list::from_string("ab");
    EXPECT_EQ(list::find_list(haystack, needle), haystack);
    list::free(haystack);
    list::free(needle);
}

TEST(ListTests, FindListNeedleRunsPastEnd) {
    list::Node* haystack = list::from_string("abc");
    list::Node* needle = list::from_string("cd");
    EXPECT_EQ(list::find_list(haystack, needle), nullptr);
    list::free(haystack);
    list::free(needle);
}

TEST(ListTests, FindListNeedleLongerThanHaystack) {
    list::Node* haystack = list::from_string("ab");
    list::Node* needle = list::from_string("abc");
    EXPECT_EQ(list::find_list(haystack, needle), nullptr);
    list::free(haystack);
    list::free(needle);
}

TEST(ListTests, FindListMissing) {
    list::Node* haystack = list::from_string("abc");
    list::Node* needle = list::from_string("xy");
    EXPECT_EQ(list::find_list(haystack, needle), nullptr);
    list::free(haystack);
    list::free(needle);
}

TEST(ListTests, NthFirstNode) {
    list::Node* head = list::from_string("abc");
    EXPECT_EQ(list::nth(head, 0), head);
    list::free(head);
}

TEST(ListTests, NthMiddleNode) {
    list::Node* head = list::from_string("abc");
    EXPECT_EQ(list::nth(head, 1), head->next);
    list::free(head);
}

TEST(ListTests, NthLastNode) {
    list::Node* head = list::from_string("abc");
    EXPECT_EQ(list::nth(head, 2), head->next->next);
    list::free(head);
}

TEST(ListTests, NthOnePastEnd) {
    list::Node* head = list::from_string("abc");
    EXPECT_EQ(list::nth(head, 3), nullptr);
    list::free(head);
}

TEST(ListTests, LongListWorks) {
    std::string text(5000, 'a');
    list::Node* head = list::from_string(text.c_str());
    list::Node* copied = list::copy(head);
    list::Node* reversed = list::reverse(head);
    EXPECT_EQ(list::length(head), 5000);
    EXPECT_EQ(list::length(copied), 5000);
    EXPECT_EQ(list::length(reversed), 5000);
    list::free(head);
    list::free(copied);
    list::free(reversed);
}