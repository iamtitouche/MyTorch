#include <cmath>
#include <gtest/gtest.h>
#include "utils.h"

class UtilsTest : public ::testing::Test {
protected:
    void SetUp() override {
        // This function is called before each test
    }

    void TearDown() override {
        // This function is called after each test
    }
};
//
//TEST_F(UtilsTest, NormalDistribution) {
//    size_t size = 500;
//    double mean = 0;
//    double stddev = 1;
//    vector<double> random_vector = normal(size, mean, stddev);
//
//    EXPECT_EQ(random_vector.size(), size);
//
//    // chi-2 test
//    int n_classes = (int) log2((double) size) + 1;
//
//    double interval_size = (max(random_vector) - min(random_vector)) / n_classes;
//    vector<double> classes_edges(n_classes + 1);
//
//    classes_edges[0] = min(random_vector);
//    classes_edges[n_classes] = max(random_vector);
//
//    for (int i = 1; i < n_classes; i++) {
//        classes_edges[i] = classes_edges[i - 1] + interval_size;
//    }
//
//    vector<double> expected_frequencies(n_classes);
//
//    for (int i = 0; i < n_classes; i++) {
//        expected_frequencies[i] = (1 + std::erf((classes_edges[i + 1] - mean) / (stddev * std::sqrt(2))));
//    }
//
//    expected_frequencies[0] = 0.5 * (expected_frequencies[0] - (1 + std::erf((classes_edges[0] - mean) / (stddev * std::sqrt(2)))));
//
//    for (int i = 1; i < n_classes; i++) {
//        expected_frequencies[i] = 0.5 * (expected_frequencies[i] - expected_frequencies[i - 1]);
//    }
//}
