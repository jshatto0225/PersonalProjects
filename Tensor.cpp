#include <iostream>
#include "Matrix.cpp"

using namespace std;

class Tensor{
    private:
        int depth;
        int rows;
        int columns;
        Matrix* tensor;
    public:
        Tensor(){}
        Tensor(int d, int r, int c){
            depth, rows, columns = d, r, c;
        }
        void setValue(int d, int r, int c){
            
        }
};
