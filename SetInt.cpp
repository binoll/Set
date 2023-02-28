#include "SetInt.h"

SetInt::SetInt(int32_t l, int32_t r) : l(l), r(r), n((r - l) / (sizeof(int32_t) * 8) + 1) {
    try {
        ptr = new int32_t[n];

        if (ptr == nullptr) {
            throw std::exception();
        }

        for (int32_t i = 0; i < n; ++i) {
            ptr[i] = 0;
        }
    } catch (...) {
        std::cout << "\nNo memory\n";
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

bool SetInt::remove(int32_t a) {
    int32_t byte = (a - l) / (sizeof(int32_t) * 8);
    int32_t bit = (a - l) % (sizeof(int32_t) * 8);
    int32_t mask = 1 << bit;

    if (static_cast<bool>(mask & ptr[byte])) {
        ptr[byte] &= ~(mask);
        --size;
        return true;
    }

    return false;
}

void SetInt::clear() {
    for (int32_t i = 0; i < n; ++i) {
        ptr[i] = 0;
    }

    size = 0;
}

int32_t SetInt::getSize() const {
    return size;
}

SetInt& SetInt::operator=(const SetInt &set) {
    try {
        if (this->ptr == set.ptr) {
            throw std::exception();
        }
        else {
            delete[] this->ptr;

            this->size = set.size;
            this->l = set.l;
            this->r = set.r;
            this->n = set.n;

            for (int32_t i = 0; i < n; ++i) {
                this->ptr[i] = set.ptr[i];
            }
        }
    } catch (...) {
        std::cout << "\nYou can't assign it yourself\n";
    }

    return *this;
}

SetInt& SetInt::operator=(SetInt &&set) {
    try {
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
    } catch (...) {
        std::cout << "\nYou can't assign it yourself\n";
    }

    return *this;
}

const SetInt& operator+(SetInt &set_left, SetInt &set_right) {
    if (set_left.r >= set_right.l) {
        for (int32_t i = set_left.l; i < set_left.r; ++i) {
            if (set_right.find(i)) {
                set_left.add(i);
            }
        }
    }

    set_left.size = 0;

    for (int32_t i = set_left.l; i < set_left.r; ++i) {
        if (set_left.find(i)) {
            ++set_left.size;
        }
    }

    return set_left;
}

const SetInt& operator*(SetInt &set_left, SetInt &set_right) {
    if (set_left.r > set_right.l) {
        for (int32_t i = set_left.l; i < set_right.l; ++i) {
            set_left.remove(i);
        }
        for (int32_t i = set_right.l; i < set_left.r; ++i) {
            if (!(set_left.find(i) && set_right.find(i))) {
                set_left.remove(i);
            }
        }

        set_left.size = 0;

        for (int32_t i = set_left.l; i < set_left.r; ++i) {
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

const SetInt& operator-(SetInt &set_left, SetInt &set_right) {
    if (set_left.r > set_right.l) {
        for (int32_t i = set_right.l; i < set_left.r; ++i) {
            if (set_left.find(i) && set_right.find(i)) {
                set_left.remove(i);
            }
        }

        set_left.size = 0;

        for (int32_t i = set_left.l; i < set_left.r; ++i) {
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

const SetInt& operator~(SetInt &set) {
    for (int32_t i = 0; i < set.n; ++i) {
        set.ptr[i] = ~(set.ptr[i]);
    }

    set.size = 0;

    for (int32_t i = set.l; i <= set.r; ++i) {
        if (set.find(i)) {
            ++set.size;
        }
    }

    return set;
}

std::ostream& operator<<(std::ostream &stream, SetInt &set) {
    int32_t count = 0;

    stream << "{ ";
    for (int32_t i = set.l; i < set.r; ++i) {
        if (set.find(i)) {
            if (count == 0) {
                std::cout << i;
            }
            else {
                std::cout << ", ";
                std::cout << i;
            }
            ++count;
        }
    }
    stream << " }";

    return stream;
}