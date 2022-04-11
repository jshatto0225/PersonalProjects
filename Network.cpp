#include <iostream>
#include <math.h>
#include<numeric>
using namespace std;

class Network{
    public:
        int numLayers;
        int *numNeurons;
        float biases;
        int numBiases;
        float weights;
        Network(int layers, int sizes[]){
            numNeurons = sizes;
            numLayers = layers;
            biases = createBiases();
            weights = createWeights();
        }
        
    private:
        float createWeights(){
        }
        float createBiases(){
        }
        float normalRandom(){
            unsigned seed = time(0);
	        srand(seed);
	        double x;
	        double u1 = ((double) rand() / (RAND_MAX));
	        double u2 = ((double) rand() / (RAND_MAX));
	        if(u1 == 0){
	        	x = 0;
	        }
	        else{
		        x = sqrt(-2.*log(u1)) * cos(2.*M_PI*u2);
	        }
            return x;
        }
};

int main(){
    int layers[] = {2, 3, 1};
    Network n = Network(3, layers);
}
