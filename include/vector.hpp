#include <string>

#include "tools.hpp"

namespace nvec {

/// @brief Watch matrix.hpp
/// @tparam T
template <typename T>
class Matrix;

template <typename T>
#if __cplusplus >= 202002L
requires requires(T x) {
    x + x;
}
requires requires(T x) { x - x; }
requires requires(T x) { x* x; }
#endif
class Vector {
   public:
    Vector();
    Vector(std::size_t size) : size(size), body(new T[size]) {
        assert(size > 0);
    }
    Vector(const Vector<T>& src) {
        T* body = new T[src.get_size()];
        size = src.get_size();
        for (unsigned long i = 0; i != size; i++) {
            body[i] = src[i];
        }
    }
    Vector(const Vector<T>* src) {
        this->body = new T[src->get_size()];
        size = src->get_size();
        for (unsigned long i = 0; i != size; i++) {
            body[i] = (*src)[i];
        }
    }
    Vector(const T* src, std::size_t size) {
        assert(size > 0);
        this->size = size;
        this->body = new T[size];
        for (int i = 0; i < size; ++i) {
            this->body[i] = src[i];
        }
    }
    template <std::size_t size>
    Vector(const T (&src)[size]) {
        assert(size > 0);
        this->size = size;
        this->body = new T[size];
        for (int i = 0; i < size; ++i) {
            this->body[i] = src[i];
        }
    }
    ~Vector() { delete[] this->body; };

    T& operator[](int index) const { return (body[index]); }
    T& operator[](int index) { return (body[index]); }

    bool operator==(const Vector<T>& other) const {
        assert(get_size() == other.get_size());
        for (unsigned long i = 0; i != this->get_size(); i++) {
            if ((*this)[i] != other[i]) {
                return false;
            }
        }
        return true;
    }

    Vector<T>& operator+=(const Vector<T>& other) {
        assert(get_size() == other.get_size());
        for (unsigned long i = 0; i < this->get_size(); ++i) {
            this->body[i] += other[i];
        }
        return *this;
    }

    template <typename S>
    Vector<T>& operator+=(const S& other) {
        for (unsigned long i = 0; i < this->get_size(); ++i) {
            this->body[i] += other;
        }
        return *this;
    }

    Vector<T>& operator-=(const Vector<T>& other) {
        assert(get_size() == other.get_size());
        for (unsigned long i = 0; i != this->get_size(); i++) {
            (*this)[i] -= other[i];
        }
        return *this;
    }

    template <typename S>
    Vector<T>& operator-=(const S& other) {
        for (unsigned long i = 0; i < this->get_size(); ++i) {
            this->body[i] -= other;
        }
        return *this;
    }

    Vector<T>& operator*=(const Vector<T>& other) {
        assert(get_size() == other.get_size());
        for (unsigned long i = 0; i != this->get_size(); i++) {
            (*this)[i] *= other[i];
        }
        return *this;
    }

    Vector<T> operator*(const Vector<T>& other) {
        assert(get_size() == other.get_size());
        Vector<T> result(this);
        result *= other;
        return result;
    }

    template <typename S>
    Vector<T> operator-(const S& decrement) const {
        Vector<T> result(this);
        result -= decrement;
        return result;
    }

    template <typename S>
    Vector<T> operator+(const S& addition) const {
        Vector result(this);
        result += addition;
        return result;
    }

    template <typename S>
    Vector matrix_multiply(const Matrix<S>& other) {
        assert(get_size() == other.get_height());
        Vector<T> result(other.get_width());
        for (std::size_t i = 0; i < other.get_width(); ++i) {
            result[i] = body[0] * other(0, i);
            for (std::size_t j = 1; j < get_size(); ++j) {
                result[i] += body[j] * other(j, i);
            }
        }
        return result;
    };

    std::string to_string() {
        std::string result = "";
        for (std::size_t i = 0; i < size; ++i) {
            result += std::to_string(body[i]) + " ";
        }
        return result;
    }
    std::size_t get_size() const { return size; }

   private:
    T* body = nullptr;
    std::size_t size;
};
}  // namespace nvec
