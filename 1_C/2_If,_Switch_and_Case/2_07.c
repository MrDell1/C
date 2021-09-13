#include<stdio.h>


int main() {

    float a;
    double f_price = 0.5, s_price = 0.75, t_price = 1.2, fou_price = 1.5;
    float c;
    double price;
    printf("Podaj ilosc zuzytej energii:  ");
    if (scanf("\t%f", &a) != 1) {
        printf("Incorrect input ");
        return 1;
    } else {
        if (a >= 250) {
            c = a - 250;
            price = c * fou_price + 220;
            price = price * 1.22;
            printf("%.2lf", price);
        } else if (a < 250 && a > 150) {
            c = a - 150;
            price = c * t_price + 100;
            price = price * 1.22;
            printf("%.2lf", price);
        } else if (a <= 150 && a > 50) {
            c = a - 50;
            price = c * s_price + 25;
            price = price * 1.22;
            printf("%.2lf", price);
        } else if (a <= 50 && a > 0) {
            price = a * f_price;
            price = price * 1.22;
            printf("%.2lf", price);
        } else {
            printf("Incorrect input ");
            return 1;
        }
    }


}