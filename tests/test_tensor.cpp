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
};

// Test constructor with shape
TEST_F(TensorTest, ConstructorWithShape) {
    const tensorShape shape = tensorShape({2, 3});
    const tensor t(shape);

    EXPECT_EQ(t.getShape(), shape);
    EXPECT_NE(&(t.getShape()), &shape);
    EXPECT_EQ(t.getSize(), shape.getSize());

}

TEST_F(TensorTest, NormalInitialisation) {
    const tensorShape shape = tensorShape({100, 100});
    tensor t(shape);

    t.initNormal(10.0, 1.0);

    EXPECT_EQ(t.getShape(), shape);
    EXPECT_EQ(t.getSize(), shape.getSize());




}


TEST_F(TensorTest, Copy) {
    const tensorShape shape = tensorShape({2, 3});
    tensor t1(shape, 2.3);
    tensor t2 = t1.copy();

    EXPECT_EQ(t1.getShape(), t2.getShape());
    EXPECT_NE(&t1, &t2);
    EXPECT_EQ(t1.getData(), t2.getData());
}


TEST_F(TensorTest, ShapeGetter) {
    const tensorShape shape = tensorShape({2, 3});
    const tensor t(shape, 2.3);

    const tensorShape& shape_from_tensor = t.getShape();

    EXPECT_EQ(shape_from_tensor, shape);
    EXPECT_NE(&shape_from_tensor, &shape);
    EXPECT_EQ(&shape_from_tensor, &t.getShape());
}

