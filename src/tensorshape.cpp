#include <iostream>
#include <sstream>
#include <utility>
#include <cstdint>
#include <numeric>

#include "../headers/tensorshape.h"

using namespace std;

tensorShape::tensorShape(vector<size_t> shape_vector) {
    if (shape_vector.empty()) throw invalid_argument("Error : Shape cannot be empty.");

    for (const auto& dim : shape_vector) {
        if (dim == 0) throw invalid_argument("Error : Dimensions must be greater than 0.");
    }

    shape = vector<size_t>(shape_vector);
}

size_t tensorShape::getSize() const {
    return accumulate(shape.begin(), shape.end(), 1, multiplies<>());
}

string tensorShape::toString() const {
    stringstream ss;
    ss << "tensorShape [";
    for (size_t i = 0; i < shape.size(); ++i) {
        ss << shape[i];
        if (i != shape.size() - 1) {
            ss << ", ";
        }
    }
    ss << "]";
    return ss.str();
}

vector<size_t> tensorShape::getShape() const {
    return shape;
}


bool tensorShape::sameSize(const tensorShape &other) const {
    return getSize() == other.getSize();
}

bool tensorShape::operator==(const tensorShape &other) const {
    return shape.size() == other.shape.size() && equal(shape.begin(), shape.end(), other.shape.begin());
}

bool tensorShape::operator!=(const tensorShape &other) const {
    return !(*this == other);
}

void tensorShape::squeeze(optional<int> dim) {
    if (dim) { // If a specific dimension is provided
        const int d = dim.value();
        if (d < 0 || d >= static_cast<int>(shape.size())) {
            throw out_of_range("Dimension out of range");
        }
        if (shape[d] != 1) {
            throw invalid_argument("This tensorShape cannot be squeezed on this dimension");
        }
        if (shape.size() == 1) return;

        shape.erase(shape.begin() + d);

    } else { // If no dimension is provided, squeeze all dimensions of size 1
        if (shape.size() == 1) return;
        vector<size_t> new_shape;
        for (size_t i = 0; i < shape.size(); ++i) {
            if (shape[i] != 1) {
                new_shape.push_back(shape[i]);
            }
        }
        shape = new_shape;
    }
}


void tensorShape::unsqueeze(int dim) {
    shape.insert(shape.begin() + dim, 1);
}


bool tensorShape::isConcatCompatible(const tensorShape &other, int dim) const {
    if (shape.size() != other.shape.size()) return false;

    for (size_t i = 0; i < shape.size(); ++i) {
        if (i != dim && shape[i] != other.shape[i]) return false;
    }

    return true;
}


