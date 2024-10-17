#include <gtest/gtest.h>
#include "tensorshape.h"


// Test fixture class
class TensorShapeTest : public ::testing::Test {
protected:
    void SetUp() override {
        // This function is called before each test
    }

    void TearDown() override {
        // This function is called after each test
    }

};

// Test constructor with valid shape
TEST_F(TensorShapeTest, Constructor) {
    const vector<size_t> v1 = {1, 2, 3};
    const tensorShape t1(v1);
    EXPECT_EQ(t1.getShape().size(), v1.size());
    EXPECT_EQ(t1.getShape(), v1);
    EXPECT_NE(&(t1.getShape()[0]), &(v1[0]));

    const tensorShape t2 = tensorShape({2, 5, 34, 2});
    EXPECT_EQ(t2.getShape().size(), 4);
    EXPECT_EQ(t2.getShape(), (vector<size_t>{2, 5, 34, 2}));

    const auto* t3_ptr = new tensorShape({1, 2, 3});
    const tensorShape t3 = *t3_ptr;
    EXPECT_NE(nullptr, t3_ptr);
    EXPECT_EQ(t3.getShape().size(), 3);
    EXPECT_EQ(t3.getShape(), (vector<size_t>{1, 2, 3}));
}

// Test copy constructor
TEST_F(TensorShapeTest, CopyConstructor) {
    tensorShape t1({13, 23, 3, 45});
    const tensorShape t2 = tensorShape(t1);
    EXPECT_EQ(t1.getShape().size(), t2.getShape().size());
    EXPECT_EQ(t1.getShape(), t2.getShape());
    EXPECT_NE(&(t1), &(t2));
}

// Test constructor throws exception for zero dimension
TEST_F(TensorShapeTest, ConstructorInvalidArgumentZeroValue) {
    EXPECT_THROW(tensorShape t({1, 2, 0});, invalid_argument);
}

// Test constructor throws exception for empty shape
TEST_F(TensorShapeTest, ConstructorInvalidArgumentEmptyVector) {
    EXPECT_THROW(tensorShape t({});, invalid_argument);
}

// Test getSize function for correctness
TEST_F(TensorShapeTest, getSize) {
    const tensorShape t1({1, 2, 3, 678});
    EXPECT_EQ(t1.getSize(), 4068);
}

// Test equality operator
TEST_F(TensorShapeTest, Equal) {
    const tensorShape t1({1, 2, 3, 678});
    const tensorShape t2({1, 2, 3, 678});
    EXPECT_TRUE(t1 == t2);
    EXPECT_TRUE(t1 == t1);

    const tensorShape t3({1, 2, 4, 678});
    EXPECT_FALSE(t1 == t3);
}

// Test inequality operator
TEST_F(TensorShapeTest, NotEqual) {
    const tensorShape t1({1, 2, 3, 678});
    const tensorShape t2({1, 2, 3, 678});
    EXPECT_FALSE(t1 != t2);
    EXPECT_FALSE(t1 != t1);

    const tensorShape t3({1, 2, 4, 678});
    EXPECT_TRUE(t1 != t3);
}

// Test squeeze function without arguments
TEST_F(TensorShapeTest, SqueezeWithoutArgument) {
    tensorShape t1({1, 2, 3, 1, 7});
    t1.squeeze();
    EXPECT_EQ(t1.getShape(), (vector<size_t>{2, 3, 7}));

    tensorShape t2({3, 2, 3, 34, 7});
    t2.squeeze();
    EXPECT_EQ(t2.getShape(), (vector<size_t>{3, 2, 3, 34, 7}));

    tensorShape t3({44, 2, 3, 3, 1});
    t3.squeeze();
    EXPECT_EQ(t3.getShape(), (vector<size_t>{44, 2, 3, 3}));
}

// Test squeeze function with a specific dimension
TEST_F(TensorShapeTest, SqueezeWithArgument) {
    tensorShape t1({1, 2, 3, 1, 7});
    t1.squeeze(3);
    EXPECT_EQ(t1.getShape(), (vector<size_t>{1, 2, 3, 7}));

    tensorShape t2({1, 2, 3, 34, 7});
    t2.squeeze(0);
    EXPECT_EQ(t2.getShape(), (vector<size_t>{2, 3, 34, 7}));

    tensorShape t3({44, 2, 3, 3, 1});
    t3.squeeze(4);
    EXPECT_EQ(t3.getShape(), (vector<size_t>{44, 2, 3, 3}));
}

TEST_F(TensorShapeTest, SqueezeOneDimensionalShape) {
    tensorShape t1({3});
    t1.squeeze();
    EXPECT_EQ(t1.getShape(), (vector<size_t>{3}));

    tensorShape t2({1});
    t2.squeeze();
    EXPECT_EQ(t2.getShape(), (vector<size_t>{1}));

    t2.squeeze(0);
    EXPECT_EQ(t2.getShape(), (vector<size_t>{1}));
}

// Test squeeze function when the targeted dimension is not 1
TEST_F(TensorShapeTest, SqueezeNonOneDimension) {
    tensorShape t1({1, 2, 3, 1, 7});
    EXPECT_THROW(t1.squeeze(2);, invalid_argument);

    tensorShape t2({3});
    EXPECT_THROW(t2.squeeze(0);, invalid_argument);
}


// Test squeeze function with a non-existent dimension
TEST_F(TensorShapeTest, SqueezeNonExistentDimension) {
    tensorShape t({1, 2, 3, 1, 7});
    EXPECT_THROW(t.squeeze(5), out_of_range);
}

TEST_F(TensorShapeTest, Unsqueeze) {
    tensorShape t1({1, 2, 3, 1, 7});
    t1.unsqueeze(5);
    EXPECT_EQ(t1.getShape(), (vector<size_t>{1, 2, 3, 1, 7, 1}));
}

TEST_F(TensorShapeTest, ConcatenationCompatibility) {
    const tensorShape t1({1, 2, 3, 1, 7});
    const tensorShape t2({1, 2, 7, 1, 7});

    EXPECT_TRUE(t1.isConcatCompatible(t2, 2));
    EXPECT_FALSE(t1.isConcatCompatible(t2, 3));

    const tensorShape t3({5, 2, 3, 1, 7});

    EXPECT_TRUE(t1.isConcatCompatible(t3, 0));
    EXPECT_FALSE(t1.isConcatCompatible(t3, 2));

    const tensorShape t4({1, 2, 3, 1});

    EXPECT_FALSE(t1.isConcatCompatible(t4, 1));
}

TEST_F(TensorShapeTest, SameSize) {
    const tensorShape t1({1, 2, 3, 1, 7});
    const tensorShape t2({3, 2, 7, 1});
    const tensorShape t3({1, 1, 3, 1, 1, 14, 1});
    EXPECT_TRUE(t1.sameSize(t2));
    EXPECT_TRUE(t2.sameSize(t1));
    EXPECT_TRUE(t1.sameSize(t3));
    EXPECT_TRUE(t3.sameSize(t1));
    EXPECT_TRUE(t2.sameSize(t3));
    EXPECT_TRUE(t3.sameSize(t2));
}

TEST_F(TensorShapeTest, StringRendering) {
    const tensorShape t1({32});
    EXPECT_EQ(t1.toString(), "tensorShape [32]");

    const tensorShape t2({1, 2, 3, 1, 7});
    EXPECT_EQ(t2.toString(), "tensorShape [1, 2, 3, 1, 7]");

    const tensorShape t3({134, 226783, 3, 14, 89, 23});
    EXPECT_EQ(t3.toString(), "tensorShape [134, 226783, 3, 14, 89, 23]");
}


