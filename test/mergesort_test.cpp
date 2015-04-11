#include <gtest/gtest.h>

#include "mergesort.hpp"

TEST(mergesort, one) {
  int unsorted[] = {2, 4, 1, 5, 3};
  int len = 5;
  EXPECT_EQ(1, merge_sort(unsorted, len)[0]);
  EXPECT_EQ(2, merge_sort(unsorted, len)[1]);
  EXPECT_EQ(3, merge_sort(unsorted, len)[2]);
  EXPECT_EQ(4, merge_sort(unsorted, len)[3]);
  EXPECT_EQ(5, merge_sort(unsorted, len)[4]);
}

