#include "dense.h"
#include "tensor.h"

#include <math.h>


dense::dense(size_t input_size, size_t output_size, const Init_Mode mode):
    weights(tensor(tensorShape({input_size, output_size}))),
    biases(tensor(tensorShape({1, output_size}))) {

    switch (mode) {
        case ZERO: {
            break;
        }
        case XAVIER_NORMAL: {
            // Xavier/Glorot Normal
            const double stddev = sqrt(2 / (input_size + output_size));

            weights.initNormal(0, stddev);
            biases.initNormal(0, stddev);
            break;
        }
        case KAIMING_NORMAL: {
            // Kaiming/He Normal
            const double stddev = sqrt(2 / input_size);

            weights.initNormal(0, stddev);
            biases.initNormal(0, stddev);
            break;
        }
        case LECUN: {
            const double stddev = sqrt(1 / input_size);

            weights.initNormal(0, stddev);
            biases.initNormal(0, stddev);
        }
    }
}
