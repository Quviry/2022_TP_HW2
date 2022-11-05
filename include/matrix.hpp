#include <cassert>
#include <string>

#include "tools.hpp"
#include "vector.hpp"

#pragma once

namespace nvec {
template <typename T>
#if __cplusplus >= 202002L
requires requires(T x) {
    x + x;
}
requires requires(T x) { x - x; }
requires requires(T x) { x* x; }
#endif
class Matrix {
   public:
    template <std::size_t size_h = 1, std::size_t size_w = 1>
    Matrix() {
        this->body = new T[size_h * size_w];
        col_num = size_h;
        row_num = size_w;
    };
    Matrix(std::size_t size_h = 1, std::size_t size_w = 1) {
        this->body = new T[size_h * size_w];
        col_num = size_h;
        row_num = size_w;
    };
    Matrix(const Matrix& src) {
        col_num = src.col_num;
        row_num = src.row_num;
        std::size_t virtual_size = col_num * row_num;

        this->body = new T[virtual_size];
        for (std::size_t i = 0; i < virtual_size; ++i) {
            this->body[i] = std::move(src.body[i]);
        }
    }
    template <std::size_t size_h, std::size_t size_w>
    Matrix(const T (&src)[size_h][size_w]) {
        std::size_t virtual_size = size_h * size_w;
        this->body = new T[virtual_size];
        for (std::size_t i = 0; i < size_h; ++i) {
            for (std::size_t j = 0; j < size_w; ++j) {
                this->body[size_w * i + j] = src[i][j];
            }
        }
        col_num = size_w;
        row_num = size_h;
    }
    template <std::size_t size>
    Matrix(const T (&src)[size]) {
        col_num = size;
        row_num = 1;
        this->body = new T[size];
        for (int i = 0; i < size; ++i) {
            this->body[i] = src[i];
        }
    }
    template <std::size_t size>
    Matrix(const Vector<T> (&src)[size]) {
        col_num = size;
        row_num = src[0].get_size();
        this->body = new T[col_num * row_num];
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < row_num; ++j) {
                this->body[i * col_num + j] = src[i][j];
            }
        }
    }
    ~Matrix() { delete[] this->body; }
    T& operator()(std::size_t row, std::size_t col) const {
        return this->body[col_num * row + col];
    }
    Vector<T> operator[](int row) const { return get_row(row); }
    bool operator==(const Matrix& other) const {
        assert(get_height() == other.get_height());
        assert(get_width() == other.get_width());

        for (std::size_t i = 0; i < row_num; ++i) {
            for (std::size_t j = 0; j < col_num; ++j) {
                if ((*this)(i, j) != other(i, j)) {
                    return false;
                }
            }
        }
        return true;
    }

    Matrix<T>& operator*=(const Matrix<T>& other) {
        assert(get_height() == other.get_height());
        assert(get_width() == other.get_width());
        for (unsigned long i = 0; i != row_num; i++) {
            for (unsigned long j = 0; j != col_num; j++) {
                body[i * col_num + j] *= other[i][j];
            }
        }
        return *this;
    }

    template <typename S>
    Matrix<T>& operator*=(const S other) {
        for (unsigned long i = 0; i != row_num; i++) {
            for (unsigned long j = 0; j != col_num; j++) {
                body[i * col_num + j] *= other;
            }
        }
        return *this;
    }

    Matrix<T> operator*(const Matrix<T>& other) {
        Matrix<T> result(*this);
        result *= other;
        return result;
    }

    template <typename S>
    Matrix<T> operator*(const S other) {
        Matrix<T> result(*this);
        result *= other;
        return result;
    }

    Matrix operator+(Matrix& a) {
        assert(get_height() == a.get_height());
        assert(get_width() == a.get_width());
        Matrix new_matrix(*this);

        for (std::size_t i = 0; i < row_num; ++i) {
            for (std::size_t j = 0; j < col_num; ++j) {
                new_matrix(i, j) += a(i, j);
            }
        }
        return new_matrix;
    }

    Matrix operator-(Matrix& a) {
        assert(get_height() == a.get_height());
        assert(get_width() == a.get_width());
        Matrix new_matrix(*this);

        for (std::size_t i = 0; i < row_num; ++i) {
            for (std::size_t j = 0; j < col_num; ++j) {
                new_matrix(i, j) -= a(i, j);
            }
        }

        return new_matrix;
    }

    template <typename S>
    Vector<T> matrix_multiply(const Vector<S>& other) {
        assert(row_num == other.get_size());
        Vector<T> result(row_num);
        for (std::size_t i = 0; i < row_num; ++i) {
            result[i] = T();
            for (std::size_t j = 0; j < col_num; ++j) {
                result[i] += (*this)(i, j) * other[j];
            }
        }
        return result;
    }

    Matrix matrix_multiply(const Matrix& other) {
        assert(get_width() == other.get_height());
        Matrix<T> result(get_height(), other.get_width());
        for (std::size_t i = 0; i < get_height(); ++i) {
            for (std::size_t j = 0; j < other.get_width(); ++j) {
                result(i, j) = (*this)(i, 0) * other(0, j);
                for (std::size_t k = 1; k < get_width(); ++k) {
                    result(i, j) += (*this)(i, k) * other(k, j);
                }
            }
        }
        return result;
    }

    const std::size_t get_height() const { return row_num; }

    const std::size_t get_width() const { return col_num; }

    std::string to_string() {
        std::string result = "";
        for (std::size_t i = 0; i < col_num; ++i) {
            for (std::size_t j = 0; j < row_num; ++j) {
                result += std::to_string(body[row_num * i + j]) + " ";
            }
            result += "\n";
        }
        return result;
    }
    Vector<T> get_diagonal() {
        std::size_t diagonal_size = min(col_num, row_num);
        T* Vector_body = new T[diagonal_size];
        for (std::size_t i = 0; i < diagonal_size; ++i) {
            Vector_body[i] = body[i * col_num + i];
        }
        Vector<T> col = Vector<T>(Vector_body, diagonal_size);
        delete[] Vector_body;
        return col;
    }
    Vector<T> get_row(int row) const {
        return Vector<T>(body + col_num * row, col_num);
    };

    Vector<T> get_column(int col) {
        T* Vector_body = new T[row_num];
        for (std::size_t i = 0; i < row_num; ++i) {
            Vector_body[i] = body[i * col_num + col];
        }
        Vector<T> result = Vector<T>(Vector_body, row_num);
        delete[] Vector_body;
        return result;
    };

   private:
    std::size_t col_num;
    std::size_t row_num;
    T* body = nullptr;
};
}  // namespace nvec
