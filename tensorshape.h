#ifndef TENSORSHAPE_H
#define TENSORSHAPE_H

#include <cstdint>
#include <string>
#include <vector>

using namespace std;

class tensorShape {
public:
    tensorShape(vector<uint32_t> shape);
    uint32_t getSize() const;
    string toString() const;
    vector<uint32_t>& getShape();
    bool sameShape(const tensorShape& other) const;
    bool sameSize(const tensorShape& other) const;
private:
    vector<uint32_t> shape;
};

#endif //TENSORSHAPE_H
