#include "tensor.h"

#include <iostream>
#include <ostream>

using namespace std;

tensor::tensor(tensorShape shape) : shape(move(shape)), data(shape.getSize(), 0.0) {}

tensor::tensor(tensorShape shape, double value) : shape(move(shape)), data(shape.getSize(), value) {}


tensorShape tensor::getShape() const {
    return shape;
}


bool tensor::sameShape(const tensor &other) const {
    return shape.sameShape(other.shape);
}

bool tensor::sameSize(const tensor &other) const {
    return shape.sameSize(other.shape);
}

void tensor::checkShapes(const tensor &other) const {
    if (!sameShape(other)) {
        throw invalid_argument("Error: shapes of tensors do not match.");
    }
}

tensor tensor::copy() const {
    tensor new_tensor(this->shape);
    new_tensor.data = this->data;
    return new_tensor;
}

// Overloaded + operator with tensor input
tensor tensor::operator+(const tensor& other) const {
    checkShapes(other);
    tensor result = copy();
    for (int i = 0; i < shape.getSize(); i++) {
        result.data[i] += other.data[i];
    }
    return result;
}

// Overloaded - operator with tensor input
tensor tensor::operator-(const tensor& other) const {
    checkShapes(other);
    tensor result = copy();
    for (int i = 0; i < shape.getSize(); i++) {
        result.data[i] -= other.data[i];
    }
    return result;
}

// Overloaded * operator with tensor input
tensor tensor::operator*(const tensor& other) const {
    checkShapes(other);
    tensor result = copy();
    for (int i = 0; i < shape.getSize(); i++) {
        result.data[i] *= other.data[i];
    }
    return result;
}

// Overloaded / operator with tensor input
tensor tensor::operator/(const tensor& other) const {
    checkShapes(other);
    tensor result = copy();
    for (int i = 0; i < shape.getSize(); i++) {
        result.data[i] /= other.data[i];
    }
    return result;
}

// Overloaded + operator with double input
tensor tensor::operator+(double other) const {
    tensor result = copy();
    for (int i = 0; i < shape.getSize(); i++) {
        result.data[i] /= other;
    }
    return result;
}

// Overloaded - operator with double input
tensor tensor::operator-(double other) const {
    tensor result = copy();
    for (int i = 0; i < shape.getSize(); i++) {
        result.data[i] -= other;
    }
    return result;
}

// Overloaded * operator with double input
tensor tensor::operator*(double other) const {
    tensor result = copy();
    for (int i = 0; i < shape.getSize(); i++) {
        result.data[i] *= other;
    }
    return result;
}

// Overloaded / operator with double input
tensor tensor::operator/(double other) const {
    tensor result = copy();
    for (int i = 0; i < shape.getSize(); i++) {
        result.data[i] /= other;
    }
    return result;
}

// Overloaded += operator with tensor input
tensor& tensor::operator+=(const tensor& other) {
    checkShapes(other);
    for (int i = 0; i < shape.getSize(); i++) {
        data[i] += other.data[i];
    }
    return *this;
}

// Overloaded -= operator with tensor input
tensor& tensor::operator-=(const tensor& other) {
    checkShapes(other);
    for (int i = 0; i < shape.getSize(); i++) {
        data[i] -= other.data[i];
    }
    return *this;
}

// Overloaded *= operator with tensor input
tensor& tensor::operator*=(const tensor& other) {
    checkShapes(other);
    for (int i = 0; i < shape.getSize(); i++) {
        data[i] *= other.data[i];
    }
    return *this;
}

// Overloaded /= operator with tensor input
tensor& tensor::operator/=(const tensor& other) {
    checkShapes(other);
    for (int i = 0; i < shape.getSize(); i++) {
        if (other.data[i] == 0) {
            throw invalid_argument("Error: Division by zero in tensor division.");
        }
        data[i] /= other.data[i];
    }
    return *this;
}

void tensor::squeeze(optional<int> dim) {
    shape.squeeze(dim);
}

void tensor::unsqueeze(int dim) {
    shape.unsqueeze(dim);
}
