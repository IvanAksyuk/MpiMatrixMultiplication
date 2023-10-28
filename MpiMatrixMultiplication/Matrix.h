
#include <iostream>
#include <string.h>

class Matrix {


	int rows, cols;
	double** A;
	
public:

	Matrix();
	Matrix(double** A_, int shape_[2]);
	Matrix(int shape_[2]);
	Matrix(double a, int shape_[2]);
	Matrix(double a, int m, int n);
	Matrix(double** A_, int m, int n);
	Matrix(int m, int n);
	Matrix(char type, int m, int n);

	void setAij(double Aij, int i, int j);

	
	void setA(double** A_);
	void setA(double a);


	double getAij(int i, int j) {
		return A[i][j];
	}
	int* getShape() {
		
		return new int[2] {rows, cols};
	}

	void info() {
		std::cout << "Matrix:" << "\n";
		std::cout << "Shape: " << Matrix::getShape()[0] << " " << Matrix::getShape()[1] << "\n";
		for (int i = 0; i < std::min(rows, rows); i++) {
			for (int j = 0; j < std::min(cols, cols); j++) {
				std::cout << getAij(i,j) << " ";
			}
			std::cout << "\n";
		}
		
	}

	Matrix dot(Matrix B);

};
