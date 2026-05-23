#include <gtest/gtest.h>
#include "list.h"

TEST(SkipListTest, ConstructorAndBasic) {
    SkipList<int> list;
    EXPECT_TRUE(list.isEmpty());

    SkipList<int> list2(10, 0.25);
    EXPECT_TRUE(list2.isEmpty());
}

TEST(SkipListTest, AddElement) {
    SkipList<int> list;
    list.add(10);
    EXPECT_FALSE(list.isEmpty());
    EXPECT_TRUE(list.find(10));
    EXPECT_FALSE(list.find(20));
}

TEST(SkipListTest, AddDuplicates) {
    SkipList<int> list;
    list.add(10);
    list.add(10);
    list.add(10);

    EXPECT_TRUE(list.find(10));

    int count = 0;
    SkipListIterator<int> i = list.itr();
    while (i.hasNext()) {
        i.Next();
        count++;
    }
    EXPECT_EQ(count, 1);
}

TEST(SkipListTest, RemoveElements) {
    SkipList<int> list;
    list.add(10);
    list.add(20);
    list.add(30);
    EXPECT_TRUE(list.find(20));
    list.remove(20);
    EXPECT_FALSE(list.find(20));
    EXPECT_TRUE(list.find(10));
    EXPECT_TRUE(list.find(30));
    list.remove(10);
    EXPECT_FALSE(list.find(10));
    EXPECT_TRUE(list.find(30));
}

TEST(SkipListTest, RemoveNonExisting) {
    SkipList<int> list;
    list.add(10);
    list.add(20);
    EXPECT_THROW(list.remove(30), int);
    EXPECT_TRUE(list.find(10));
    EXPECT_TRUE(list.find(20));
}

TEST(SkipListTest, RemoveFromEmpty) {
    SkipList<int> list;
    EXPECT_THROW(list.remove(10), int);
}

TEST(SkipListTest, CopyConstructor) {
    SkipList<int> list1;
    list1.add(10);
    list1.add(20);
    list1.add(30);
    SkipList<int> list2(list1);

    EXPECT_TRUE(list2.find(10));
    EXPECT_TRUE(list2.find(20));
    EXPECT_TRUE(list2.find(30));

    list1.remove(20);
    EXPECT_FALSE(list1.find(20));
    EXPECT_TRUE(list2.find(20));
}

TEST(SkipListTest, AssignmentOperator) {
    SkipList<int> list1;
    list1.add(10);
    list1.add(20);
    list1.add(30);
    SkipList<int> list2;
    list2 = list1;

    EXPECT_TRUE(list2.find(10));
    EXPECT_TRUE(list2.find(20));
    EXPECT_TRUE(list2.find(30));

    list1.remove(20);
    EXPECT_FALSE(list1.find(20));
    EXPECT_TRUE(list2.find(20));
}

TEST(SkipListTest, SelfAssignment) {
    SkipList<int> list;
    list.add(10);
    list.add(20);
    list.add(30);
    list = list;

    EXPECT_TRUE(list.find(10));
    EXPECT_TRUE(list.find(20));
    EXPECT_TRUE(list.find(30));
}

TEST(SkipListTest, Clear) {
    SkipList<int> list;
    list.add(10);
    list.add(20);
    list.add(30);
    EXPECT_FALSE(list.isEmpty());
    list.clear();
    EXPECT_TRUE(list.isEmpty());
    EXPECT_FALSE(list.find(10));
    list.add(40);
    EXPECT_TRUE(list.find(40));
}