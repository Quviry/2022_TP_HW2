#include "Row.hpp"
#include "Column.hpp"
#include "tools.hpp"
#include <cassert>

#pragma once

namespace nvec{
	template <typename T>
	class Matrix{
	public:
		template <size_t size_h, size_t size_w>
		Matrix(){
			this->data = new T[size_h, size_w];
			col_num = size_h;
			row_num = size_w;
		};
		Matrix(const Matrix& src){
			col_num = src.col_num;
			row_num = src.row_num;
			size_t virtual_size = col_num * row_num;

			this->data = new T[virtual_size];
			for(size_t i = 0; i < virtual_size; ++i){

				this->data[i] = std::move(src.data[i]);
			}
		}
		template <size_t size_h, size_t size_w>
		Matrix(const T (&src)[size_h][size_w]){
		size_t virtual_size = size_h * size_w;
		this->data = new T[virtual_size];
		for(size_t i = 0; i < size_h; ++i){
			for(size_t j = 0; j < size_w; ++j){
				this->data[size_w*i + j] = src[i][j];
			}
		}
		col_num = size_h;
		row_num = size_w;
		}

		template <size_t size>
		Matrix(const T (&src)[size]){
			col_num = size;
			row_num = 1;
			this->data = new T[size];
			for(int i = 0; i < size; ++i){
				this->data[i] = src[i];
			}
		}
		T& operator()(size_t row, size_t col){
			return this->data[col_num*row + col];
		}

		Matrix operator+( Matrix& a) {
			assert(get_height() == a.get_height());
			assert(get_width() == a.get_width());
			Matrix new_matrix{*this};
			
			for(size_t i = 0; i < row_num; ++i){
				for(size_t j = 0; j < col_num; ++j){
					new_matrix(i, j) += a(i, j);
				}
			}
			return new_matrix;
		}

		Matrix operator-( Matrix& a) {
			assert(get_height() == a.get_height());
			assert(get_width() == a.get_width());
			Matrix new_matrix{*this};
			
			for(size_t i = 0; i < row_num; ++i){
				for(size_t j = 0; j < col_num; ++j){
					new_matrix(i, j) -= a(i, j);
				}
			}
			return new_matrix;
		}
		
		const size_t get_height(){
			return row_num;
		}

		const size_t get_width(){
			return col_num;
		}
		
		Row<T> operator[](int row){
			return get_row(row);
		}
		std::string to_string(){
			std::string result = "";
			for(size_t i = 0; i < col_num; ++i){
				for(size_t j = 0; j < row_num; ++j){
					result +=  std::to_string(data[row_num * i + j]) + " ";
				}
				result += "\n";
			} 
			return result;
		}
		Column<T> get_diagonal(){
			size_t diagonal_size = min(col_num, row_num);
			T* column_data = new T[diagonal_size];
			for(size_t i = 0; i < diagonal_size; ++i){
				column_data[i] = data[i*col_num+i];
			}
			Column<T> col =  Column(column_data, diagonal_size);
			delete column_data;
			return col;
		}
		Row<T> get_row(int row){
			return Row(data + col_num*row, col_num);
		}
		Column<T> get_column(int col){
			T* column_data = new T[row_num];
			for(size_t i = 0; i < row_num; ++i){
				column_data[i] = data[i*col_num + col];
			}
			Column<T> result =  Column(column_data, row_num);
			delete column_data;
			return result;
		};

		void reshape(const unsigned int height, const unsigned int width);
		~Matrix(){
			delete this->data;
		}

	private:
		size_t col_num;
		size_t row_num;
		T* data;
	};
/*
	template <typename T, size_t size>
	Matrix::Matrix<T><Column<T>>(const T (&src)[size]){
		col_num = size;
		row_num = 1;
		this->data = new T[size];
		for(int i = 0; i < size; ++i){
			this->data[i] = src[i];
		}
	}*/

	// template <size_t size>
	// Matrix::Matrix<Row<T>>(const T (&src)[size]){
	// 	col_num = size;
	// 	row_num = 1;
	// 	this->data = new T[size];
	// 	for(int i = 0; i < size; ++i){
	// 		this->data[i] = src[i];
	// 	}

}

