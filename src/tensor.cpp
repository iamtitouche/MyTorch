#include "tensor.h"

#include <iostream>
#include <ostream>
#include <sstream>

using namespace std;

tensor::tensor(tensorShape shape) : shape(move(shape)), data(shape.getSize(), 0.0) {}

//tensor::tensor(tensorShape shape, double value): shape() {
//    this->shape = shape.copy();
//    this->data = vector<double>(shape.getSize(), value);
//}


tensorShape tensor::getShape() const {
    return shape;
}

vector<double> tensor::getData() const {
    return data;
}

bool tensor::sameShape(const tensor &other) const {
    return shape == other.shape;
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

tensor tensor::squeeze(optional<int> dim) const {
    tensor new_tensor = this->copy();
    new_tensor.shape.squeeze(dim);
    return new_tensor;
}

tensor tensor::unsqueeze(int dim) const {
    tensor new_tensor = this->copy();
    new_tensor.shape.unsqueeze(dim);
    return new_tensor;
}

tensor tensor::concat(const tensor &other, int dim) const {
    if (!shape.isConcatCompatible(other.shape, dim)) {
        throw invalid_argument("Error: Concatenation of tensors do not match.");
    }

    vector<size_t> new_shape_vector = shape.getShape();
    new_shape_vector[dim] += other.shape.getShape()[dim];

    tensorShape new_shape(new_shape_vector);

    vector<double> new_data;

    uint32_t p1 = 1;
    for (int i = 0; i < dim; i++) {
        p1 *= new_shape_vector[i];
    }

    uint32_t p2 = 1;
    for (int i = dim; i < shape.getShape().size(); i++) {
        p1 *= shape.getShape()[i];
    }

    uint32_t p3 = 1;
    for (int i = dim; i < other.getShape().getShape().size(); i++) {
        p1 *= other.getShape().getShape()[i];
    }

    for (uint32_t i = 0; i < p1; i++) {
        for (uint32_t j = 0; j < p2; j++) {
            new_data.push_back(data[i * p1 + j]);
        }
        for (uint32_t j = 0; j < p3; j++) {
            new_data.push_back(other.data[i * p1 + j]);
        }
    }

    tensor new_tensor(new_shape);

    new_tensor.data = new_data;

    return new_tensor;
}

string tensor::toString() const {
    stringstream ss;
    ss << "Tensor : " << shape.toString() << "\n";
    cout << "Size " << data.size() << endl;
    for (size_t i = 0; i < data.size(); i++) {
        ss << data[i];
        if (i != data.size() - 1) {
            ss << ", ";
        }
        if ((i + 1) % shape.getShape().back() == 0 && i != data.size() - 1) {
            ss << "\n ";
        }
    }
    ss << "]";
    return ss.str();
}

