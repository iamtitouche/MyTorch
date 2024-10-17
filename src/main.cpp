#include <iostream>
#include "../headers/tensor.h"
#include "../headers/tensorshape.h"
#include "../headers/utils.h"

using namespace std;

int main() {
    tensorShape shape = tensorShape({6, 5, 6});

    tensorShape *shapePtr = &shape;

    //cout << "Addresse de shape : " << reinterpret_cast<int>(shapePtr) << endl;
    cout << shape.toString() << endl;
    cout << shape.getSize() << endl;

    tensor t(shape, 1.2);
    t.initNormal(19, 0.8);
    tensor t2(shape, 3.567);

    tensor *tPtr = &t;
    //cout << "Addresse de t : " << reinterpret_cast<int>(tPtr) << endl;
//
    //tensorShape s = t.getShape();
    cout << t.toString() << endl;

    //cout << t2.toString() << endl;

    //const tensor t_c = t.concat(t2, 0);

    //cout << t_c.toString() << endl;

    followNormal(10, 0.8, t.getData());


    return 0;
}
