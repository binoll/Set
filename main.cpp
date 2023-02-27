#include "SetChar.h"
#include "SetInt.h"

int main() {
    setlocale(LC_ALL, "Rus");

    /*Класс SetChar*/
    int32_t l1, r1;

    std::cout << "Class SetChar. Enter a range of numbers [l;r] (always [0;128)):\n";
    std::cin >> l1 >> r1;

    SetChar setchar1(l1, r1);
    SetChar setchar2(l1, r1);
    SetChar setchar3(l1, r1);
    SetChar setchar4(l1, r1);
    SetChar setchar5(l1, r1);

    setchar1.add('1');
    setchar2.add('2');
    setchar3.add('1');
    setchar4.add('B');
    setchar4.add('A');
    setchar5.add('B');
    setchar5.add('C');

    std::cout << "Before: " << setchar1 << " " << setchar2 << " " << setchar3
              << " " << setchar4 << " " << setchar5 << '\n';
    setchar1 + setchar2;
    std::cout << "After sum: " << setchar1 << ". Size: " << setchar1.getSize() << '\n';
    setchar1 - setchar3;
    std::cout << "After dif: " << setchar1 << ". Size: " << setchar1.getSize() << '\n';
    setchar1.remove('2');
    std::cout << "After remove: " << setchar1 << ". Size: " << setchar1.getSize() << '\n';
    setchar4 * setchar5;
    std::cout << "After composition: " << setchar4 << ". Size: " << setchar4.getSize() << '\n';

    /*Класс SetInt*/
    int32_t l2, r2;

    std::cout << "Class SetInt. Enter a range of numbers [l;r]:\n";
    std::cin >> l2 >> r2;

    SetInt setint1(l2, r2);
    SetInt setint2(l2, r2);

    setint1.add(10);
    setint2.add(20);

    std::cout << "Before: " << setint1 << " " << setint2 << '\n';
    setint1 + setint2;
    std::cout << "After sum: " << setint1 << ". Size: " << setint1.getSize() << '\n';
    setint1.remove(10);
    std::cout << "After remove: " << setint1 << ". Size: " << setint1.getSize() << '\n';
    ~setint1;
    std::cout << "After addition: " << setint1 << ". Size: " << setint1.getSize() << '\n';

    /*Оценка временных затрат*/
    int l = 0, r = 100;
    SetInt my_set1(l, r);
    SetInt my_set2(l, r);
    std::set<int> stl_set1;
    std::set<int> stl_set2;

    std::set<int> stl_set3;
    std::set<int> stl_set4;
    SetInt my_set3(l, r);
    SetInt my_set4(l, r);

    std::set<int> stl_set5;
    std::set<int> stl_set6;
    SetInt my_set5(l, r);
    SetInt my_set6(l, r);

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
    std::array<int, 41> arr2 = {20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
                                30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
                                40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
                                50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60};

    for (auto i : arr1) {
        my_set1.add(i);
        stl_set1.insert(i);
        my_set3.add(i);
        stl_set3.insert(i);
    }
    for (auto i : arr2) {
        my_set2.add(i);
        stl_set2.insert(i);
        my_set4.add(i);
        stl_set4.insert(i);
    }

    /*Addition*/
    auto start1 = clock();
    my_set1 + my_set2;
    auto stop1 = clock();

    auto start2 = clock();
    stl_set1.insert(stl_set2.begin(), stl_set2.end());
    auto stop2 = clock();

    std::cout << "\nTime stl_set: "
              << static_cast<double>(stop1 - start1) / CLOCKS_PER_SEC
              << " sec\n"
              << "\nTime my_set: "
              << static_cast<double>(stop2 - start2) / CLOCKS_PER_SEC
              << " sec\n";

    for (auto i = stl_set1.begin(); i != stl_set1.end(); ++i) {
        std::cout << *i << ' ';
    }
    std::cout << '\n' << my_set1 << '\n';

    return 0;
}
