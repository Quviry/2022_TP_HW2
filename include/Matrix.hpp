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
    template <std::size_t size_h = 0, std::size_t size_w = (0)>
    Matrix() {
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
        col_num = size_h;
        row_num = size_w;
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
    T& operator()(std::size_t row, std::size_t col) {
        return this->body[col_num * row + col];
    }

    Matrix operator+(Matrix& a) {
        assert(get_height() == a.get_height());
        assert(get_width() == a.get_width());
        Matrix new_matrix{*this};

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
        Matrix new_matrix{*this};

        for (std::size_t i = 0; i < row_num; ++i) {
            for (std::size_t j = 0; j < col_num; ++j) {
                new_matrix(i, j) -= a(i, j);
            }
        }
        return new_matrix;
    }

    const std::size_t get_height() { return row_num; }

    const std::size_t get_width() { return col_num; }

    Vector<T> operator[](int row) { return get_Vector(row); }
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
    // Row<T> get_row(int row) { return Row(body + col_num * row, col_num); }
    Vector<T> get_Vector(int col) {
        T* Vector_body = new T[row_num];
        for (std::size_t i = 0; i < row_num; ++i) {
            Vector_body[i] = body[i * col_num + col];
        }
        Vector<T> result = Vector<T>(Vector_body, row_num);
        delete[] Vector_body;
        return result;
    };

    void reshape(const unsigned int height, const unsigned int width);
    ~Matrix() { delete this->body; }

   private:
    std::size_t col_num;
    std::size_t row_num;
    T* body = nullptr;
};
/*
        template <typename T, std::size_t size>
        Matrix::Matrix<T><Vector<T>>(const T (&src)[size]){
                col_num = size;
                row_num = 1;
                this->body = new T[size];
                for(int i = 0; i < size; ++i){
                        this->body[i] = src[i];
                }
        }*/

// template <std::size_t size>
// Matrix::Matrix<Row<T>>(const T (&src)[size]){
// 	col_num = size;
// 	row_num = 1;
// 	this->body = new T[size];
// 	for(int i = 0; i < size; ++i){
// 		this->body[i] = src[i];
// 	}

}  // namespace nvec
