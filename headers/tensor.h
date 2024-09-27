#ifndef TENSOR_H
#define TENSOR_H

#include <vector>
#include <optional>
#include "tensorshape.h"

using namespace std;

class tensor {
public:
    explicit tensor(tensorShape shape);
    tensor(tensorShape shape, double value);
    [[nodiscard]] tensor copy() const;

    [[nodiscard]] tensorShape getShape() const;
    [[nodiscard]] vector<double> getData() const;

    bool sameShape(const tensor &other) const;
    bool sameSize(const tensor &other) const;
    void checkShapes(const tensor &other) const;

    [[nodiscard]] string toString() const;

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

    [[nodiscard]] tensor squeeze(optional<int> dim = nullopt) const;
    [[nodiscard]] tensor unsqueeze(int dim) const;

    [[nodiscard]] tensor concat(const tensor& other, int dim) const;

private:
    tensorShape shape;
    vector<double> data;
};

#endif // TENSOR_H