#include <iostream>
#include "Vector.cpp"

using namespace std;

class Matrix{
    private:
        int x;
        int y;
        Vector* m;
    public:
        Matrix(){}
        Matrix(int r, int c, Vector* vals){
            x, y = r, c;
            m = new Vector[y];
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

int main(){
    return 0;
}
