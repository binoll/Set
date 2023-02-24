#include "lib/googletest/include/gtest/gtest.h"
#include "../SetChar.h"

int l1 = 0, r1 = 100;
int l2 = 0, r2 = 10;
SetChar setchar1(l1, r1);
SetChar setchar2(l1, r1);
SetChar setchar3(l2, r2);
std::array<char, 100> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                             11, 12, 13, 14, 15, 16, 17, 18, 19,
                             20, 21, 22, 23, 24, 25,26, 27, 28, 29,
                             30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
                             40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
                             50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
                             60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
                             70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
                             80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
                             90, 91, 92, 93, 94, 95, 96, 97, 98, 99};

TEST(TestSetChar, TestAddMethod) {
    for (auto s : arr) {
        ASSERT_TRUE(setchar1.add(s));
        ASSERT_TRUE(setchar2.add(s));
        if (s > r2) {
            ASSERT_FALSE(setchar3.add(s));
        }
    }

    ASSERT_EQ(setchar1.getSize(), setchar2.getSize());
    ASSERT_NE(setchar1.getSize(), setchar3.getSize());
}

TEST(TestSetChar, TestRemoveMethod) {
    ASSERT_EQ(setchar1.getSize(), setchar2.getSize());

    for (auto s : arr) {
        ASSERT_TRUE(setchar1.remove(s));
        ASSERT_TRUE(setchar2.remove(s));
        ASSERT_FALSE(setchar3.remove(s));
    }
}
