#include "headers.h"

/*Класс множества символов (коды ASCII)*/
class SetChar {
public:
    SetChar(int16_t l, int16_t r); //Конструктор с параметрами

    SetChar(const SetChar &set); //Конструктор копирования

    SetChar(SetChar &&set) noexcept; //Конструктор перемещения

    ~SetChar(); //Деструктор

    bool find(char a); //Поиск элемента

    bool add(char a); //Добавление элемента в множество

    bool remove(char a); //Удаление элемента из множества

    void clear(); //Обнуление мн-ва

    int16_t getSize() const; //Метод возвращает текущий размер мн-ва

    SetChar& operator=(const SetChar &set); //Перегрузка оператора для присваивания

    SetChar& operator=(SetChar &&set); //Перегрузка оператора для присваивания с переносом

    friend const SetChar& operator+(SetChar &set_left, SetChar &set_right); //Перегрузка оператора для объединения двух множеств

    friend const SetChar& operator*(SetChar &set_left, SetChar &set_right); //Перегрузка оператора для пересечения двух множеств

    friend const SetChar& operator-(SetChar &set_left, SetChar &set_right); //Перегрузка оператора для разности двух множеств

    friend const SetChar& operator~(SetChar &set); //Перегрузка оператора для дополнения множества

    friend std::ostream& operator<<(std::ostream &stream, SetChar &set); //Перегрузка оператора для вставки в поток

private:
    int16_t size = 0; //Текущая мощность мн-ва
    int16_t n = 0; //Максимальная мощность мн-ва
    int16_t l = 0; //Граница мн-ва [l;r]
    int16_t r = 0;
    char *ptr = nullptr; //Указывает на массив, в котором хранятся элементы множества
};