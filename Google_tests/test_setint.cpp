#include "lib/googletest/include/gtest/gtest.h"
#include "../headers.h"
#include "../SetInt.h"

namespace Int {
    int l1 = 0, r1 = 100;
    int l2 = 50, r2 = 100;
    int l3 = 0, r3 = 100;
    int l4 = 50, r4 = 100;
    SetInt setint1(l1, r1);
    SetInt setint2(l1, r1);
    SetInt setint3(l1, r1);
    SetInt setint4(l1, r1);
    SetInt setint5(l2, r2);
    SetInt setint6(l2, r2);
    SetInt setint7(l2, r2);
    SetInt setint8(l3, r3);
    SetInt setint9(l3, r3);
    SetInt setint10(l4, r4);
    SetInt setint11(l3, r3);
    SetInt setint12(l4, r4);
    SetInt setint13(l2, r2);
    std::array<int, 100> arr1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                 11, 12, 13, 14, 15, 16, 17, 18, 19,
                                 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
                                 30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
                                 40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
                                 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
                                 60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
                                 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
                                 80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
                                 90, 91, 92, 93, 94, 95, 96, 97, 98, 99};
    std::array<int, 10> arr2 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::array<int, 11> arr3 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::array<int, 41> arr4 = {20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
                                30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
                                40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
                                50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60};
    std::array<int, 49> arr5 = {51, 52, 53, 54, 55, 56, 57, 58, 59,
                                60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
                                70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
                                80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
                                90, 91, 92, 93, 94, 95, 96, 97, 98, 99};
    std::array<int, 20> arr6 = {80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
                                90, 91, 92, 93, 94, 95, 96, 97, 98, 99};
}

using namespace Int;

TEST(TestSetInt, TestAddMethod) {
    ASSERT_EQ(setint1.getSize(), setint2.getSize());

    for (auto s : arr1) {
        ASSERT_TRUE(setint1.add(s));
        ASSERT_TRUE(setint2.add(s));
    }

    ASSERT_EQ(setint1.getSize(), setint2.getSize());
}

TEST(TestSetInt, TestRemoveMethod) {
    ASSERT_EQ(setint3.getSize(), setint4.getSize());

    for (auto s : arr2) {
        setint3.add(s);
    }
    for (auto s : arr3) {
        setint4.add(s);
    }

    ASSERT_NE(setint3.getSize(), setint4.getSize());
    ASSERT_TRUE(setint4.remove(10));
    ASSERT_EQ(setint3.getSize(), setint4.getSize());
}

TEST(TestSetInt, TestFindMethod) {
    for (auto s : arr3) {
        setint5.add(s);
        setint6.add(s);
    }

    setint3.remove(5);
    setint4.remove(7);

    for (auto s : arr2) {
        if (s != 5 && s != 7) {
            ASSERT_TRUE(setint3.find(s));
            ASSERT_TRUE(setint4.find(s));
        }
        else if (s == 5) {
            ASSERT_FALSE(setint3.find(s));
        }
        else if (s == 7) {
            ASSERT_FALSE(setint4.find(s));
        }
    }
}

TEST(TestSetInt, TestSum) {
    for (auto s : arr4) {
        setint7.add(s);
    }
    for (auto s : arr5) {
        setint8.add(s);
    }

    ASSERT_EQ(11, setint7.getSize());

    setint7 + setint8;

    ASSERT_EQ(50, setint7.getSize());
}

TEST(TestSetInt, TestDif) {
    for (auto s : arr4) {
        setint9.add(s);
    }
    for (auto s : arr5) {
        setint10.add(s);
    }

    ASSERT_EQ(41, setint9.getSize());

    setint9 - setint10;

    ASSERT_EQ(49, setint10.getSize());
}

TEST(TestSetInt, TestMulti) {
    for (auto s: arr4) {
        setint11.add(s);
    }
    for (auto s: arr5) {
        setint12.add(s);
    }

    ASSERT_NE(setint12.getSize(), setint11.getSize());

    setint11 * setint12;

    ASSERT_EQ(10, setint11.getSize());
}

TEST(TestSetInt, TestAddition) {
    for (auto s: arr6) {
        setint13.add(s);
    }

    ASSERT_EQ(20, setint13.getSize());

    ~setint13;

    ASSERT_EQ(31, setint13.getSize());
}