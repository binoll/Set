#include "headers.h"

/*Класс множества чисел*/
class SetInt {
public:
    SetInt(int32_t l, int32_t r); //Конструктор с параметрами

    SetInt(const SetInt &set); //Конструктор копирования

    SetInt(SetInt &&set) noexcept; //Конструктор перемещения

    ~SetInt(); //Деструктор

    bool find(int32_t a); //Поиск элемента

    bool add(int32_t a); //Добавление элемента в множество

    bool remove(int32_t a); //Удаление элемента из множества

    void clear(); //Обнуление мн-ва

    int32_t getSize() const; //Метод возвращает текущий размер мн-ва

    SetInt& operator=(const SetInt &set); //Перегрузка оператора для присваивания

    SetInt& operator=(SetInt &&set); //Перегрузка оператора для присваивания с переносом

    friend const SetInt& operator+(SetInt &set_left, SetInt &set_right); //Перегрузка оператора для объединения двух множеств

    friend const SetInt& operator*(SetInt &set_left, SetInt &set_right); //Перегрузка оператора для пересечения двух множеств

    friend const SetInt& operator-(SetInt &set_left, SetInt &set_right); //Перегрузка оператора для разности двух множеств

    friend const SetInt& operator~(SetInt &set); //Перегрузка оператора для дополнения множества

    friend std::ostream& operator<<(std::ostream &stream, SetInt &set); //Перегрузка оператора для вставки в поток

private:
    int32_t size = 0; //Текущая мощность мн-ва
    int32_t n = 0; //Максимальная мощность мн-ва
    int32_t l = 0; //Граница мн-ва [l;r]
    int32_t r = 0;
    int32_t *ptr = nullptr; //Указывает на массив, в котором хранятся элементы множества
};