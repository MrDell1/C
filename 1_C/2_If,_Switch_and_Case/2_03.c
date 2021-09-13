#include<stdio.h>


int main() {

    int day;
    int month;
    int year;


    printf("Podaj date (w formacie dd-mm-yyyy):  ");
    if (scanf("\t %d-%d-%d", &day, &month, &year) != 3) {
        printf("Incorrect input");
        return 1;
    } else {
        if (day > 0 && day <= 31 && month >= 1 && month <= 12 && year < 2020) {
            if (year % 4 == 0) {
                if (month == 02 && day > 29) {
                    printf("Incorrect");
                } else if (month == 01 && day > 31 || month == 03 && day > 31 || month == 05 && day > 31 || month == 07 && day > 31 ||
                           month == 8 && day > 31 || month == 10 && day > 31 || month == 12 && day > 31) {
                    printf("Incorrect");
                } else if (month == 04 && day > 30 || month == 06 && day > 30 || month == 9 && day > 30 || month == 11 && day > 30) {
                    printf("Incorrect");
                } else {
                    printf("Correct");
                    return 0;
                }
            } else if (month == 02 && day > 28) {
                printf("Incorrect");
            } else if (month == 01 && day > 31 || month == 03 && day > 31 || month == 05 && day > 31 || month == 07 && day > 31 ||
                       month == 8 && day > 31 || month == 10 && day > 31 || month == 12 && day > 31) {
                printf("Incorrect");
            } else if (month == 04 && day > 30 || month == 06 && day > 30 || month == 9 && day > 30 || month == 11 && day > 30) {
                printf("Incorrect");
            } else {
                printf("Correct");
                return 0;
            }
        } else {
            printf("Incorrect");

        }


    }

}