#include "SetChar.h"

SetChar::SetChar(int16_t l, int16_t r) : l(l), r(r), n((r - l) / (sizeof(char) * 8) + 1) {
    try {
        ptr = new char[n];

        if (ptr == nullptr) {
            throw std::exception();
        }

        for (int16_t i = 0; i < n; ++i) {
            ptr[i] = 0;
        }
    } catch (...) {
        std::cout << "\nNo memory\n";
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

void SetChar::clear() {
    for (int16_t i = 0; i < n; ++i) {
        ptr[i] = 0;
    }

    size = 0;
}

int16_t SetChar::getSize() const {
    return size;
}

SetChar& SetChar::operator=(const SetChar &set) {
    if (this->ptr == set.ptr) {
        throw std::exception();
    }
    else {
        delete[] this->ptr;

        this->size = set.size;
        this->l = set.l;
        this->r = set.r;
        this->n = set.n;

        for (int16_t i = 0; i < n; ++i) {
            this->ptr[i] = set.ptr[i];
        }
    }

    return *this;
}

SetChar& SetChar::operator=(SetChar &&set) {
    if (this->ptr == set.ptr) {
        throw std::exception();
    }
    else {
        this->ptr = set.ptr;
        this->size = set.size;
        this->l = set.l;
        this->r = set.r;

        set.ptr = nullptr;
        set.n = 0;
        set.r = 0;
        set.l = 0;
    }

    return *this;
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