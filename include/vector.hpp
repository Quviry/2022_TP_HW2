#include <string>

namespace nvec {

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
    Vector(std::size_t size) : size(size), body(new T[size]) {}
    Vector(const Vector<T>& src) {
        T* body = new T[src.get_size()];
        size = src.get_size();
        for (unsigned long i = 0; i != size; i++) {
            body[i] = src[i];
        }
    }
    Vector(const T* src, std::size_t size) {
        this->size = size;
        this->body = new T[size];
        for (int i = 0; i < size; ++i) {
            this->body[i] = src[i];
        }
    }
    template <std::size_t size>
    Vector(const T (&src)[size]) {
        this->size = size;
        this->body = new T[size];
        for (int i = 0; i < size; ++i) {
            this->body[i] = src[i];
        }
    }
    ~Vector() { delete[] this->body; };

    const T& operator[](int pos) const { return this->body[pos]; }
    T& operator[](int pos) { return this->body[pos]; }

    bool operator==(const Vector<T>& other) const {
        for (unsigned long i = 0; i != this->get_size(); i++) {
            if ((*this)[i] != other[i]) {
                return false;
            }
        }
        return true;
    }

    Vector<T>& operator+=(const Vector<T>& other) {
        for (unsigned long i = 0; i != this->get_size(); i++) {
            this[i] += other[i];
        }
        return this;
    }

    Vector<T>& operator+(const Vector<T>& other) const {
        Vector<T> result(this);
        for (unsigned long i = 0; i != result.get_size(); i++) {
            result[i] += other[i];
        }
        return result;
    }

    Vector<T>& operator-=(const Vector<T>& other) {
        for (unsigned long i = 0; i != this->get_size(); i++) {
            this[i] -= other[i];
        }
        return this;
    }

    Vector<T>& operator-(const Vector<T>& other) {
        Vector<T> result(this);
        for (unsigned long i = 0; i != result.get_size(); i++) {
            result[i] -= other[i];
        }
        return result;
    }

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
