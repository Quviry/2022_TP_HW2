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

    
    T operator[](int pos) { return this->body[pos]; }
    
    std::string to_string() {
        std::string result = "";
        for (std::size_t i = 0; i < size; ++i) {
            result += std::to_string(body[i]) + " ";
        }
        return result;
    }
    const std::size_t get_size() { return size; }

   private:
    T* body = nullptr;
    std::size_t size;
};
}  // namespace nvec
