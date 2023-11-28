
#include <iostream>
#include <string.h>

template<int rows=1, int cols=1>
struct Matrix 
{


	
	double** A;
	
	
	Matrix(double** A_)
	{
		A = new double* [rows];
		for (int i = 0; i < rows; i++) {
			A[i] = new double[cols];
			for (int j = 0; j < cols; j++) {
				A[i][j] = A_[i][j];
			}
		}
	}
		
	Matrix(double a) {
		A = new double* [rows];
		for (int i = 0; i < rows; i++) {
			A[i] = new double[cols];
			for (int j = 0; j < cols; j++) {
				A[i][j] = a;
			}
		}
	}
	Matrix() : Matrix((double)0) {}
	
	const double& operator()(int i, int j) const{
	 return A[i][j];
	 }

	double& operator()(int i, int j) { return A[i][j]; }
	
	

	void info(int shape_of_out) {

		std::cout << "Matrix:" << "\n";
		std::cout << "Shape: " << rows << " " << cols << "\n";
		for (int i = 0; i < std::min(shape_of_out, rows); i++) {
			for (int j = 0; j < std::min(shape_of_out, cols); j++) {
				std::cout << (*this)(i, j) << " ";
			}
			std::cout << "\n";
		}
	}

	
	

};


template<int M=1, int N=1, int K=1>
Matrix<M, K> dot(Matrix<M, N> A, Matrix<N, K> B)
{
	Matrix<M, K> C;

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < K; j++) {
			double c = 0;
			for (int k = 0; k < N; k++) {
				c += A(i, k) * B(k, j);
			}
			C(i, j) = c;
		}
	}


	return C;
}
