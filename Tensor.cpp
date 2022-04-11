#include <iostream>
#include "Matrix.cpp"

using namespace std;

class Tensor{
    private:
        int depth;
        Matrix* tensor;
    public:
        Tensor(){}
        Tensor(int d, Matrix m[]){
            depth = d;
            tensor = m;
        }
        void setValue(int d, int r, int c, float val){
            tensor[d].setVal(r, c, val);
        }
        float getVal(int d, int r, int c){
            return tensor[d].getVal(r, c);
        }
};

int main(){
    return 0;
}
