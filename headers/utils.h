//
// Created by dev on 01/10/2024.
//

#ifndef UTILS_H
#define UTILS_H
#include <vector>


using namespace std;

vector<double> normal(size_t size, double mean, double stddev);

void followNormal(double mean, double stddev, vector<double> input);


#endif //UTILS_H
