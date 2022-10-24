#include <iostream>

#include "Matrix.hpp"

void print(std::string msg){
	std::cout << msg << std::endl;
}

int main(){

	print("### Set up matrix ###");
	nvec::Matrix a({{1, 2 , 3}, {4, 5, 6 }, {7, 8, 9}});
	std::cout << a.to_string()  << std::endl;
	print("### Set up ended ###");

	print("> Test #1");

	print("Index assess");
	print("Value at pos (1, 1): ");
	std::cout << a(1, 1)  << std::endl;
	print("Value at pos [1][1]: ");
	std::cout << a[1][1]  << std::endl;
	print("Change value at pos (1, 1): ");
	a(1, 1) = 10;
	std::cout << a(1, 1)  << std::endl;
	print("Change value at pos [1][1] is not allowed");
	auto c = a[1][1];
	c = 11;
	std::cout << a[1][1]  << std::endl;
	print("Subelements assess");
	std::cout << a.to_string()  << std::endl;
	print("Diagonal assess");
	std::cout << a.get_diagonal().to_string()  << std::endl;
	print("Row n assess");
	std::cout << a[1].to_string()  << std::endl;
	print("Column n assess");
	std::cout << a.get_column(1).to_string()  << std::endl;

	print("> Test #2");
	print("Type transformation");
	std::cout << nvec::Column({1, 2 , 3, 4}).to_string()  << std::endl;
	std::cout << nvec::Row({1, 2 , 3, 4}).to_string()  << std::endl;
	// std::cout << nvec::Matrix({nvec::Row({1, 2}), nvec::Row({1, 2})}).to_string()  << std::endl;  ToDo


	print("> Test #3");

	print("Math in same size objects");
	nvec::Matrix first_({{1, 2}, {3, 4}});
	std::cout << first_.to_string() << std::endl;

	nvec::Matrix second_({{5, 6}, {7, 8}});
	std::cout << second_.to_string() << std::endl;

	print("> first + second");
	std::cout << (first_ + second_).to_string() << std::endl;


	print("> first - second");
	std::cout << (first_ - second_).to_string() << std::endl;

	print("> Test #4");
	print("> Test #5");
	print("> Test #6");
	print("> Test #7");
	print("> Test #8");
	print("> Test #9");
	
	std::cout << "somethn" << std::endl;
	/*
	std::cout << a.to_string()  << std::endl;
	std::cout << a[1][2]  << std::endl;
	auto b = a[1][2];
	b = 10;
	std::cout << b  << std::endl;
	std::cout << a[1][2]  << std::endl;
	auto c = a(1, 2);
	c = 10;
	std::cout << a[1][2]  << std::endl;
	a(1, 2) = 10;
	std::cout << a[1][2]  << std::endl; return Column(subarray(data, col_num*row, col_num*(row+1)));
	std::cout << a.to_string() << std::endl;*/
	return 0;
} 