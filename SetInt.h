#include "headers.h"

/*Класс множества чисел*/
class SetInt {
public:
    SetInt(int32_t l, int32_t r); //Конструктор без параметров

    SetInt(const SetInt &set); //Конструктор копирования

    SetInt(SetInt &&set) noexcept; //Конструктор перемещения

    ~SetInt(); //Деструктор

    bool find(int32_t a); //Поиск элемента

    bool add(int32_t a); //Добавление элемента в множество

    bool remove(int32_t a); //Удаление элемента из множества

    bool clear(); //Обнуление мн-ва

    int32_t getSize() const; //Метод возвращает текущий размер мн-ва

    SetInt& operator=(const SetInt &set); //Перегрузка оператора для присваивания

    SetInt& operator=(SetInt &&set) noexcept; //Перегрузка оператора для присваивания с переносом

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

SetInt::SetInt(int32_t l, int32_t r) : l(l), r(r), n((r - l) / sizeof(int32_t) + 1) {
    ptr = new int32_t[n];

    for (int32_t i = 0; i < n; ++i) {
        ptr[i] = 0;
    }
}

SetInt::SetInt(const SetInt &set) : SetInt(set.l, set.r) {
    this->size = set.size;
    this->l = set.l;
    this->r = set.r;
    this->n = set.n;

    for (int32_t i = 0; i < n; ++i) {
        this->ptr[i] = set.ptr[i];
    }
}

SetInt::SetInt(SetInt &&set) noexcept {
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

SetInt::~SetInt() {
   delete[] ptr;
}

bool SetInt::find(int32_t a) {
    int32_t byte = (a - l) / (sizeof(int32_t) * 8);
    int32_t bit = (a - l) % (sizeof(int32_t) * 8);
    int32_t mask = 1 << bit;

    if (static_cast<bool>(mask & ptr[byte])) {
        return true;
    }

    return false;
}

bool SetInt::add(int32_t a) {
    int32_t byte = (a - l) / (sizeof(int32_t) * 8);
    int32_t bit = (a - l) % (sizeof(int32_t) * 8);
    int32_t mask = 1 << bit;

    if (size == (r - l) || a > r || a < l) {
        return false;
    }
    if (!static_cast<bool>(mask & ptr[byte])) {
        ptr[byte] |= mask;
        ++size;
        return true;
    }

    return false;
}

bool SetInt::remove(int32_t a) {
    int32_t byte = (a - l) / (sizeof(int32_t) * 8);
    int32_t bit = (a - l) % (sizeof(int32_t) * 8);
    int32_t mask = 1 << bit;

    if (size == 0) {
        return false;
    }
    if (static_cast<bool>(mask & ptr[byte])) {
        ptr[byte] &= ~mask;
        --size;
        return true;
    }

    return false;
}

bool SetInt::clear() {
    for (int32_t i = 0; i < n; ++i) {
        ptr[i] = 0;
    }

    return true;
}

int32_t SetInt::getSize() const {
    return size;
}

SetInt& SetInt::operator=(const SetInt &set) {
    this->size = set.size;
    this->l = set.l;
    this->r = set.r;
    this->n = set.n;

    for (int32_t i = 0; i < n; ++i) {
        this->ptr[i] = set.ptr[i];
    }

    return *this;
}

SetInt& SetInt::operator=(SetInt &&set) noexcept {
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

const SetInt& operator+(SetInt &set_left, SetInt &set_right) {
    for (int32_t start = 0, end = set_left.n; start < end; ++start) {
        set_left.ptr[start] |= set_right.ptr[start];
    }

    set_left.size = 0;

    for (int32_t start = set_left.l, end = (set_left.r - set_left.l); start < end; ++start) {
        if (set_left.find(start)) {
            ++set_left.size;
        }
    }

    return set_left;
}

const SetInt& operator*(SetInt &set_left, SetInt &set_right) {
    for (int32_t start = 0, end = set_left.n; start < end; ++start) {
        set_left.ptr[start] &= set_right.ptr[start];
    }

    set_left.size = 0;

    for (int32_t start = set_left.l, end = (set_left.r - set_left.l); start < end; ++start) {
        if (set_left.find(start)) {
            ++set_left.size;
        }
    }

    return set_left;
}

const SetInt& operator-(SetInt &set_left, SetInt &set_right) {
    if (set_left.size > set_right.size) {
        set_left.size = 0;
        for (int32_t start = 0, end = set_left.n; start < end; ++start) {
            set_left.ptr[start] &= ~(set_right.ptr[start]);
        }
        for (int32_t start = 0, end = (set_left.r - set_left.l); start < end; ++start) {
            if (set_left.find(start)) {
                ++set_left.size;
            }
        }
    }
    else {
        for (int32_t start = 0, end = set_left.n; start < end; ++start) {
            set_left.ptr[start] = 0;
        }
        set_left.size = 0;
    }

    return set_left;
}

const SetInt& operator~(SetInt &set) {
    set.size = set.n - set.size;

    for (int32_t start = 0, end = set.n; start < end; ++start) {
        set.ptr[start] = ~(set.ptr[start]);
    }

    set.size = 0;

    for (int16_t start = set.l, end = (set.r - set.l); start < end; ++start) {
        if (set.find(start)) {
            ++set.size;
        }
    }

    return set;
}

std::ostream& operator<<(std::ostream &stream, SetInt &set) {
    int32_t count = 0;

    stream << "{ ";
    for (int32_t start = 0, end = (set.r - set.l); start < end; ++start) {
        if (set.find(start)) {
            if (count == 0) {
                std::cout << start;
            }
            else {
                std::cout << ", " << start;
            }
            ++count;
        }
    }
    stream << " }";

    return stream;
}