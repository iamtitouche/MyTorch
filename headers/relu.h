//
// Created by dev on 01/10/2024.
//

#ifndef RELU_H
#define RELU_H

#include "tensor.h"

class ReLU {
    public:
        static tensor forward(const tensor& input);
};

#endif //RELU_H
