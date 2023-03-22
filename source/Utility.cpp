#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Utility.h"
using namespace std;
float Utility::Map(float value, float from1, float to1, float from2, float to2) {
    return (value - from1) / (to1 - from1) * (to2 - from2) + from2;
}

float Utility::RandomRate() {
    
    return (double)rand() / (RAND_MAX);
}

int Utility::RandomRangeInt(int min, int max) {
    
    return min + rand() % (max - min);;
}


