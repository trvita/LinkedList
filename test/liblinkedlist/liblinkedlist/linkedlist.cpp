#include <algorithm>
#include <gtest/gtest.h>
#include <linkedlist.hpp>
#include <sstream>
#include <string>

using namespace linkedlist;

class LinkedListTest : public ::testing::Test {};

TEST_F(LinkedListTest, DefaultConstructor) {
  LinkedList<int> list;
  EXPECT_EQ(list.size(), 0);
}

TEST_F(LinkedListTest, RangeConstructor) {
  int arr[] = {1, 2, 3};
  LinkedList<int> list(std::begin(arr), std::end(arr));
  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 3);
}

TEST_F(LinkedListTest, InitializerListConstructor) {
  LinkedList<int> list({1, 2, 3});
  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 3);
}

TEST_F(LinkedListTest, CopyConstructor) {
  LinkedList<int> list1;
  list1.push_back(1);
  list1.push_back(2);

  LinkedList<int> list2 = list1;

  EXPECT_EQ(list2.size(), 2);
  EXPECT_EQ(list2.front(), 1);
  EXPECT_EQ(list2.back(), 2);
}

TEST_F(LinkedListTest, MoveConstructor) {
  LinkedList<int> list1;
  list1.push_back(1);
  list1.push_back(2);

  LinkedList<int> list2 = std::move(list1);

  EXPECT_EQ(list1.size(), 0);
  EXPECT_EQ(list2.size(), 2);
  EXPECT_EQ(list2.front(), 1);
  EXPECT_EQ(list2.back(), 2);
}

TEST_F(LinkedListTest, CopyAssignment) {
  LinkedList<int> list1;
  list1.push_back(1);
  list1.push_back(2);

  LinkedList<int> list2;
  list2 = list1;

  EXPECT_EQ(list2.size(), 2);
  EXPECT_EQ(list2.front(), 1);
  EXPECT_EQ(list2.back(), 2);
}

TEST_F(LinkedListTest, MoveAssignment) {
  LinkedList<int> list1;
  list1.push_back(1);
  list1.push_back(2);

  LinkedList<int> list2;
  list2 = std::move(list1);

  EXPECT_EQ(list1.size(), 0);
  EXPECT_EQ(list2.size(), 2);
  EXPECT_EQ(list2.front(), 1);
  EXPECT_EQ(list2.back(), 2);
}

TEST_F(LinkedListTest, FrontEmptyList) {
  LinkedList<int> list;
  EXPECT_THROW(list.front(), std::out_of_range);
}

TEST_F(LinkedListTest, FrontNonEmptyList) {
  LinkedList<int> list;
  list.push_back(1);
  EXPECT_EQ(list.front(), 1);
}

TEST_F(LinkedListTest, ConstFrontEmptyList) {
  const LinkedList<int> list;
  EXPECT_THROW(list.front(), std::out_of_range);
}

TEST_F(LinkedListTest, ConstFrontNonEmptyList) {
  LinkedList<int> list;
  list.push_back(1);
  const LinkedList<int> &constList = list;
  EXPECT_EQ(constList.front(), 1);
}

TEST_F(LinkedListTest, BackEmptyList) {
  LinkedList<int> list;
  EXPECT_THROW(list.back(), std::out_of_range);
}

TEST_F(LinkedListTest, BackNonEmptyList) {
  LinkedList<int> list;
  list.push_back(1);
  EXPECT_EQ(list.back(), 1);
}

TEST_F(LinkedListTest, ConstBackEmptyList) {
  const LinkedList<int> list;
  EXPECT_THROW(list.back(), std::out_of_range);
}

TEST_F(LinkedListTest, ConstBackNonEmptyList) {
  LinkedList<int> list;
  list.push_back(1);
  const LinkedList<int> &constList = list;
  EXPECT_EQ(constList.back(), 1);
}

TEST_F(LinkedListTest, PushFrontLvalue) {
  LinkedList<int> list;
  list.push_front(1);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 1);
}

TEST_F(LinkedListTest, PushFrontRvalue) {
  LinkedList<std::string> list;
  list.push_front("hello");
  EXPECT_EQ(list.front(), "hello");
  EXPECT_EQ(list.back(), "hello");
}

TEST_F(LinkedListTest, PushBackLvalue) {
  LinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 2);
}

TEST_F(LinkedListTest, PushBackRvalue) {
  LinkedList<std::string> list;
  list.push_back("world");
  EXPECT_EQ(list.front(), "world");
  EXPECT_EQ(list.back(), "world");
}
TEST(IteratorTest, IncrementDecrement) {
  LinkedList<int> list{1, 2, 3};

  auto it = list.begin();

  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);

  --it;
  EXPECT_EQ(*it, 1);
}
TEST(IteratorTest, Comparison) {
  LinkedList<int> list;
  list.push_back(1);
  auto it1 = list.begin();
  auto it2 = list.begin();

  EXPECT_EQ(it1, it2);

  ++it1;

  EXPECT_NE(it1, it2);
}
TEST(ConstIteratorTest, IncrementDecrement) {
  LinkedList<int> list{1, 2, 3};

  auto it = list.cbegin();

  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);

  --it;
  EXPECT_EQ(*it, 1);
}

