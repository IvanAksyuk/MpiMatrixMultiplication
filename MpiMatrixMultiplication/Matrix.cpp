#include "Matrix.h"

Matrix::Matrix(double** A_, int shape_[2]) : rows(shape_[0]), cols(shape_[1])
{
	this->A = new double*[shape_[0]];
	for (int i = 0; i < shape_[0]; i++) {
		this->A[i] = new double[shape_[1]];
		for (int j = 0; j < cols; j++) {
			A[i][j] = A_[i][j];
		}
	}
	

	

}
Matrix::Matrix(): rows(1), cols(1)
{
	this->A = new double*[rows];
	this->A[0] = new double[cols];
	A[0][0] = 0;

}

Matrix::Matrix(int shape_[2]): rows(shape_[0]), cols(shape_[1])
{
	this->A = new double* [shape_[0]];
	for (int i = 0; i < shape_[0]; i++) {
		this->A[i] = new double[shape_[1]];
		for (int j = 0; j < cols; j++) {
			A[i][j] = 0;
		}
	}
	
}

Matrix::Matrix(double a, int shape_[2]) : rows(shape_[0]), cols(shape_[1])
{
	this->A = new double* [rows];
	for (int i = 0; i < rows; i++) {
		this->A[i] = new double[cols];
		for (int j = 0; j < cols; j++) {
			A[i][j] = a;
		}
	}
	
	
}
Matrix::Matrix( int m, int n): rows(m), cols(n)
{
	
	this->A = new double* [rows];
	for (int i = 0; i < rows; i++) {
		this->A[i] = new double[cols];
		for (int j = 0; j < cols; j++) {
			A[i][j] = 0;
		}
	}
}

Matrix::Matrix(char type, int m, int n) : rows(m), cols(n)
{
	this->A = new double* [rows];
	for (int i = 0; i < rows; i++) {
		this->A[i] = new double[cols];
		for (int j = 0; j < cols; j++) {
			A[i][j] = (double)(rand())/RAND_MAX;
		}
	}

}


Matrix::Matrix(double a, int m, int n) : rows(m), cols(n)
{	
	this->A = new double* [rows];
	for (int i = 0; i < rows; i++) {
		this->A[i] = new double[cols];
		for (int j = 0; j < cols; j++) {
			A[i][j] = a;
		}
	}

}

Matrix::Matrix(double** A_, int m, int n) : rows(m), cols(n)
{
	this->A = new double* [rows];
	for (int i = 0; i < rows; i++) {
		this->A[i] = new double[cols];
		for (int j = 0; j < cols; j++) {
			A[i][j] = A_[i][j];
		}
	}
}

void Matrix::setAij(double Aij, int i, int j)
{
	A[i][j] = Aij;
}


void Matrix::setA(double ** A_)
{
	for (int i = 0; i < getShape()[0]; i++) {
		for (int j = 0; j < getShape()[1]; j++) {
			this->setAij(A_[i][j], i, j);

		}
	}

}

void Matrix::setA(double a)
{
	for (int i = 0; i < Matrix::getShape()[0]; i++) {
		for (int j = 0; j < Matrix::getShape()[1]; j++) {
			this->setAij(a, i, j);

		}
	}
}



Matrix Matrix::dot(Matrix B)
{
	int shape[2] = { this->getShape()[0], B.getShape()[1] };

	Matrix C(shape);
	
	for (int i = 0; i < getShape()[0]; i++) {
		for (int j = 0; j < B.getShape()[1]; j++) {
			double c = 0;
			for (int k = 0; k < B.getShape()[0]; k++) {
				c += A[i][k] * B.getAij(k,j);
			}
			C.setAij(c, i, j);
		}
	}
	

	return C;
}
