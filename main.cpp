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
    setchar4.add('B');
    setchar4.add('A');
    setchar5.add('B');
    setchar5.add('C');

    setchar3 = setchar1;

    std::cout << "Before: " << setchar1 << " " << setchar2 << " " << setchar3
              << " " << setchar4 << " " << setchar5 << '\n';
    setchar1 + setchar2;
    std::cout << "After sum: " << setchar1 << '\n';
    setchar1 - setchar3;
    std::cout << "After dif: " << setchar1 << '\n';
    setchar1.remove('2');
    std::cout << "After remove: " << setchar1 << '\n';
    setchar4 * setchar5;
    std::cout << "After composition: " << setchar4 << '\n';

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
    std::cout << "After sum: " << setint1 << '\n';
    setint1.remove(10);
    std::cout << "After remove: " << setint1 << '\n';
    ~setint1;
    std::cout << "After addition: " << setint1 << '\n';

    return 0;
}
