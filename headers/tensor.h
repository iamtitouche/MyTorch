#ifndef TENSOR_H
#define TENSOR_H

#include <vector>
#include <optional>
#include "tensorshape.h"

using namespace std;

class tensor {
public:
    tensor(tensorShape shape);
    tensor(tensorShape shape, double value);
    tensor copy() const;

    tensorShape getShape() const;

    bool sameShape(const tensor &other) const;
    bool sameSize(const tensor &other) const;
    void checkShapes(const tensor &other) const;

    // Overloaded operators with tensor input
    tensor operator+(const tensor& other) const;
    tensor operator-(const tensor& other) const;
    tensor operator*(const tensor& other) const;
    tensor operator/(const tensor& other) const;

    // Overloaded operators with double input
    tensor operator+(double other) const;
    tensor operator-(double other) const;
    tensor operator*(double other) const;
    tensor operator/(double other) const;

    // Overloaded compound assignment operators
    tensor& operator+=(const tensor& other);
    tensor& operator-=(const tensor& other);
    tensor& operator*=(const tensor& other);
    tensor& operator/=(const tensor& other);

    void squeeze(optional<int> dim = nullopt);
    void unsqueeze(int dim);

private:
    tensorShape shape;
    vector<double> data;
};

#endif // TENSOR_H