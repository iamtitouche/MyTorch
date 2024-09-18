#include <sstream>
#include <utility>

#include "../headers/tensorshape.h"

using namespace std;

tensorShape::tensorShape(vector<uint32_t> shape) {
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
