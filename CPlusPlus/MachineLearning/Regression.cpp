#include <iostream>
#include <stdio.h>
#include "../Matrix/Matrix.cpp"
#include <cmath>

using std::cout;
using std::endl;

// Creates matrix with dimentions (inputs.cols_ + 1, 1) that correspond to coeficients of regression line
// out = lr(0, 0)x + lr(1, 0)y + ... + lr(input.cols_+1, 0)
// bool linear set to true will perform regression on linear data
// bool linear set to false will perform polynomial regression with order inputs.cols_
// poly regression will be returned in the order ax + bx^2 + cx^3 + ... + C(constant)
Matrix regress(Matrix inputs, Matrix outputs, bool linear = true) {
    // Creates matrix a with dimentions r, c+1
    Matrix a(inputs.getRows(), inputs.getCols() + 1);
    // Sets a values to input values and sets extra column to ones
    for (int i = 0; i < a.getRows(); i++) {
        for (int j = 0; j < a.getCols(); j++) {
            (j < inputs.getCols()) ? a(i, j) = inputs(i, j) : a(i, j) = 1;
            // If using poly regression raise element[i][j] to jth power
            a(i, j) = pow(a(i, j), j + 1) * !linear;
        }
    }
    // Multiple regression formula
    Matrix aT = a.transpose();
    Matrix p = aT * a;
    Matrix pInverse = p.invert();
    Matrix c = aT * outputs;
    Matrix final = pInverse * c;
    return final;
}

int main() {

    double arr[12] = { 1, 1, 1, 1, 4, 2, 7, 4, 2 , 3, 8, 2 };
    double arr2[4] = { 16, 90, 126, 294 };

    Matrix inputs(arr, 4, 3);
    Matrix outputs(arr2, 4, 1);

    cout << inputs << endl << outputs << endl;

    Matrix eq = regress(inputs, outputs, false);

    cout << eq;

    return 0;
}
