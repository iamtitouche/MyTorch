//
// Created by dev on 01/10/2024.
//

#ifndef DENSE_H
#define DENSE_H
#include <tensor.h>

enum Init_Mode {
    ZERO,
    XAVIER_NORMAL,
    KAIMING_NORMAL,
    LECUN
};

class dense {
public:
    dense(size_t input_size, size_t output_size, Init_Mode mode=XAVIER_NORMAL);

    tensor forward(tensor input);

private:
    tensor weights;
    tensor biases;
};

#endif //DENSE_H
