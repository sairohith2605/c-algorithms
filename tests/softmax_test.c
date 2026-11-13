#include "unity.h"

void softmax(double in_vector[], double out_vector[], size_t vector_len);

void setUp(void) {}
void tearDown(void) {}

static void check_output(double input[], const double expected[], size_t len) {
    double output[3];
    double sum = 0.0;
    softmax(input, output, len);
    for (size_t i = 0; i < len; i++) {
        TEST_ASSERT_DOUBLE_WITHIN(1e-6, expected[i], output[i]);
        sum += output[i];
    }
    TEST_ASSERT_DOUBLE_WITHIN(1e-6, 1.0, sum);
}

void test_example(void) {
    double input[] = {2.0, 1.0, 0.1};
    const double expected[] = {0.659001, 0.242433, 0.098566};
    check_output(input, expected, 3);
}

void test_equal_inputs(void) {
    double input[] = {3.0, 3.0, 3.0};
    const double expected[] = {1.0 / 3, 1.0 / 3, 1.0 / 3};
    check_output(input, expected, 3);
}

void test_single_input(void) {
    double input[] = {-5.0};
    const double expected[] = {1.0};
    check_output(input, expected, 1);
}

void test_large_positive_inputs(void) {
    double input[] = {1002.0, 1001.0, 1000.1};
    const double expected[] = {0.659001, 0.242433, 0.098566};
    check_output(input, expected, 3);
}

void test_large_negative_inputs(void) {
    double input[] = {-998.0, -999.0, -999.9};
    const double expected[] = {0.659001, 0.242433, 0.098566};
    check_output(input, expected, 3);
}

void test_empty_input(void) {
    double output = 42.0;
    softmax(NULL, &output, 0);
    TEST_ASSERT_DOUBLE_WITHIN(1e-6, 42.0, output);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_example);
    RUN_TEST(test_equal_inputs);
    RUN_TEST(test_single_input);
    RUN_TEST(test_large_positive_inputs);
    RUN_TEST(test_large_negative_inputs);
    RUN_TEST(test_empty_input);
    return UNITY_END();
}
