#include <stdio.h>
#include <stdarg.h>

int stats(int *sum, float *avg, int num, ...);

int main() {
    printf("Enter number of elements: ");
    int n;
    if (scanf("%d", &n) != 1) {
        printf("Incorrect input");
        return 1;
    }
    if (n > 3 || n <= 0) {
        printf("Incorrect input data");
        return 2;
    }

    printf("Podaj liczby: ");
    if (n == 1) {
        int x = 0;
        if (scanf("%d", &x) != 1) {
            printf("Incorrect input");
            return 1;
        }
        int sum = 0;
        float avg = 0;
        stats(&sum, &avg, n, x);
        printf("%d %f", sum, avg);
        return 0;
    } else if (n == 2) {
        int x = 0, y = 0;
        if (scanf("%d %d", &x, &y) != 2) {
            printf("Incorrect input");
            return 1;
        }
        int sum = 0;
        float avg = 0;
        stats(&sum, &avg, n, x, y);
        printf("%d %f", sum, avg);
        return 0;
    } else if (n == 3) {
        int x = 0, y = 0, z = 0;
        if (scanf("%d %d %d", &x, &y, &z) != 3) {
            printf("Incorrect input");
            return 1;
        }
        int sum = 0;
        float avg = 0;
        stats(&sum, &avg, n, x, y, z);
        printf("%d %f", sum, avg);
        return 0;
    }

}

int stats(int *sum, float *avg, int num, ...) {
    if (sum == NULL || avg == NULL || num <= 0) {
        return 1;
    }
    *sum = 0;
    *avg = 0;
    va_list vaList;
            va_start(vaList, num);
    for (int i = 0; i < num; i++) {
        *sum += va_arg(vaList, int);
    }

    *avg = ((float)*sum / (float)num);
            va_end(vaList);
    return 0;
}