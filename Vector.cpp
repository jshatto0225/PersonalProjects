#include <iostream>

using namespace std;

class Vector{
    private:
        int s;
        float* vector;
    public:
        Vector(){}
        float getVal(int i){
            return vector[i];
        }
        int size(){
            return s;
        }
        void setVal(int i, float val){
            vector[i] = val;
        }
        void setVector(float v[]){
            vector = v;
        }
};
