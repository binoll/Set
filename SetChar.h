#include "headers.h"

/*Класс множества символов (коды ASCII)*/
class SetChar {
public:
    SetChar(int16_t l, int16_t r); //Конструктор без параметров

    SetChar(const SetChar &set); //Конструктор копирования

    SetChar(SetChar &&set) noexcept; //Конструктор перемещения

    ~SetChar(); //Деструктор

    bool find(char a); //Поиск элемента

    bool add(char a); //Добавление элемента в множество

    bool remove(char a); //Удаление элемента из множества

    SetChar& operator=(const SetChar &set); //Перегрузка оператора для присваивания

    SetChar& operator=(SetChar &&set) noexcept; //Перегрузка оператора для присваивания с переносом

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

SetChar::SetChar(int16_t l, int16_t r) : l(l), r(r), n((r - l) / 8 + 1) {
    ptr = new char[n];

    for (int16_t i = 0; i < n; ++i) {
        ptr[i] = 0;
    }
}

SetChar::SetChar(const SetChar &set) : SetChar(set.l, set.r) {
    this->size = set.size;
    this->l = set.l;
    this->r = set.r;
    this->n = set.n;

    for (int16_t i = 0; i < n; ++i) {
        this->ptr[i] = set.ptr[i];
    }
}

SetChar::SetChar(SetChar &&set) noexcept {
    this->ptr = set.ptr;
    this->size = set.size;
    this->l = set.l;
    this->r = set.r;
    this->n = set.n;

    set.ptr = nullptr;
    set.n = 0;
    set.r = 0;
    set.l = 0;
}

SetChar::~SetChar() {
    for (int16_t i = 0; i < n; ++i) {
        ptr[i] = 0;
    }

    delete[] ptr;
}

bool SetChar::find(char a) {
    int16_t byte = (static_cast<int16_t>(a) - l) / 8;
    int16_t bit = (static_cast<int16_t>(a) - l) % 8;
    int16_t mask = 1 << bit;

    if (static_cast<bool>(mask & ptr[byte])) {
        return true;
    }

    return false;
}

bool SetChar::add(char a) {
    int16_t byte = (static_cast<int16_t>(a) - l) / 8;
    int16_t bit = (static_cast<int16_t>(a) - l) % 8;
    int8_t mask = 1 << bit;

    if (!static_cast<bool>(mask & ptr[byte])) {
        ptr[byte] |= mask;
        ++size;
        return true;
    }

    return false;
}

bool SetChar::remove(char a) {
    int16_t byte = (static_cast<int16_t>(a) - l) / 8;
    int16_t bit = (static_cast<int16_t>(a) - l) % 8;
    int16_t mask = ~(1 << bit);

    if (static_cast<bool>(mask & ptr[byte])) {
        ptr[byte] &= mask;
        --size;
        return true;
    }

    return false;
}

SetChar& SetChar::operator=(const SetChar &set) {
    this->size = set.size;
    this->l = set.l;
    this->r = set.r;
    this->n = set.n;

    for (int16_t i = 0; i < n; ++i) {
        this->ptr[i] = set.ptr[i];
    }

    return *this;
}

SetChar& SetChar::operator=(SetChar &&set) noexcept {
    this->ptr = set.ptr;
    this->size = set.size;
    this->l = set.l;
    this->r = set.r;

    set.ptr = nullptr;
    set.n = 0;
    set.r = 0;
    set.l = 0;

    return *this;
}

const SetChar& operator+(SetChar &set_left, SetChar &set_right) {
    for (int16_t start = 0, end = set_left.n; start < end; ++start) {
        set_left.ptr[start] |= set_right.ptr[start];
    }

    set_left.size = 0;

    for (int16_t start = 0, end = (set_left.r - set_left.l); start < end; ++start) {
        if (set_left.find(start)) {
            ++set_left.size;
        }
    }

    return set_left;
}

const SetChar& operator*(SetChar &set_left, SetChar &set_right) {
    for (int16_t start = 0, end = set_left.n; start < end; ++start) {
        set_left.ptr[start] &= set_right.ptr[start];
    }

    set_left.size = 0;

    for (int16_t start = 0, end = (set_left.r - set_left.l); start < end; ++start) {
        if (set_left.find(start)) {
            ++set_left.size;
        }
    }

    return set_left;
}

const SetChar& operator-(SetChar &set_left, SetChar &set_right) {
    if (set_left.size > set_right.size) {
        set_left.size = 0;
        for (int16_t start = 0, end = set_left.n; start < end; ++start) {
            set_left.ptr[start] &= ~(set_right.ptr[start]);
        }
        for (int16_t start = 0, end = (set_left.r - set_left.l); start < end; ++start) {
            if (set_left.find(start)) {
                ++set_left.size;
            }
        }
    }
    else {
        for (int16_t start = 0, end = set_left.n; start < end; ++start) {
            set_left.ptr[start] = 0;
        }
        set_left.size = 0;
    }

    return set_left;
}

const SetChar& operator~(SetChar &set) {
    set.size = set.n - set.size;

    for (int16_t start = 0, end = set.n; start < end; ++start) {
        set.ptr[start] = ~(set.ptr[start]);
    }

    return set;
}

std::ostream& operator<<(std::ostream &stream, SetChar &set) {
    int16_t count = 0;

    stream << "{ ";
    for (int16_t start = 0, end = (set.r - set.l); start < end; ++start) {
        if (set.find(start)) {
            if (count == 0) {
                std::cout << static_cast<char>(start) << " (" << static_cast<int16_t>(start) << ")";
            }
            else {
                std::cout << ", " << static_cast<char>(start) << " (" << static_cast<int16_t>(start) << ")";
            }
            ++count;
        }
    }
    stream << " }";

    return stream;
}