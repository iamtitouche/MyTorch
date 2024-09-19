#include <gtest/gtest.h>
#include "tensor.h"


// Test fixture class
class TensorTest : public ::testing::Test {
protected:
    void SetUp() override {
        // This function is called before each test
        std::cout << "Setting up tests" << std::endl;
    }

    void TearDown() override {
        // This function is called after each test
    }

    // Example tensor shapes for testing
    tensorShape shape1 = tensorShape({2, 3});
    tensorShape shape2 = tensorShape({3, 2});
};

// Test constructor with shape
TEST_F(TensorTest, ConstructorWithShape) {
    std::cout << "Running ConstructorWithShape test" << std::endl;
    tensor t(shape1);
    EXPECT_EQ(t.sameShape(tensor(shape1)), true);
    EXPECT_EQ(t.sameSize(tensor(shape1)), true);
    EXPECT_EQ(t.getShape(), shape1);
}

// Test constructor with shape and initial value
TEST_F(TensorTest, ConstructorWithShapeAndValue) {
    std::cout << "Running ConstructorWithShapeAndValue test" << std::endl;
    double initValue = 5.0;
    tensor t(shape1, initValue);
    EXPECT_EQ(t.sameShape(tensor(shape1)), true);
    EXPECT_EQ(t.sameSize(tensor(shape1)), true);
}
