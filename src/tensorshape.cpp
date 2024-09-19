#include <sstream>
#include <utility>

#include "../headers/tensorshape.h"

using namespace std;

tensorShape::tensorShape(vector<uint32_t> shape) {
    if (shape.empty()) throw invalid_argument("Error : Shape cannot be empty.");

    for (const auto& dim : shape) {
        if (dim == 0) throw invalid_argument("Error : Dimensions must be greater than 0.");
    }
    this->shape = move(shape);
}

uint32_t tensorShape::getSize() const {
    uint32_t size = 1;
    for (int i = 0; i < this->shape.size(); i++) {
        size *= this->shape[i];
    }
    return size;
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

vector<uint32_t>& tensorShape::getShape() {
    return shape;
}

bool tensorShape::sameShape(const tensorShape &other) const {
    if (shape.size() != other.shape.size()) return false;

    for (int i = 0; i < this->shape.size(); i++) {
        if (shape[i] != other.shape[i]) return false;
    }

    return true;
}

bool tensorShape::sameSize(const tensorShape &other) const {
    return getSize() == other.getSize();
}

bool tensorShape::operator==(const tensorShape &other) const {
    if (shape.size() != other.shape.size()) return false;

    for (int i = 0; i < shape.size(); i++) {
        if (shape[i] != other.shape[i]) return false;
    }

    return true;
}

bool tensorShape::operator!=(const tensorShape &other) const {
    return !(*this == other);
}

void tensorShape::squeeze(optional<int> dim) {
    if (shape.size() == 1) return;

    if (dim) { // If a specific dimension is provided
        int d = dim.value();
        if (d < 0 || d >= static_cast<int>(shape.size())) {
            throw out_of_range("Dimension out of range");
        }
        if (shape[d] == 1) {
            shape.erase(shape.begin() + d);
        }
    } else { // If no dimension is provided, squeeze all dimensions of size 1
        vector<uint32_t> new_shape;
        for (size_t i = 0; i < shape.size(); i++) {
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

