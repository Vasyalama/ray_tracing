#ifndef UTILSS_H
#define UTILSS_H
#include <iostream>
#include <random> 

std::default_random_engine generator;
std::uniform_real_distribution<double> distribution(0.0,1.0);
double random_double(){ 
    return distribution(generator);
}


double random_double(double min, double max){
    return min + (max - min) * random_double();
}

#endif