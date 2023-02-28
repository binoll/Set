#include "lib/googletest/include/gtest/gtest.h"
#include "../headers.h"
#include "../SetChar.h"

namespace Char {
    int l1 = 0, r1 = 100;
    int l2 = 50, r2 = 100;
    int l3 = 0, r3 = 100;
    int l4 = 50, r4 = 100;
    SetChar setchar1(l1, r1);
    SetChar setchar2(l1, r1);
    SetChar setchar3(l1, r1);
    SetChar setchar4(l1, r1);
    SetChar setchar5(l2, r2);
    SetChar setchar6(l2, r2);
    SetChar setchar7(l2, r2);
    SetChar setchar8(l3, r3);
    SetChar setchar9(l3, r3);
    SetChar setchar10(l4, r4);
    SetChar setchar11(l3, r3);
    SetChar setchar12(l4, r4);
    SetChar setchar13(l2, r2);
    SetChar setchar14(l1, r1);
    std::array<char, 100> arr1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                  11, 12, 13, 14, 15, 16, 17, 18, 19,
                                  20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
                                  30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
                                  40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
                                  50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
                                  60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
                                  70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
                                  80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
                                  90, 91, 92, 93, 94, 95, 96, 97, 98, 99};
    std::array<char, 10> arr2 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::array<char, 11> arr3 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::array<char, 41> arr4 = {20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
                                 30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
                                 40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
                                 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60};
    std::array<char, 49> arr5 = {51, 52, 53, 54, 55, 56, 57, 58, 59,
                                 60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
                                 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
                                 80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
                                 90, 91, 92, 93, 94, 95, 96, 97, 98, 99};
    std::array<char, 20> arr6 = {80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
                                 90, 91, 92, 93, 94, 95, 96, 97, 98, 99};
}

using namespace Char;

TEST(TestSetChar, TestAddMethod) {
    ASSERT_EQ(setchar1.getSize(), setchar2.getSize());

    for (auto s : arr1) {
        ASSERT_TRUE(setchar1.add(s));
        ASSERT_TRUE(setchar2.add(s));
    }

    ASSERT_EQ(setchar1.getSize(), setchar2.getSize());
}

TEST(TestSetChar, TestRemoveMethod) {
    ASSERT_EQ(setchar3.getSize(), setchar4.getSize());

    for (auto s : arr2) {
        setchar3.add(s);
    }
    for (auto s : arr3) {
        setchar4.add(s);
    }

    ASSERT_NE(setchar3.getSize(), setchar4.getSize());
    ASSERT_TRUE(setchar4.remove(10));
    ASSERT_EQ(setchar3.getSize(), setchar4.getSize());
}

TEST(TestSetChar, TestFindMethod) {
    for (auto s : arr3) {
        setchar5.add(s);
        setchar6.add(s);
    }

    setchar3.remove(5);
    setchar4.remove(7);

    for (auto s : arr2) {
        if (s != 5 && s != 7) {
            ASSERT_TRUE(setchar3.find(s));
            ASSERT_TRUE(setchar4.find(s));
        }
        else if (s == 5) {
            ASSERT_FALSE(setchar3.find(s));
        }
        else if (s == 7) {
            ASSERT_FALSE(setchar4.find(s));
        }
    }
}

TEST(TestSetChar, TestSum) {
    for (auto s : arr4) {
        setchar7.add(s);
    }
    for (auto s : arr5) {
        setchar8.add(s);
    }

    ASSERT_EQ(11, setchar7.getSize());

    setchar7 + setchar8;

    ASSERT_EQ(50, setchar7.getSize());
}

TEST(TestSetChar, TestDif) {
    for (auto s : arr4) {
        setchar9.add(s);
    }
    for (auto s : arr5) {
        setchar10.add(s);
    }

    ASSERT_EQ(41, setchar9.getSize());

    setchar9 - setchar10;

    ASSERT_EQ(49, setchar10.getSize());
}

TEST(TestSetChar, TestMulti) {
    for (auto s: arr4) {
        setchar11.add(s);
    }
    for (auto s: arr5) {
        setchar12.add(s);
    }

    ASSERT_NE(setchar12.getSize(), setchar11.getSize());

    setchar11 * setchar12;

    ASSERT_EQ(10, setchar11.getSize());
}

TEST(TestSetChar, TestAddition) {
    for (auto s: arr6) {
        setchar13.add(s);
    }

    ASSERT_EQ(20, setchar13.getSize());

    ~setchar13;

    ASSERT_EQ(31, setchar13.getSize());
}

TEST(TestSetChar, TestAssignment) {
    for (auto s : arr1) {
        setchar14.add(s);
    }

    ASSERT_ANY_THROW(setchar14 = setchar14);
}