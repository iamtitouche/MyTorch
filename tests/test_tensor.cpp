#include <gtest/gtest.h>
#include "tensor.h"


// Test fixture class
class TensorTest : public ::testing::Test {
protected:
    void SetUp() override {
        // This function is called before each test
    }

    void TearDown() override {
        // This function is called after each test
    }

    // Example tensor shapes for testing
    tensorShape shape = tensorShape({2, 3});
    tensorShape shape2 = tensorShape({3, 2});
};

// Test constructor with shape
//TEST_F(TensorTest, ConstructorWithShape) {
//    tensor t(shape);
//    EXPECT_EQ(t.sameShape(tensor(shape)), true);
//    EXPECT_EQ(t.sameSize(tensor(shape)), true);
//    EXPECT_EQ(t.getShape(), shape);
//}
//
//// Test constructor with shape and initial value
//TEST_F(TensorTest, ConstructorWithShapeAndValue) {
//    double initValue = 5.0;
//    tensor t(shape, initValue);
//    EXPECT_EQ(t.sameShape(tensor(shape)), true);
//    EXPECT_EQ(t.sameSize(tensor(shape)), true);
//}
//
//
//TEST_F(TensorTest, Copy) {
//    tensor t1(shape, 2.3);
//
//    tensor t2 = t1.copy();
//
//    EXPECT_EQ(t1.getShape(), t2.getShape());
//    EXPECT_EQ(t1.getData(), t2.getData());
//
//    EXPECT_NE(&t1, &t2);
//    EXPECT_NE(t1.getData().data(), t2.getData().data());
//}
//