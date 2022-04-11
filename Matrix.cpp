#include <iostream>
#include "Vector.cpp"

using namespace std;

class Matrix{
    private:
        int y;
        Vector* m;
    public:
        Matrix(){}
        Matrix(int r, Vector vals[]){
            y = r;
            m = vals;
        }
        float getVal(int r, int c){
            return m[r].getVal(c);
        }
        void setVal(int r, int c, float val){
            m[r].setVal(c, val);
        }
        void setRow(int r, Vector v){
            m[r] = v;
        }
};
