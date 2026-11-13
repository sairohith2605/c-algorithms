#include <math.h>
#include <stdio.h>

double find_max(double in_vector[], size_t vector_len);
void softmax(double in_vector[], double out_vector[], size_t vector_len);

int main(void) {
    double vec[3] = {2.0, 1.0, 0.1};
    double out_vector[3];
    softmax(vec, out_vector, 3);
    printf("[ ");
    for (int i=0; i<3; i++) {
        printf("%lf ", out_vector[i]);
    }
    printf(" ]\n");
    return 0;
}

void softmax(double in_vector[], double out_vector[], size_t vector_len) {
    double max_val = find_max(in_vector, vector_len);
    double sum = 0.0;
    for (int i=0; i < vector_len; i++) {
        out_vector[i] = exp(in_vector[i] - max_val);
        sum += out_vector[i];
    }
    for (int i=0; i < vector_len; i++) {
        out_vector[i] = out_vector[i] / sum;
    }
}

double find_max(double in_vector[], size_t vector_len) {
    double max_val = 0.0;
    if (vector_len != 0) {
        for (int i=0; i<vector_len; i++) {
            if (max_val < in_vector[i]) {
                max_val = in_vector[i];
            }
        }
    }
    return max_val;
}

