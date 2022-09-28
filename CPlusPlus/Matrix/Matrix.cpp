#include "Matrix.h"

using std::endl;
using std::istream;
using std::ostream;

// Constructors
// Initializes matrix of size row, cols to 0
Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
    allocateSpace();
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            p[i][j] = 0;
        }
    }
}
// Initializes matrix from double pointer
Matrix::Matrix(double** m, int rows, int cols) : rows_(rows), cols_(cols) {
    allocateSpace();
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            p[i][j] = m[i][j];
        }
    }
}
// Initializes matrix from array
Matrix::Matrix(double arr [ ], int r, int c) : rows_(r), cols_(c) {
    allocateSpace();
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            p[i][j] = arr[(i * (cols_)) + j];
        }
    }
}
// Initializes matrix of size 1, 1 to 0
Matrix::Matrix() : rows_(1), cols_(1) {
    p[0][0] = 0;
}
// Initializes matrix with values from matrix passed in
Matrix::Matrix(const Matrix& m) : rows_(m.rows_), cols_(m.cols_) {
    allocateSpace();
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            p[i][j] = m.p[i][j];
        }
    }
}
// Deletes matrix attribute p
Matrix::~Matrix() {
    for (int i = 0; i < rows_; i++) {
        delete [ ] p[i];
    }
    delete [ ] p;
}

// Operator overloads
// Copies matrix
Matrix& Matrix::operator=(const Matrix& m) {
    if (this == &m) {
        return *this;
    }
    if (rows_ != m.rows_ || cols_ != m.cols_) {
        for (int i = 0; i < rows_; i++) {
            delete [ ] p[i];
        }
        delete [ ] p;

        rows_ = m.rows_;
        cols_ = m.cols_;
        allocateSpace();
    }
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            p[i][j] = m.p[i][j];
        }
    }
    return *this;
}
// Add matrices
Matrix& Matrix::operator+=(const Matrix& m) {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            p[i][j] += m.p[i][j];
        }
    }
    return *this;
}
// Subtract matrices
Matrix& Matrix::operator-=(const Matrix& m) {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            p[i][j] -= m.p[i][j];
        }
    }
    return *this;
}
// Multiply matrix by scalar or other matrix
Matrix& Matrix::operator*=(double k) {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            p[i][j] *= k;
        }
    }
    return *this;
}
Matrix& Matrix::operator*=(const Matrix& m) {
    Matrix temp(rows_, m.cols_);
    for (int i = 0; i < temp.rows_; i++) {
        for (int j = 0; j < temp.cols_; j++) {
            for (int k = 0; k < cols_; k++) {
                temp(i, j) += (p[i][k] * m.p[k][j]);
            }
        }
    }
    *this = temp;
    return *this;
}
// Devide matrix by scalar
Matrix& Matrix::operator/=(double k) {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            p[i][j] /= k;
        }
    }
    return *this;
}

// Matrix operations
// Swaps matrix rows
void Matrix::swapRows(int r1, int r2) {
    double* temp = p[r1];
    p[r1] = p[r2];
    p[r2] = temp;
}
// Transposes matrix
Matrix Matrix::transpose() {
    Matrix tran(cols_, rows_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            tran.p[j][i] = p[i][j];
        }
    }
    return tran;
}
// Gets matrix to reduced row echelon form
Matrix Matrix::rref() {
    Matrix ref(*this);
    int rows = ref.rows_;
    int cols = ref.cols_;

    int lead = 0;

    while (lead < rows) {
        for (int r = 0; r < rows; r++) {
            int i = r;
            while (ref(i, lead) == 0 && cols > lead) {
                i++;
                if (rows == i) {
                    i = r;
                    lead++;

                }
            }
            ref.swapRows(i, r);
            if (ref(r, lead) != 0) {
                double temp = ref(r, lead);
                for (int c = 0; c < cols; c++) {
                    ref(r, c) /= temp;
                }
            }
            for (i = 0; i < rows; i++) {
                if (i != r) {
                    double temp = ref(i, lead);
                    for (int c = 0; c < cols; c++) {
                        ref(i, c) -= ref(r, c) * temp;
                    }
                }
            }
            lead++;
        }
    }
    return ref;
}
// Inverts matrix
Matrix Matrix::invert() {
    Matrix I = createIdentity(rows_);
    Matrix AI = augment(*this, I);
    Matrix U = AI.rref();
    Matrix inverse(rows_, cols_);
    for (int i = 0; i < inverse.rows_; i++) {
        for (int j = 0; j < inverse.cols_; j++) {
            inverse(i, j) = U(i, j + cols_);
        }
    }
    return inverse;
}
// Creates identity matrix
Matrix Matrix::createIdentity(int n) {
    Matrix temp(n, n);
    for (int i = 0; i < temp.rows_; i++) {
        for (int j = 0; j < temp.cols_; j++) {
            temp.p[i][j] = (i == j);
        }
    }
    return temp;
}
// Augments matrix m1 with matrix m2
Matrix Matrix::augment(Matrix m1, Matrix m2) {
    Matrix aug(m1.rows_, m1.cols_ + m2.cols_);
    for (int i = 0; i < m1.rows_; i++) {
        for (int j = 0; j < m1.cols_ + m2.cols_; j++) {
            aug(i, j) = m1(i, j) * (j < m1.cols_) + m2(i, j - m2.cols_) * (j >= m1.cols_);
        }
    }
    return aug;
}
// Allocates space for p
void Matrix::allocateSpace() {
    p = new double* [rows_];
    for (int i = 0; i < rows_; i++) {
        p[i] = new double[cols_];
    }
}
// Scale row by scalar
Matrix Matrix::scaleRow(Matrix& m, int r, double k) {
    Matrix scaled(m);
    for (int i = 0; i < scaled.cols_; i++) {
        scaled(r, i) = m(r, i) * k;
    }
    return scaled;
}

// General operators
Matrix operator+(const Matrix& m1, const Matrix& m2) {
    Matrix temp(m1);
    return temp += m2;
}
Matrix operator-(const Matrix& m1, const Matrix& m2) {
    Matrix temp(m1);
    return temp -= m2;
}
Matrix operator*(const Matrix& m1, const Matrix& m2) {
    Matrix temp(m1);
    return temp *= m2;
}
Matrix operator*(const Matrix& m, double k) {
    Matrix temp(m);
    return temp *= k;
}
Matrix operator*(double k, const Matrix& m) {
    Matrix temp(m);
    return temp *= k;
}
Matrix operator/(const Matrix m, double k) {
    Matrix temp(m);
    return temp /= k;
}

// IO operators
ostream& operator<<(std::ostream& os, const Matrix& m) {
    for (int i = 0; i < m.rows_; i++) {
        for (int j = 0; j < m.cols_; j++) {
            os << m.p[i][j] << " ";
        }
        os << endl;
    }
    return os;
}
istream& operator>>(std::istream& is, Matrix& m) {
    for (int i = 0; i < m.rows_; i++) {
        for (int j = 0; j < m.cols_; j++) {
            is >> m.p[i][j];
        }
    }
    return is;
}
