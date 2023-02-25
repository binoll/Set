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

    bool clear(); //Обнуление мн-ва

    int16_t getSize() const; //Метод возвращает текущий размер мн-ва

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

SetChar::SetChar(int16_t l, int16_t r) : l(l), r(r), n((r - l) / (sizeof(char) * 8) + 1) {
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
    delete[] ptr;
}

bool SetChar::find(char a) {
    int16_t byte = (static_cast<int16_t>(a) - l) / (sizeof(char) * 8);
    int16_t bit = (static_cast<int16_t>(a) - l) % (sizeof(char) * 8);
    int16_t mask = 1 << bit;

    if (static_cast<bool>(mask & ptr[byte])) {
        return true;
    }

    return false;
}

bool SetChar::add(char a) {
    int16_t byte = (static_cast<int16_t>(a) - l) / (sizeof(char) * 8);
    int16_t bit = (static_cast<int16_t>(a) - l) % (sizeof(char) * 8);
    int16_t mask = 1 << bit;

    if ((a > r) || (a < l)) {
        return false;
    }
    if (!static_cast<bool>(mask & ptr[byte])) {
        ptr[byte] |= mask;
        ++size;
        return true;
    }

    return false;
}

bool SetChar::remove(char a) {
    int16_t byte = (static_cast<int16_t>(a) - l) / (sizeof(char) * 8);
    int16_t bit = (static_cast<int16_t>(a) - l) % (sizeof(char) * 8);
    int16_t mask = 1 << bit;

    if (static_cast<bool>(mask & ptr[byte])) {
        ptr[byte] &= ~(mask);
        --size;
        return true;
    }

     return false;
}

bool SetChar::clear() {
    for (int16_t i = 0; i < n; ++i) {
        ptr[i] = 0;
    }

    size = 0;

    return true;
}

int16_t SetChar::getSize() const {
    return size;
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
    if (set_left.r > set_right.l) {
        for (int16_t i = set_right.l; i < set_left.r; ++i) {
            if (set_right.find(i)) {
                set_left.add(i);
            }
        }

        set_left.size = 0;

        for (int16_t i = set_left.l; i < set_left.r; ++i) {
            if (set_left.find(i)) {
                ++set_left.size;
            }
        }
    }
    else if ((set_left.l > set_right.l) && (set_left.r < set_left.r)) {
        for (int16_t i = set_right.l; i < set_left.r; ++i) {
            if (set_right.find(i)) {
                set_left.add(i);
            }
        }

        return set_left;
    }

    return set_left;
}

const SetChar& operator*(SetChar &set_left, SetChar &set_right) {
    if (set_left.r > set_right.l) {
        for (int16_t i = set_left.l; i < set_right.l; ++i) {
            set_left.remove(i);
        }
        for (int16_t i = set_right.l; i < set_left.r; ++i) {
            if (!(set_left.find(i) && set_right.find(i))) {
                set_left.remove(i);
            }
        }

        set_left.size = 0;

        for (int16_t i = set_left.l; i < set_left.r; ++i) {
            if (set_left.find(i)) {
                ++set_left.size;
            }
        }
    }
    else {
        set_left.clear();
        set_left.size = 0;

        return set_left;
    }

    return set_left;
}

const SetChar& operator-(SetChar &set_left, SetChar &set_right) {
    if (set_left.r > set_right.l) {
        for (int16_t i = set_right.l; i < set_left.r; ++i) {
            if (set_left.find(i) && set_right.find(i)) {
                set_left.remove(i);
            }
        }

        set_left.size = 0;

        for (int16_t i = set_left.l; i < set_left.r; ++i) {
            if (set_left.find(i)) {
                ++set_left.size;
            }
        }
    }
    else if ((set_left.l > set_right.l) && (set_left.r < set_left.r)) {
        set_left.clear();
        set_left.size = 0;

        return set_left;
    }

    return set_left;
}

const SetChar& operator~(SetChar &set) {
    for (int16_t i = 0; i < set.n; ++i) {
        set.ptr[i] = ~(set.ptr[i]);
    }

    set.size = 0;

    for (int16_t i = set.l; i <= set.r; ++i) {
        if (set.find(i)) {
            ++set.size;
        }
    }

    return set;
}

std::ostream& operator<<(std::ostream &stream, SetChar &set) {
    int16_t count = 0;

    stream << "{ ";
    for (int16_t i = set.l; i < set.r; ++i) {
        if (set.find(i)) {
            if (count == 0) {
                std::cout << "'" << static_cast<char>(i) << "'" << "(" << static_cast<int16_t>(i) << ")";
            }
            else {
                std::cout << ", ";
                std::cout << "'" << static_cast<char>(i) << "'";
                std::cout << "(" << static_cast<int16_t>(i) << ")";
            }
            ++count;
        }
    }
    stream << " }";

    return stream;
}