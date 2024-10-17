//
// Created by dev on 01/10/2024.
//

#include "relu.h"

tensor ReLU::forward(const tensor& input) {
    auto result = tensor(input);

    for (size_t i = 0; i < input.getData().size(); i++) {
        if (input.getData()[i] < 0) {
            input.getData()[i] = 0;
        }
    }

    return result;
}
