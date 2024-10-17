//
// Created by dev on 01/10/2024.
//

#include "utils.h"
#include <stdexcept>
#include <random>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <ostream>

using namespace std;


double sum_of_squares(const double x, const double y) {
    return x * x + y * y;
}


vector<double> normal(const size_t size, const double mean, const double stddev) {
    // Normal variable generator, using Marsaglia polar method
    if (stddev <= 0) {
        throw invalid_argument("Error : stddev must be positive");
    }

    vector<double> result(size);

    random_device rd;
    mt19937 gen(rd());

    uniform_real_distribution<> dis(-1.0, 1.0);

    for (size_t i = 0; i < size; i += 2) {
        double uniform_1 = dis(gen);
        double uniform_2 = dis(gen);
        double s = sum_of_squares(uniform_1, uniform_2);

        while (s > 1) {
            uniform_1 = dis(gen);
            uniform_2 = dis(gen);
            s = sum_of_squares(uniform_1, uniform_2);
        }

        const double factor = sqrt( - 2 * log(s) / s);

        const double normal_1 = uniform_1 * factor;
        const double normal_2 = uniform_2 * factor;

        result[i] = mean + stddev * normal_1;
        if (i + 1 < size) {
            result[i + 1] = mean + stddev * normal_2;
        }
    }

    return result;
}


void followNormal(const double mean, const double stddev, vector<double> input) {
    auto min = ranges::min_element(input);
    auto max = ranges::max_element(input);

    const int n_classes = static_cast<int>(log2(static_cast<double>(input.size()))) + 1;

    const double interval_size = (*max - *min) / n_classes;
    vector<double> classes_edges(n_classes + 1);

    classes_edges[0] = *min;
    for (int i = 1; i < n_classes; i++) {
        classes_edges[i] = classes_edges[i - 1] + interval_size;
    }
    classes_edges[n_classes] = *max;

    vector<double> expected_frequencies(n_classes);

    for (int i = 0; i < n_classes; i++) {
        expected_frequencies[i] = (1 + erf((classes_edges[i + 1] - mean) / (stddev * sqrt(2))));
    }

    expected_frequencies[0] = 0.5 * (expected_frequencies[0] - (1 + erf((classes_edges[0] - mean) / (stddev * std::sqrt(2)))));

    for (int i = 1; i < n_classes; i++) {
        expected_frequencies[i] = 0.5 * (expected_frequencies[i] - expected_frequencies[i - 1]);
    }

    vector<int> samples(n_classes, 0);

    for (double num : input) {
        int i = 0;
        while (num < classes_edges[i + 1]) {
            i++;
        }
        samples[i]++;
    }

    double p_value = 0;

    for (int i = 0; i < n_classes; i++) {
        if (expected_frequencies[i] > 0) {
            p_value += pow((expected_frequencies[i] - static_cast<double>(samples[i]) / static_cast<double>(input.size())), 2) /
                expected_frequencies[i];
        }
    }

    p_value /= n_classes;

    cout << p_value << endl;
}
