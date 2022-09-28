#include <iostream>
#include <stdio.h>
#include "../Matrix/Matrix.cpp"

using namespace std;

// Creates matrix with dimentions (inputs.cols_ + 1, 1) that correspond to coeficients of regression line
// out = lr(0, 0)x + lr(1, 0)y + ... + lr(input.cols_+1, 0)
Matrix lr(Matrix inputs, Matrix outputs) {
    // Creates matrix a with dimentions r, c+1
    Matrix a(inputs.getRows(), inputs.getCols() + 1);
    // Sets a values to input values and sets extra column to ones
    for (int i = 0; i < a.getRows(); i++) {
        for (int j = 0; j < a.getCols(); j++) {
            (j < inputs.getCols()) ? a(i, j) = inputs(i, j) : a(i, j) = 1;
        }
    }
    // Linear regression formula
    Matrix aT = a.transpose();
    Matrix p = aT * a;
    Matrix pInverse = p.invert();
    Matrix c = aT * outputs;
    Matrix final = pInverse * c;
    return final;
}

int main() {

    double arr[6] = { 1, 1, 1, 2, 2, 2 };
    double arr2[3] = { 7, 10, 14 };

    Matrix inputs(arr, 3, 2);
    Matrix outputs(arr2, 3, 1);

    cout << inputs << endl << outputs << endl;

    Matrix eq = lr(inputs, outputs);

    cout << eq;

    return 0;
}
