#include<stdio.h>


int main() {
    double table[16] = {818.2322865, 0.2559284267, 0.8075320057, 0.420383407, 0.2302881821, 0.8099938753,
                        0.7093625361, -5.174125467, 0.640470207, 0.34488766, 0.3592073480, 0.667142349,
                        -8.698238416, 97.23240366, 0.0220584254, 0.8590693462}, j;

    for (int i = 0; i < 16; i++) {
        j = table[i];
        if (j < 1 && j > 0) {
            printf("  %.3f\n", table[i]);
        } else if (j < 0) {
            printf(" %.3f\n", table[i]);
        } else if (j >= 10 && j < 100) {
            printf(" %.3f\n", table[i]);
        } else {
            printf("%.3f\n", table[i]);
        }
    }

}