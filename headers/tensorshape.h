#ifndef TENSORSHAPE_H
#define TENSORSHAPE_H

#include <cstdint>
#include <string>
#include <vector>
#include <optional>

using namespace std;

class tensorShape {
public:
    explicit tensorShape(const vector<size_t>& shape_vector);

    // toString method
    [[nodiscard]] string toString() const;

    // shape and size getter
    [[nodiscard]] vector<size_t> getShape() const;
    [[nodiscard]] size_t getSize() const;

    // Overloaded equality operator
    bool operator==(const tensorShape& other) const;

    // Overloaded inequality operator
    bool operator!=(const tensorShape& other) const;

    void squeeze(optional<int> dim = nullopt);
    void unsqueeze(int dim);

    // TensorShape Comparator
    [[nodiscard]] bool sameSize(const tensorShape& other) const;
    [[nodiscard]] bool isConcatCompatible(const tensorShape& other, int dim) const;


private:
    vector<size_t> shape;
};

#endif //TENSORSHAPE_H
