#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <stdlib.h>
#include <iostream>

class Matrix {
    public:
    Matrix(int, int);
    Matrix(double**, int, int);
    Matrix(double [ ], int, int);
    Matrix();
    Matrix(const Matrix&);
    ~Matrix();

    Matrix& operator=(const Matrix&);
    inline double& operator()(int x, int y) { return p[x][y]; }
    Matrix& operator+=(const Matrix&);
    Matrix& operator-=(const Matrix&);
    Matrix& operator*=(double);
    Matrix& operator*=(const Matrix&);
    Matrix& operator/=(double);

    friend std::ostream& operator<<(std::ostream&, const Matrix&);
    friend std::istream& operator>>(std::istream&, Matrix&);

    void swapRows(int, int);
    Matrix transpose();

    static Matrix createIdentity(int);

    static Matrix augment(Matrix, Matrix);
    Matrix ref();
    Matrix rref();
    Matrix invert();

    Matrix scaleRow(Matrix&, int, double);
    double* subtract(double*, double*);
    double* add(double*, double*);

    int getRows() { return rows_; }
    int getCols() { return cols_; }

    private:
    int rows_, cols_;
    double** p;
    void allocateSpace();
};

Matrix operator+(const Matrix&, const Matrix&);
Matrix operator-(const Matrix&, const Matrix&);
Matrix operator*(const Matrix&, const Matrix&);
Matrix operator*(const Matrix&, double);
Matrix operator*(double, const Matrix&);
Matrix operator/(const Matrix, double);

#endif