TEST(ConstIteratorTest, Comparison) {
  LinkedList<int> list;
  list.push_back(1);
  auto it1 = list.cbegin();
  auto it2 = list.cbegin();

  EXPECT_EQ(it1, it2);

  ++it1;

  EXPECT_NE(it1, it2);
}

TEST_F(LinkedListTest, IteratorBeginEnd) {
  LinkedList<int> list{1, 2, 3};

  auto it = list.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(it, list.end());
}

TEST_F(LinkedListTest, ConstIteratorBeginEnd) {
  LinkedList<int> list{1, 2, 3};

  const LinkedList<int> constList = list;
  auto it = constList.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(it, constList.end());
}

TEST_F(LinkedListTest, ReverseIteratorBeginEnd) {
  LinkedList<int> list{1, 2, 3};

  auto it = list.rbegin();
  EXPECT_EQ(*it, 3);

  ++it;
  EXPECT_EQ(*it, 2);

  ++it;
  EXPECT_EQ(*it, 1);

  ++it;
  EXPECT_EQ(it, list.rend());
}

TEST_F(LinkedListTest, ConstReverseIteratorBeginEnd) {
  LinkedList<int> list{1, 2, 3};

  const LinkedList<int> constList = list;
  auto it = constList.rbegin();
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(it, constList.rend());
}

TEST_F(LinkedListTest, FindIterator) {
  LinkedList<int> list{1, 2, 3, 4, 5, 6};
  auto it = std::find(list.begin(), list.end(), 4);
  EXPECT_NE(it, list.end());
  EXPECT_EQ(*it, 4);
}

TEST_F(LinkedListTest, FindConstIterator) {
  LinkedList<int> list{1, 2, 3, 4, 5, 6};
  const LinkedList<int> constList = list;
  auto it = std::find(constList.begin(), constList.end(), 2);
  EXPECT_NE(it, constList.end());
  EXPECT_EQ(*it, 2);
}

TEST_F(LinkedListTest, FindReverseIterator) {
  LinkedList<int> list{1, 2, 3, 4};
  auto it = std::find(list.rbegin(), list.rend(), 2);
  EXPECT_NE(it, list.rend());
  EXPECT_EQ(*it, 2);
}

TEST_F(LinkedListTest, FindConstReverseIterator) {
  LinkedList<int> list{1, 2, 3, 4};
  const LinkedList<int> constList = list;
  auto it = std::find(constList.rbegin(), constList.rend(), 2);
  EXPECT_NE(it, constList.rend());
  EXPECT_EQ(*it, 2);
}

// TEST_F(LinkedListTest, ReverseIterator) {
//   LinkedList<int> list{1, 2, 3};
//   std::reverse(list.begin(), list.end());
//   auto it = list.begin();
//   EXPECT_EQ(*it, 3);
//   ++it;
//   EXPECT_EQ(*it, 2);
//   ++it;
//   EXPECT_EQ(*it, 1);
//   ++it;
//   EXPECT_EQ(it, list.end());
// }
// TEST_F(LinkedListTest, ReverseConstIterator) {}
// TEST_F(LinkedListTest, ReverseReverseIterator) {}
// TEST_F(LinkedListTest, ReverseConstReverseIterator) {}

// TEST_F(LinkedListTest, SortIterator) {
//   LinkedList<int> list{3, 2, 4, 1, 5, 1, 6};
//   std::sort(list.begin(), list.end());
//   auto it = list.begin();
//   EXPECT_EQ(*it, 1);
//   ++it;
//   EXPECT_EQ(*it, 1);
//   ++it;
//   EXPECT_EQ(*it, 2);
//   ++it;
//   EXPECT_EQ(*it, 3);
//   ++it;
//   EXPECT_EQ(*it, 4);
//   ++it;
//   EXPECT_EQ(*it, 5);
//   ++it;
//   EXPECT_EQ(*it, 6);
//   ++it;
// }

TEST_F(LinkedListTest, Empty) {
  LinkedList<int> list;
  EXPECT_TRUE(list.empty());
  list.push_back(1);
  EXPECT_FALSE(list.empty());
}

TEST_F(LinkedListTest, Size) {
  LinkedList<int> list;
  EXPECT_EQ(list.size(), 0);
  int N = 10;
  for (int i = 0; i < N; ++i) {
    list.push_back(i);
    EXPECT_EQ(list.size(), i + 1);
  }
  EXPECT_EQ(list.size(), N);
}

TEST_F(LinkedListTest, Clear) {
  LinkedList<int> list;
  list.clear();
  EXPECT_EQ(list.size(), 0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
