//
// Created by dev on 01/10/2024.
//

#ifndef MODULE_H
#define MODULE_H

#include <vector>
#include <optional>
#include <tensor.h>

using namespace std;

class Function {
    public:
        tensor forward(tensor input);
};

#endif //MODULE_H
