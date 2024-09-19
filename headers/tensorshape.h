#ifndef TENSORSHAPE_H
#define TENSORSHAPE_H

#include <cstdint>
#include <string>
#include <vector>
#include <optional>

using namespace std;

class tensorShape {
public:
    tensorShape(vector<uint32_t> shape);
    uint32_t getSize() const;
    string toString() const;
    vector<uint32_t>& getShape();
    bool sameShape(const tensorShape& other) const;
    bool sameSize(const tensorShape& other) const;

    // Overloaded equality operator
    bool operator==(const tensorShape& other) const;

    // Overloaded inequality operator
    bool operator!=(const tensorShape& other) const;

    void squeeze(optional<int> dim = nullopt);
    void unsqueeze(int dim);


private:
    vector<uint32_t> shape;
};

#endif //TENSORSHAPE_H
