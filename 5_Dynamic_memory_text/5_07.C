#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int multiply(const char *number1, const char *number2, char **result);

int subtract(const char *number1, const char *number2, char **result);

int add(const char *number1, const char *number2, char **result);

int validate_expression(const char *expr);

int validate(const char *number);

int calculate(const char *expr, char **result);

int compare(const char *number1, const char *number2);

void reverse(char *x, int begin, int end);

int main() {
    char *num, *res;//, *expr;
    num = (char*)malloc(501);
    if (num == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }

    printf("Podaj pierwsza liczbe:");
    scanf("%500[^\n]s", num);
    setbuf(stdin, NULL);

    if (validate_expression(num) != 0) {
        printf("Incorrect input");
        free(num);
        return 1;
    }
    int calc_err = 0;
    calc_err = calculate(num, &res);

    if(calc_err == 3){
        printf("Failed to allocate memory");
        free(num);
        return 8;
    }
    else if(calc_err != 0){
        printf("Incorrect input");
        free(num);
        return 1;
    }
    else {
        printf("%s", res);
        free(res);
        free(num);
    }
    
    return 0;
}

int validate_expression(const char *expr) {
    if (expr == NULL) {
        return 2;
    }

    for (int i = 0; i < (int) strlen(expr); i++) {
        if ((*(expr + i) < 48 || *(expr + i) > 57)) {
            if (*(expr + i) != 42) {
                if (*(expr + i) != 43) {
                    if (*(expr + i) != 45) {
                        return 1;
                    }
                }
            }
        }
    }

    for (int i = 0; i < (int) strlen(expr) - 1; i++) {
        if (*(expr + i) == 45 && (*(expr + i + 1) == 43 || *(expr + i + 1) == 42)) {
            return 1;
        }
        if (*(expr + i) == 43 && (*(expr + i + 1) == 43 || *(expr + i + 1) == 42)) {
            return 1;
        }
        if (*(expr + i) == 42 && (*(expr + i + 1) == 43 || *(expr + i + 1) == 42)) {
            return 1;
        }
    }

    if (strlen(expr) == 1 && *(expr + 0) == 48) {
        return 0;
    }

    if (*(expr + 0) == 48) {
        return 1;
    }

    if (*(expr + strlen(expr) - 1) < 48 || *(expr + strlen(expr) - 1) > 57) {
        return 1;
    }

    if (*(expr + 0) < 48 || *(expr + 0) > 57) {
        if (*(expr + 0) != 45) {
            return 1;
        }
    }

    return 0;
}

int validate(const char *number) {
    if (number == NULL) {
        return -1;
    }
    if (*(number + 0) > 48 && *(number + 0) <= 57) {
        for (int i = 1; i < (int) strlen(number); i++) {

            if (*(number + i) < 48 || *(number + i) > 57) {
                return 2;
            }

        }
    } else if (strlen(number) == 1 && *(number + 0) == '0') {
        return 0;
    } else if (*(number + 0) == '-' && (*(number + 1) > 48 && *(number + 1) <= 57)) {
        return 0;
    } else {
        return 2;
    }


    return 0;
}

int calculate(const char *expr, char **result) {
    if (expr == NULL || result == NULL) {
        return 1;
    }

    if(validate_expression(expr) != 0){
        return 2;
    }

    char *temp_res = (char*)calloc((int) strlen(expr) + 3, 1);
    if (temp_res == NULL) {
        return 3;
    }
    int count = 0;
    if (*(expr + 0) == 45) {
        count++;
    }

    for (int i = 0; i < (int) strlen(expr); i++) {
        if (*(expr + i) >= 48 && *(expr + i) <= 57) {
            count++;
        }
    }

    if (count == (int) strlen(expr)) {
        add(expr, "0", result);
        free(temp_res);
        return 0;
    }

    strcpy(temp_res, expr);
    int count_res = 0;
    char *plus, *minus, *mult;
    Begin:;
    char *num1 = (char*)calloc((int) strlen(expr), 1);
    if (num1 == NULL) {
        free(temp_res);
        return 3;
    }
    char *num2 = (char*)calloc((int) strlen(expr), 1);
    if (num2 == NULL) {
        free(temp_res);
        free(num1);
        return 3;
    }
    count_res = 0;
    plus = NULL;
    minus = NULL;
    mult = NULL;


    if (*(temp_res + 0) == 45) {
        mult = strchr(temp_res + 1, 42);
        plus = strchr(temp_res + 1, 43);
        minus = strchr(temp_res + 1, 45);
    } else {
        mult = strchr(temp_res + 1, 42);
        plus = strchr(temp_res + 1, 43);
        minus = strchr(temp_res + 1, 45);
    }
    if (mult == NULL) {
        if (plus != NULL && minus != NULL) {
            if (strlen(plus) > strlen(minus)) {
                strncpy(num1, temp_res, plus - temp_res);
                count_res += (int) (plus - temp_res);
                for (int i = (int) (plus - temp_res) + 1; i < (int) strlen(temp_res); i++) {
                    if (i == (int) (plus - temp_res) + 1 && *(temp_res + i) == 45) {
                        const char ch = *(temp_res + i);
                        strncat(num2, &ch, 1);
                        count_res++;
                    } else {
                        if (*(temp_res + i) == 42 || *(temp_res + i) == 43 || *(temp_res + i) == 45) {
                            break;
                        } else {
                            const char ch = *(temp_res + i);
                            strncat(num2, &ch, 1);
                            count_res++;
                        }
                    }
                }

                int add_err = 0;
                add_err = add(num1, num2, result);
                if (add_err != 0) {
                    if (add_err == 3) {
                        free(num1);
                        free(num2);
                        free(temp_res);
                        return 3;
                    } else {
                        free(num1);
                        free(num2);
                        free(temp_res);
                        return 2;
                    }
                }

                goto Next;
            }
            else {
                strncpy(num1, temp_res, minus - temp_res);
                count_res += (int) (minus - temp_res);
                for (int i = (int) (minus - temp_res) + 1; i < (int) strlen(temp_res); i++) {
                    if (i == (int) (minus - temp_res) + 1 && *(temp_res + i) == 45) {
                        const char ch = *(temp_res + i);
                        strncat(num2, &ch, 1);
                        count_res++;

                    } else {
                        if (*(temp_res + i) == 42 || *(temp_res + i) == 43 || *(temp_res + i) == 45) {
                            break;
                        } else {
                            const char ch = *(temp_res + i);
                            strncat(num2, &ch, 1);
                            count_res++;
                        }
                    }
                }

                int sub_err = 0;
                sub_err = subtract(num1, num2, result);
                if (sub_err != 0) {
                    if (sub_err == 3) {
                        free(num1);
                        free(num2);
                        free(temp_res);
                        return 3;
                    } else {
                        free(num1);
                        free(num2);
                        free(temp_res);
                        return 2;
                    }
                }

                goto Next;
            }

        }
        else if (plus == NULL) {
            strncpy(num1, temp_res, minus - temp_res);
            count_res += (int) (minus - temp_res);
            for (int i = (int) (minus - temp_res) + 1; i < (int) strlen(temp_res); i++) {
                if (i == (int) (minus - temp_res) + 1 && *(temp_res + i) == 45) {
                    const char ch = *(temp_res + i);
                    strncat(num2, &ch, 1);
                    count_res++;
                } else {
                    if (*(temp_res + i) == 42 || *(temp_res + i) == 43 || *(temp_res + i) == 45) {
                        break;
                    } else {
                        const char ch = *(temp_res + i);
                        strncat(num2, &ch, 1);
                        count_res++;
                    }
                }
            }

            int sub_err = 0;
            sub_err = subtract(num1, num2, result);
            if (sub_err != 0) {
                if (sub_err == 3) {
                    free(num1);
                    free(num2);
                    free(temp_res);
                    return 3;
                } else {
                    free(num1);
                    free(num2);
                    free(temp_res);
                    return 2;
                }
            }

            goto Next;
        }
        else {
            strncpy(num1, temp_res, plus - temp_res);
            count_res += (int) (plus - temp_res);
            for (int i = (int) (plus - temp_res) + 1; i < (int) strlen(temp_res); i++) {
                if (i == (int) (plus - temp_res) + 1 && *(temp_res + i) == 45) {
                    const char ch = *(temp_res + i);
                    strncat(num2, &ch, 1);
                    count_res++;
                } else {
                    if (*(temp_res + i) == 42 || *(temp_res + i) == 43 || *(temp_res + i) == 45) {
                        break;
                    } else {
                        const char ch = *(temp_res + i);
                        strncat(num2, &ch, 1);
                        count_res++;
                    }
                }
            }

            int add_err = 0;
            add_err = add(num1, num2, result);
            if (add_err != 0) {
                if (add_err == 3) {
                    free(num1);
                    free(num2);
                    free(temp_res);
                    return 3;
                } else {
                    free(num1);
                    free(num2);
                    free(temp_res);
                    return 2;
                }
            }

            goto Next;
        }
    }

    if (plus == NULL) {
        if (mult != NULL && minus != NULL) {
            if (strlen(mult) > strlen(minus)) {
                strncpy(num1, temp_res, mult - temp_res);
                count_res += (int) (mult - temp_res);
                for (int i = (int) (mult - temp_res) + 1; i < (int) strlen(temp_res); i++) {
                    if (i == (int) (mult - temp_res) + 1 && *(temp_res + i) == 45) {
                        const char ch = *(temp_res + i);
                        strncat(num2, &ch, 1);
                        count_res++;
                    } else {
                        if (*(temp_res + i) == 42 || *(temp_res + i) == 43 || *(temp_res + i) == 45) {
                            break;
                        } else {
                            const char ch = *(temp_res + i);
                            strncat(num2, &ch, 1);
                            count_res++;

                        }
                    }
                }

                int mul_err = 0;
                mul_err = multiply(num1, num2, result);
                if (mul_err != 0) {
                    if (mul_err == 3) {
                        free(num1);
                        free(num2);
                        free(temp_res);
                        return 3;
                    } else {
                        free(num1);
                        free(num2);
                        free(temp_res);
                        return 2;
                    }
                }

                goto Next;
            }
            else {
                strncpy(num1, temp_res, minus - temp_res);
                count_res += (int) (minus - temp_res);
                for (int i = (int) (minus - temp_res) + 1; i < (int) strlen(temp_res); i++) {
                    if (i == (int) (minus - temp_res) + 1 && *(temp_res + i) == 45) {
                        const char ch = *(temp_res + i);
                        strncat(num2, &ch, 1);
                        count_res++;
                    } else {
                        if (*(temp_res + i) == 42 || *(temp_res + i) == 43 || *(temp_res + i) == 45) {
                            break;
                        } else {
                            const char ch = *(temp_res + i);
                            strncat(num2, &ch, 1);
                            count_res++;

                        }
                    }
                }

                int sub_err = 0;
                sub_err = subtract(num1, num2, result);
                if (sub_err != 0) {
                    if (sub_err == 3) {
                        free(num1);
                        free(num2);
                        free(temp_res);
                        return 3;
                    } else {
                        free(num1);
                        free(num2);
                        free(temp_res);
                        return 2;
                    }
                }

                goto Next;
            }
        }
        else if (mult == NULL) {
            strncpy(num1, temp_res, minus - temp_res);
            count_res += (int) (minus - temp_res);
            for (int i = (int) (minus - temp_res) + 1; i < (int) strlen(temp_res); i++) {
                if (i == (int) (minus - temp_res) + 1 && *(temp_res + i) == 45) {
                    const char ch = *(temp_res + i);
                    strncat(num2, &ch, 1);
                    count_res++;
                } else {
                    if (*(temp_res + i) == 42 || *(temp_res + i) == 43 || *(temp_res + i) == 45) {
                        break;
                    } else {
                        const char ch = *(temp_res + i);
                        strncat(num2, &ch, 1);
                        count_res++;

                    }
                }
            }

            int sub_err = 0;
            sub_err = subtract(num1, num2, result);
            if (sub_err != 0) {
                if (sub_err == 3) {
                    free(num1);
                    free(num2);
                    free(temp_res);
                    return 3;
                } else {
                    free(num1);
                    free(num2);
                    free(temp_res);
                    return 2;
                }
            }

            goto Next;
        }
        else {
            strncpy(num1, temp_res, mult - temp_res);
            count_res += (int) (mult - temp_res);
            for (int i = (int) (mult - temp_res) + 1; i < (int) strlen(temp_res); i++) {
                if (i == (int) (mult - temp_res) + 1 && *(temp_res + i) == 45) {
                    const char ch = *(temp_res + i);
                    strncat(num2, &ch, 1);
                    count_res++;
                } else {
                    if (*(temp_res + i) == 42 || *(temp_res + i) == 43 || *(temp_res + i) == 45) {
                        break;
                    } else {
                        const char ch = *(temp_res + i);
                        strncat(num2, &ch, 1);
                        count_res++;

                    }
                }
            }

            int mul_err = 0;
            mul_err = multiply(num1, num2, result);
            if (mul_err != 0) {
                if (mul_err == 3) {
                    free(num1);
                    free(num2);
                    free(temp_res);
                    return 3;
                } else {
                    free(num1);
                    free(num2);
                    free(temp_res);
                    return 2;
                }
            }

            goto Next;
        }
    }

    if (minus == NULL) {
        if (mult != NULL && plus != NULL) {
            if (strlen(mult) > strlen(plus)) {
                strncpy(num1, temp_res, mult- temp_res);
                count_res += (int) (mult - temp_res);
                for (int i = (int) (mult - temp_res) + 1; i < (int) strlen(temp_res); i++) {
                    if (i == (int) (mult - temp_res) + 1 && *(temp_res + i) == 45) {
                        const char ch = *(temp_res + i);
                        strncat(num2, &ch, 1);
                        count_res++;
                    } else {
                        if (*(temp_res + i) == 42 || *(temp_res + i) == 43 || *(temp_res + i) == 45) {
                            break;
                        } else {
                            const char ch = *(temp_res + i);
                            strncat(num2, &ch, 1);
                            count_res++;

                        }
                    }
                }

                int mul_err = 0;
                mul_err = multiply(num1, num2, result);
                if (mul_err != 0) {
                    if (mul_err == 3) {
                        free(num1);
                        free(num2);
                        free(temp_res);
                        return 3;
                    } else {
                        free(num1);
                        free(num2);
                        free(temp_res);
                        return 2;
                    }
                }

                goto Next;
            }
            else {
                strncpy(num1, temp_res, plus - temp_res);
                count_res += (int) (plus - temp_res);
                for (int i = (int) (plus - temp_res) + 1; i < (int) strlen(temp_res); i++) {
                    if (i == (int) (plus - temp_res) + 1 && *(temp_res + i) == 45) {
                        const char ch = *(temp_res + i);
                        strncat(num2, &ch, 1);
                        count_res++;
                    } else {
                        if (*(temp_res + i) == 42 || *(temp_res + i) == 43 || *(temp_res + i) == 45) {
                            break;
                        } else {
                            const char ch = *(temp_res + i);
                            strncat(num2, &ch, 1);
                            count_res++;

                        }
                    }
                }

                int add_err = 0;
                add_err = add(num1, num2, result);
                if (add_err != 0) {
                    if (add_err == 3) {
                        free(num1);
                        free(num2);
                        free(temp_res);
                        return 3;
                    } else {
                        free(num1);
                        free(num2);
                        free(temp_res);
                        return 2;
                    }
                }

                goto Next;
            }
        }
        else if (mult == NULL) {
            strncpy(num1, temp_res, plus - temp_res);
            count_res += (int) (plus - temp_res);
            for (int i = (int) (plus - temp_res) + 1; i < (int) strlen(temp_res); i++) {
                if (i == (int) (plus - temp_res) + 1 && *(temp_res + i) == 45) {
                    const char ch = *(temp_res + i);
                    strncat(num2, &ch, 1);
                    count_res++;
                } else {
                    if (*(temp_res + i) == 42 || *(temp_res + i) == 43 || *(temp_res + i) == 45) {
                        break;
                    } else {
                        const char ch = *(temp_res + i);
                        strncat(num2, &ch, 1);
                        count_res++;

                    }
                }
            }

            int add_err = 0;
            add_err = add(num1, num2, result);
            if (add_err != 0) {
                if (add_err == 3) {
                    free(num1);
                    free(num2);
                    free(temp_res);
                    return 3;
                } else {
                    free(num1);
                    free(num2);
                    free(temp_res);
                    return 2;
                }
            }

            goto Next;
        }
        else {
            strncpy(num1, temp_res, mult - temp_res);
            count_res += (int) (mult - temp_res);
            for (int i = (int) (mult - temp_res) + 1; i < (int) strlen(temp_res); i++) {
                if (i == (int) (mult - temp_res) + 1 && *(temp_res + i) == 45) {
                    const char ch = *(temp_res + i);
                    strncat(num2, &ch, 1);
                    count_res++;
                } else {
                    if (*(temp_res + i) == 42 || *(temp_res + i) == 43 || *(temp_res + i) == 45) {
                        break;
                    } else {
                        const char ch = *(temp_res + i);
                        strncat(num2, &ch, 1);
                        count_res++;

                    }
                }
            }

            int mul_err = 0;
            mul_err = multiply(num1, num2, result);
            if (mul_err != 0) {
                if (mul_err == 3) {
                    free(num1);
                    free(num2);
                    free(temp_res);
                    return 3;
                } else {
                    free(num1);
                    free(num2);
                    free(temp_res);
                    return 2;
                }
            }

            goto Next;
        }
    }

    if (mult != NULL && plus != NULL && minus != NULL) {
        if (strlen(mult) > strlen(plus) && strlen(mult) > strlen(minus)) {
            strncpy(num1, temp_res, mult - temp_res);
            count_res += (int) (mult - temp_res);
            for (int i = (int) (mult - temp_res) + 1; i < (int) strlen(temp_res); i++) {
                if (i == (int) (mult - temp_res) + 1 && *(temp_res + i) == 45) {
                    const char ch = *(temp_res + i);
                    strncat(num2, &ch, 1);
                    count_res++;
                } else {
                    if (*(temp_res + i) == 42 || *(temp_res + i) == 43 || *(temp_res + i) == 45) {
                        break;
                    } else {
                        const char ch = *(temp_res + i);
                        strncat(num2, &ch, 1);
                        count_res++;

                    }
                }
            }

            int mul_err = 0;
            mul_err = multiply(num1, num2, result);
            if (mul_err != 0) {
                if (mul_err == 3) {
                    free(num1);
                    free(num2);
                    free(temp_res);
                    return 3;
                } else {
                    free(num1);
                    free(num2);
                    free(temp_res);
                    return 2;
                }
            }

            goto Next;
        }
        if (strlen(plus) > strlen(mult) && strlen(plus) > strlen(minus)) {
            strncpy(num1, temp_res, plus - temp_res);
            count_res += (int) (plus - temp_res);
            for (int i = (int) (plus - temp_res) + 1; i < (int) strlen(temp_res); i++) {
                if (i == (int) (plus - temp_res) + 1 && *(temp_res + i) == 45) {
                    const char ch = *(temp_res + i);
                    strncat(num2, &ch, 1);
                    count_res++;
                } else {
                    if (*(temp_res + i) == 42 || *(temp_res + i) == 43 || *(temp_res + i) == 45) {
                        break;
                    } else {
                        const char ch = *(temp_res + i);
                        strncat(num2, &ch, 1);
                        count_res++;

                    }
                }
            }

            int add_err = 0;
            add_err = add(num1, num2, result);
            if (add_err != 0) {
                if (add_err == 3) {
                    free(num1);
                    free(num2);
                    free(temp_res);
                    return 3;
                } else {
                    free(num1);
                    free(num2);
                    free(temp_res);
                    return 2;
                }
            }

            goto Next;
        }
        if (strlen(minus) > strlen(mult) && strlen(minus) > strlen(plus)) {
            strncpy(num1, temp_res, minus - temp_res);
            count_res += (int)(minus - temp_res);
            for (int i = (int) (minus - temp_res) + 1; i < (int) strlen(temp_res); i++) {
                if (i == (int) (minus - temp_res) + 1 && *(temp_res + i) == 45) {
                    const char ch = *(temp_res + i);
                    strncat(num2, &ch, 1);
                    count_res++;
                } else {
                    if (*(temp_res + i) == 42 || *(temp_res + i) == 43 || *(temp_res + i) == 45) {
                        break;
                    } else {
                        const char ch = *(temp_res + i);
                        strncat(num2, &ch, 1);
                        count_res++;

                    }
                }
            }

            int sub_err = 0;
            sub_err = subtract(num1, num2, result);
            if (sub_err != 0) {
                if (sub_err == 3) {
                    free(num1);
                    free(num2);
                    free(temp_res);
                    return 3;
                } else {
                    free(num1);
                    free(num2);
                    free(temp_res);
                    return 2;
                }
            }

            goto Next;
        }
    }

    Next:;
    char *temp = (char*)calloc((int) strlen(*result) + strlen(temp_res), 1);
    strcpy(temp, *result);
    strcat(temp, temp_res + count_res + 1);
    strcpy(temp_res, temp);
    free(temp);
    //printf("%s \n", *result);
    if (*(temp_res + 0) != 45) {
        for (int i = 0; i < (int)strlen(temp_res); i++) {
            if (*(temp_res + i) == 42 || *(temp_res + i) == 43 || *(temp_res + i) == 45) {
                free(*result);
                free(num1);
                free(num2);
                goto Begin;
            }
        }
    } else {
        for (int i = 1; i < (int)strlen(temp_res); i++) {
            if (*(temp_res + i) == 42 || *(temp_res + i) == 43 || *(temp_res + i) == 45) {
                free(*result);
                free(num1);
                free(num2);
                goto Begin;
            }
        }
    }
    strcpy(*result, temp_res);
    free(temp_res);
    free(num1);
    free(num2);
    return 0;
}

int compare(const char *number1, const char *number2) {
    if (number1 == NULL || number2 == NULL) {
        return 2;
    }
    if (validate_expression(number1) != 0) {
        return 3;
    }
    if (validate_expression(number2) != 0) {
        return 3;
    }

    if (*(number1 + 0) == 45 && *(number2 + 0) != 45) {
        return -1;
    } else if (*(number1 + 0) != 45 && *(number2 + 0) == 45) {
        return 1;
    } else if (*(number1 + 0) == 45 && *(number2 + 0) == 45) {
        if (strlen(number1) > strlen(number2)) {
            return -1;
        } else if (strlen(number1) < strlen(number2)) {
            return 1;
        } else {
            for (int i = 0; i < (int) strlen(number1); i++) {

                if (*(number1 + i) > *(number2 + i)) {
                    return -1;
                } else if (*(number1 + i) < *(number2 + i)) {
                    return 1;
                }

            }

        }

    }

    if (strlen(number1) > strlen(number2)) {
        return 1;
    } else if (strlen(number1) < strlen(number2)) {
        return -1;
    } else {
        for (int i = 0; i < (int) strlen(number1); i++) {

            if (*(number1 + i) > *(number2 + i)) {
                return 1;
            } else if (*(number1 + i) < *(number2 + i)) {
                return -1;
            }

        }

    }
    return 0;
}

int add(const char *number1, const char *number2, char **result) {
    if (number1 == NULL || number2 == NULL || result == NULL) {
        return 1;
    }
    if (validate(number1) != 0) {
        return 2;
    }
    if (validate(number2) != 0) {
        return 2;
    }
    int comp = compare(number1, number2);
    if (comp == 0 || comp == 1) {//n1 == n2 || n1 > n2
        if (*(number1 + 0) == 45) {
            *result = (char *) calloc((int) strlen(number2) + 3, 1);
            if (*result == NULL) {
                return 3;
            }
            const char ch_min = '-';
            strncat(*result, &ch_min, 1);
            int longer = (int) strlen(number2) - 1, shorter = (int) strlen(number1) - 1, carry = 0, diff =
                    longer - shorter;
            for (int i = shorter - 1; i >= 0; i--) {
                int sum = (int) ((*(number1 + i + 1) - '0') + (*(number2 + i + diff + 1) - '0') + carry);
                const char ch = (const char) (sum % 10 + '0');
                strncat(*result, &ch, 1);
                carry = sum / 10;
            }
            for (int i = diff - 1; i >= 0; i--) {
                int sum = (int) ((*(number2 + i + 1) - '0') + carry);
                const char ch = (const char) (sum % 10 + '0');
                strncat(*result, &ch, 1);
                carry = sum / 10;
            }
            if (carry) {
                const char ch = (const char) (carry + '0');
                strncat(*result, &ch, 1);
            }

            reverse(*result, 1, (int) strlen(*result) - 1);

        } else if (*(number1 + 0) != 45 && *(number2 + 0) == 45) {
            if (strlen(number2) - 1 > strlen(number1)) {

                *result = (char *) calloc(strlen(number2) + 3, 1);
                if (*result == NULL) {
                    return 3;
                }
                const char ch_min = '-';
                strncat(*result, &ch_min, 1);
                int longer = (int) strlen(number2) - 1, shorter = (int) strlen(number1), carry = 0, diff =
                        longer - shorter;
                for (int i = shorter - 1; i >= 0; i--) {
                    int sub = (int) ((*(number2 + i + diff + 1) - '0') - (*(number1 + i) - '0') - carry);
                    if (sub < 0) {
                        sub = sub + 10;
                        carry = 1;
                    } else {
                        carry = 0;
                    }
                    const char ch = (const char) (sub + '0');
                    strncat(*result, &ch, 1);
                }
                for (int i = diff - 1; i >= 0; i--) {
                    if (*(number2 + i + 1) == '0' && carry) {
                        const char ch = '9';
                        strncat(*result, &ch, 1);
                        continue;
                    }
                    int sub = ((*(number2 + i + 1) - '0') - carry);
                    if (i > 0 || sub > 0) {
                        const char ch = (const char) (sub + '0');
                        strncat(*result, &ch, 1);
                    }
                    carry = 0;

                }
                reverse(*result, 1, (int) strlen(*result) - 1);

            } else {
                *result = (char *) calloc(strlen(number1) + 3, 1);
                if (*result == NULL) {
                    return 3;
                }

                int longer = (int) strlen(number1), shorter = (int) strlen(number2) - 1, carry = 0, diff =
                        longer - shorter;
                for (int i = shorter - 1; i >= 0; i--) {
                    int sub = (int) ((*(number1 + i + diff) - '0') - (*(number2 + i + 1) - '0') - carry);
                    if (sub < 0) {
                        sub = sub + 10;
                        carry = 1;
                    } else {
                        carry = 0;
                    }
                    const char ch = (const char) (sub + '0');
                    strncat(*result, &ch, 1);
                }
                for (int i = diff - 1; i >= 0; i--) {
                    if (*(number1 + i) == '0' && carry) {
                        const char ch = '9';
                        strncat(*result, &ch, 1);
                        continue;
                    }
                    int sub = ((*(number1 + i) - '0') - carry);
                    if (i > 0 || sub > 0) {
                        const char ch = (const char) (sub + '0');
                        strncat(*result, &ch, 1);
                    }
                    carry = 0;

                }
                reverse(*result, 0, (int) strlen(*result) - 1);
            }
            if (compare(number1, *result) == -1) {
                free(*result);
                *result = (char *) calloc(strlen(number2) + 3, 1);
                if (*result == NULL) {
                    return 3;
                }
                const char ch_min = '-';
                strncat(*result, &ch_min, 1);
                int longer = (int) strlen(number2) - 1, shorter = (int) strlen(number1), carry = 0, diff =
                        longer - shorter;
                for (int i = shorter - 1; i >= 0; i--) {
                    int sub = (int) ((*(number2 + i + diff + 1) - '0') - (*(number1 + i) - '0') - carry);
                    if (sub < 0) {
                        sub = sub + 10;
                        carry = 1;
                    } else {
                        carry = 0;
                    }
                    if (i == 0 && sub == 0) {

                    } else {
                        const char ch = (const char) (sub + '0');
                        strncat(*result, &ch, 1);
                    }
                }
                for (int i = diff - 1; i >= 0; i--) {
                    if (*(number2 + i + 1) == '0' && carry) {
                        const char ch = '9';
                        strncat(*result, &ch, 1);
                        continue;
                    }
                    int sub = ((*(number2 + i + 1) - '0') - carry);
                    if (i > 0 || sub > 0) {
                        const char ch = (const char) (sub + '0');
                        strncat(*result, &ch, 1);
                    }
                    carry = 0;
                }
                if (*(*result + strlen(*result) - 1) == 48) {
                    *(*result + strlen(*result) - 1) = '\0';
                }
                reverse(*result, 1, (int) strlen(*result) - 1);
            }
        } else {
            *result = (char *) calloc((int) strlen(number1) + 3, 1);
            if (*result == NULL) {
                return 3;
            }
            int longer = (int) strlen(number1), shorter = (int) strlen(number2), carry = 0, diff = longer - shorter;
            for (int i = shorter - 1; i >= 0; i--) {
                int sum = (int) ((*(number2 + i) - '0') + (*(number1 + i + diff) - '0') + carry);
                const char ch = (const char) (sum % 10 + '0');
                strncat(*result, &ch, 1);
                carry = sum / 10;
            }
            for (int i = diff - 1; i >= 0; i--) {
                int sum = (int) ((*(number1 + i) - '0') + carry);
                const char ch = (const char) (sum % 10 + '0');
                strncat(*result, &ch, 1);
                carry = sum / 10;
            }
            if (carry) {
                const char ch = (const char) (carry + '0');
                strncat(*result, &ch, 1);
            }

            reverse(*result, 0, (int) strlen(*result) - 1);
        }
    } else if (comp == -1) {//n1 < n2
        if (*(number2 + 0) == 45) {
            *result = (char *) calloc((int) strlen(number1) + 3, 1);
            if (*result == NULL) {
                return 3;
            }
            const char ch_min = '-';
            strncat(*result, &ch_min, 1);
            int longer = (int) strlen(number1) - 1, shorter = (int) strlen(number2) - 1, carry = 0, diff =
                    longer - shorter;
            for (int i = shorter - 1; i >= 0; i--) {
                int sum = (int) ((*(number2 + i + 1) - '0') + (*(number1 + i + diff + 1) - '0') + carry);
                const char ch = (const char) (sum % 10 + '0');
                strncat(*result, &ch, 1);
                carry = sum / 10;
            }
            if (diff != 0) {
                for (int i = diff - 1; i >= 0; i--) {
                    int sum = (int) ((*(number1 + i + 1) - '0') + carry);
                    const char ch = (const char) (sum % 10 + '0');
                    strncat(*result, &ch, 1);
                    carry = sum / 10;
                }
            }
            if (carry) {
                const char ch = (const char) (carry + '0');
                strncat(*result, &ch, 1);
            }

            reverse(*result, 1, (int) strlen(*result) - 1);
        } else if (*(number2 + 0) != 45 && *(number1 + 0) == 45) {
            if (strlen(number2) > strlen(number1) - 1) {
                *result = (char *) calloc(strlen(number2) + 3, 1);
                if (*result == NULL) {
                    return 3;
                }
                int longer = (int) strlen(number2), shorter = (int) strlen(number1) - 1, carry = 0, diff =
                        longer - shorter;
                for (int i = shorter - 1; i >= 0; i--) {
                    int sub = (int) ((*(number2 + i + diff) - '0') - (*(number1 + i + 1) - '0') - carry);
                    if (sub < 0) {
                        sub = sub + 10;
                        carry = 1;
                    } else {
                        carry = 0;
                    }
                    const char ch = (const char) (sub + '0');
                    strncat(*result, &ch, 1);
                }
                for (int i = diff - 1; i >= 0; i--) {
                    if (*(number2 + i) == '0' && carry) {
                        const char ch = '0';
                        strncat(*result, &ch, 1);
                        continue;
                    }
                    int sub = ((*(number2 + i) - '0') - carry);
                    if (i > 0 || sub > 0) {
                        const char ch = (const char) (sub + '0');
                        strncat(*result, &ch, 1);
                    }
                    carry = 0;
                }

                reverse(*result, 0, (int) strlen(*result) - 1);
            } else if (strlen(number2) < strlen(number1) - 1) {
                *result = (char *) calloc(strlen(number1) + 3, 1);
                if (*result == NULL) {
                    return 3;
                }
                const char ch_min = '-';
                strncat(*result, &ch_min, 1);
                if (strcmp(number2, "0") == 0) {
                    strcpy(*result, number1);
                } else {
                    int longer = (int) strlen(number1) - 1, shorter = (int) strlen(number2), carry = 0, diff =
                            longer - shorter;
                    for (int i = shorter - 1; i >= 0; i--) {
                        int sub = (int) ((*(number1 + i + diff + 1) - '0') - (*(number2 + i) - '0') - carry);
                        if (sub < 0) {
                            sub = sub + 10;
                            carry = 1;
                        } else {
                            carry = 0;
                        }
                        const char ch = (const char) (sub + '0');
                        strncat(*result, &ch, 1);
                    }
                    for (int i = diff - 1; i >= 0; i--) {
                        if (*(number1 + i + 1) == '0' && carry) {
                            const char ch = '9';
                            strncat(*result, &ch, 1);
                            continue;
                        }
                        int sub = ((*(number1 + i + 1) - '0') - carry);
                        if (sub > 0 || i > 0) {
                            const char ch = (const char) (sub + '0');
                            strncat(*result, &ch, 1);
                        }
                        carry = 0;

                    }
                    reverse(*result, 1, (int) strlen(*result) - 1);
                }
            } else {
                *result = (char *) calloc(strlen(number2) + 3, 1);
                if (*result == NULL) {
                    return 3;
                }
                int longer = (int) strlen(number2), shorter = (int) strlen(number1) - 1, carry = 0, diff =
                        longer - shorter;
                for (int i = shorter - 1; i >= 0; i--) {
                    int sub = (int) ((*(number2 + i + diff) - '0') - (*(number1 + i + 1) - '0') - carry);
                    if (sub < 0) {
                        sub = sub + 10;
                        carry = 1;
                    } else {
                        carry = 0;
                    }
                    const char ch = (const char) (sub + '0');
                    strncat(*result, &ch, 1);
                }
                for (int i = diff - 1; i >= 0; i--) {
                    if (*(number2 + i) == '0' && carry) {
                        const char ch = '9';
                        strncat(*result, &ch, 1);
                        continue;
                    }
                    int sub = ((*(number2 + i) - '0') - carry);
                    if (i > 0 || sub > 0) {
                        const char ch = (const char) (sub + '0');
                        strncat(*result, &ch, 1);
                    }
                    carry = 0;
                }

                reverse(*result, 0, (int) strlen(*result) - 1);
                if (compare(number2, *result) == -1) {
                    free(*result);
                    *result = (char *) calloc(strlen(number2) + 3, 1);
                    if (*result == NULL) {
                        return 3;
                    }
                    const char ch_min = '-';
                    strncat(*result, &ch_min, 1);
                    longer = (int) strlen(number2), shorter = (int) strlen(number1) - 1, carry = 0, diff =
                            longer - shorter;
                    for (int i = shorter - 1; i >= 0; i--) {
                        int sub = (int) ((*(number1 + i + diff + 1) - '0') - (*(number2 + i) - '0') - carry);
                        if (sub < 0) {
                            sub = sub + 10;
                            carry = 1;
                        } else {
                            carry = 0;
                        }
                        if (i == 0 && sub == 0) {

                        } else {
                            const char ch = (const char) (sub + '0');
                            strncat(*result, &ch, 1);
                        }
                    }
                    for (int i = diff - 1; i >= 0; i--) {
                        if (*(number1 + i + 1) == '0' && carry) {
                            const char ch = '9';
                            strncat(*result, &ch, 1);
                            continue;
                        }
                        int sub = ((*(number1 + i + 1) - '0') - carry);
                        if (i > 0 || sub > 0) {
                            const char ch = (const char) (sub + '0');
                            strncat(*result, &ch, 1);
                        }
                        carry = 0;

                    }
                    reverse(*result, 1, (int) strlen(*result) - 1);
                }
            }
        } else {
            *result = (char *) calloc(strlen(number2) + 3, 1);
            if (*result == NULL) {
                return 3;
            }
            int longer = (int) strlen(number2), shorter = (int) strlen(number1), carry = 0, diff = longer - shorter;
            for (int i = shorter - 1; i >= 0; i--) {
                int sum = (int) ((*(number1 + i) - '0') + (*(number2 + i + diff) - '0') + carry);
                const char ch = (const char) (sum % 10 + '0');
                strncat(*result, &ch, 1);
                carry = sum / 10;
            }
            for (int i = diff - 1; i >= 0; i--) {
                int sum = (int) ((*(number2 + i) - '0') + carry);
                const char ch = (const char) (sum % 10 + '0');
                strncat(*result, &ch, 1);
                carry = sum / 10;
            }
            if (carry) {
                const char ch = (const char) (carry + '0');
                strncat(*result, &ch, 1);

            }

            reverse(*result, 0, (int) strlen(*result) - 1);
        }
    }
    int i;
    if (*(*result + 0) == 45) {
        i = 1;
    } else {
        i = 0;
    }
    while (*(*result + i) == 48 && *(*result + i + 1) != '\0') {
        memmove((*result + i), (*result + i + 1), strlen(*result) - i);
    }
    return 0;
}

int subtract(const char *number1, const char *number2, char **result) {
    if (number1 == NULL || number2 == NULL || result == NULL) {
        return 1;
    }
    if (validate(number1) != 0) {
        return 2;
    }
    if (validate(number2) != 0) {
        return 2;
    }
    int comp = compare(number1, number2);
    if (comp == 0 || comp == 1) {//n1 == n2 || n1 > n2
        if (*(number1 + 0) == 45 && *(number2 + 0) == 45) {

            *result = (char *) calloc(strlen(number2) - 1 + 3, 1);
            if (*result == NULL) {
                return 3;
            }
            int longer = (int) strlen(number2) - 1, shorter = (int) strlen(number1) - 1, carry = 0, diff =
                    longer - shorter;
            for (int i = shorter - 1; i >= 0; i--) {
                int sub = (int) ((*(number2 + i + diff + 1) - '0') - (*(number1 + i + 1) - '0') - carry);
                if (sub < 0) {
                    sub = sub + 10;
                    carry = 1;
                } else {
                    carry = 0;
                }
                const char ch = (const char) (sub + '0');
                strncat(*result, &ch, 1);
            }
            for (int i = diff - 1; i >= 0; i--) {
                if (*(number2 + i + 1) == '0' && carry) {
                    const char ch = '9';
                    strncat(*result, &ch, 1);
                    continue;
                }
                int sub = ((*(number2 + i + 1) - '0') - carry);
                if (i > 0 || sub > 0) {
                    const char ch = (const char) (sub + '0');
                    strncat(*result, &ch, 1);
                }
                carry = 0;
            }

            reverse(*result, 0, (int) strlen(*result) - 1);

        } else if (*(number1 + 0) != 45 && *(number2 + 0) == 45) {
            if (strlen(number1) > strlen(number2) - 1) {
                *result = (char *) calloc(strlen(number1) + 3, 1);
                if (*result == NULL) {
                    return 3;
                }
                int longer = (int) strlen(number1), shorter = (int) strlen(number2) - 1, carry = 0, diff =
                        longer - shorter;
                for (int i = shorter - 1; i >= 0; i--) {
                    int sum = (int) ((*(number2 + i + 1) - '0') + (*(number1 + i + diff) - '0') + carry);
                    const char ch = (const char) (sum % 10 + '0');
                    strncat(*result, &ch, 1);
                    carry = sum / 10;
                }
                for (int i = diff - 1; i >= 0; i--) {
                    int sum = (int) ((*(number1 + i) - '0') + carry);
                    const char ch = (const char) (sum % 10 + '0');
                    strncat(*result, &ch, 1);
                    carry = sum / 10;
                }
                if (carry) {
                    const char ch = (const char) (carry + '0');
                    strncat(*result, &ch, 1);
                }

                reverse(*result, 0, (int) strlen(*result) - 1);
            } else {
                *result = (char *) calloc(strlen(number2) - 1 + 3, 1);
                if (*result == NULL) {
                    return 3;
                }
                int longer = (int) strlen(number2) - 1, shorter = (int) strlen(number1), carry = 0, diff =
                        longer - shorter;
                for (int i = shorter - 1; i >= 0; i--) {
                    int sum = (int) ((*(number1 + i) - '0') + (*(number2 + i + diff + 1) - '0') + carry);
                    const char ch = (const char) (sum % 10 + '0');
                    strncat(*result, &ch, 1);
                    carry = sum / 10;
                }
                for (int i = diff - 1; i >= 0; i--) {
                    int sum = (int) ((*(number2 + i + 1) - '0') + carry);
                    const char ch = (const char) (sum % 10 + '0');
                    strncat(*result, &ch, 1);
                    carry = sum / 10;
                }
                if (carry) {
                    const char ch = (const char) (carry + '0');
                    strncat(*result, &ch, 1);
                }

                reverse(*result, 0, (int) strlen(*result) - 1);
            }
        } else {
            *result = (char *) calloc(strlen(number1) + 3, 1);
            if (*result == NULL) {
                return 3;
            }
            int longer = (int) strlen(number1), shorter = (int) strlen(number2), carry = 0, diff = longer - shorter;
            for (int i = shorter - 1; i >= 0; i--) {
                int sub = (int) ((*(number1 + i + diff) - '0') - (*(number2 + i) - '0') - carry);
                if (sub < 0) {
                    sub = sub + 10;
                    carry = 1;
                } else {
                    carry = 0;
                }
                const char ch = (const char) (sub + '0');
                strncat(*result, &ch, 1);
            }
            for (int i = diff - 1; i >= 0; i--) {
                if (*(number1 + i) == '0' && carry) {
                    const char ch = '9';
                    strncat(*result, &ch, 1);
                    continue;
                }
                int sub = ((*(number1 + i) - '0') - carry);
                if (i > 0 || sub > 0) {
                    const char ch = (const char) (sub + '0');
                    strncat(*result, &ch, 1);
                }
                carry = 0;

            }
            reverse(*result, 0, (int) strlen(*result) - 1);
        }

    } else if (comp == -1) { //n1 < n2
        if (*(number1 + 0) == 45 && *(number2 + 0) == 45) {
            *result = (char *) calloc(strlen(number1) - 1 + 3, 1);
            if (*result == NULL) {
                return 3;
            }
            const char ch_min = '-';
            strncat(*result, &ch_min, 1);
            int longer = (int) strlen(number1) - 1, shorter = (int) strlen(number2) - 1, carry = 0, diff =
                    longer - shorter;
            for (int i = shorter - 1; i >= 0; i--) {
                int sub = (int) ((*(number1 + i + diff + 1) - '0') - (*(number2 + i + 1) - '0') - carry);
                if (sub < 0) {
                    sub = sub + 10;
                    carry = 1;
                } else {
                    carry = 0;
                }
                const char ch = (const char) (sub + '0');
                strncat(*result, &ch, 1);
            }
            for (int i = diff - 1; i >= 0; i--) {
                if (*(number1 + i + 1) == '0' && carry) {
                    const char ch = '9';
                    strncat(*result, &ch, 1);
                    continue;
                }
                int sub = ((*(number1 + i + 1) - '0') - carry);
                if (i > 0 || sub > 0) {
                    const char ch = (const char) (sub + '0');
                    strncat(*result, &ch, 1);
                }
                carry = 0;
            }

            reverse(*result, 1, (int) strlen(*result) - 1);
        } else if (*(number1 + 0) == 45 && *(number2 + 0) != 45) {
            if (strlen(number1) - 1 > strlen(number2)) {
                *result = (char *) calloc(strlen(number1) - 1 + 3, 1);
                if (*result == NULL) {
                    return 3;
                }
                const char ch_min = '-';
                strncat(*result, &ch_min, 1);
                int longer = (int) strlen(number1) - 1, shorter = (int) strlen(number2), carry = 0, diff =
                        longer - shorter;
                for (int i = shorter - 1; i >= 0; i--) {
                    int sum = (int) ((*(number2 + i) - '0') + (*(number1 + i + diff + 1) - '0') + carry);
                    const char ch = (const char) (sum % 10 + '0');
                    strncat(*result, &ch, 1);
                    carry = sum / 10;
                }
                for (int i = diff - 1; i >= 0; i--) {
                    int sum = (int) ((*(number1 + i + 1) - '0') + carry);
                    const char ch = (const char) (sum % 10 + '0');
                    strncat(*result, &ch, 1);
                    carry = sum / 10;
                }
                if (carry) {
                    const char ch = (const char) (carry + '0');
                    strncat(*result, &ch, 1);
                }

                reverse(*result, 1, (int) strlen(*result) - 1);
            } else {
                *result = (char *) calloc(strlen(number2) + 3, 1);
                if (*result == NULL) {
                    return 3;
                }
                const char ch_min = '-';
                strncat(*result, &ch_min, 1);
                int longer = (int) strlen(number2), shorter = (int) strlen(number1) - 1, carry = 0, diff =
                        longer - shorter;
                for (int i = shorter - 1; i >= 0; i--) {
                    int sum = (int) ((*(number1 + i + 1) - '0') + (*(number2 + i + diff) - '0') + carry);
                    const char ch = (const char) (sum % 10 + '0');
                    strncat(*result, &ch, 1);
                    carry = sum / 10;
                }
                for (int i = diff - 1; i >= 0; i--) {
                    int sum = (int) ((*(number2 + i) - '0') + carry);
                    const char ch = (const char) (sum % 10 + '0');
                    strncat(*result, &ch, 1);
                    carry = sum / 10;
                }
                if (carry) {
                    const char ch = (const char) (carry + '0');
                    strncat(*result, &ch, 1);
                }

                reverse(*result, 1, (int) strlen(*result) - 1);
            }
        } else {
            *result = (char *) calloc(strlen(number2) + 3, 1);
            if (*result == NULL) {
                return 3;
            }
            const char ch_min = '-';
            strncat(*result, &ch_min, 1);
            int longer = (int) strlen(number2), shorter = (int) strlen(number1), carry = 0, diff = longer - shorter;
            for (int i = shorter - 1; i >= 0; i--) {
                int sub = (int) ((*(number2 + i + diff) - '0') - (*(number1 + i) - '0') - carry);
                if (sub < 0) {
                    sub = sub + 10;
                    carry = 1;
                } else {
                    carry = 0;
                }
                const char ch = (const char) (sub + '0');
                strncat(*result, &ch, 1);
            }
            for (int i = diff - 1; i >= 0; i--) {
                if (*(number2 + i) == '0' && carry) {
                    const char ch = '9';
                    strncat(*result, &ch, 1);
                    continue;
                }
                int sub = ((*(number2 + i) - '0') - carry);
                if (i > 0 || sub > 0) {
                    const char ch = (const char) (sub + '0');
                    strncat(*result, &ch, 1);
                }
                carry = 0;
            }

            reverse(*result, 1, (int) strlen(*result) - 1);
        }
    }
    int i;
    if (*(*result + 0) == 45) {
        i = 1;
    } else {
        i = 0;
    }
    while (*(*result + i) == 48 && *(*result + i + 1) != '\0') {
        memmove((*result + i), (*result + i + 1), strlen(*result) - i);
    }
    return 0;
}

int multiply(const char *number1, const char *number2, char **result) {
    if (number1 == NULL || number2 == NULL || result == NULL) {
        return 1;
    }
    if (validate(number1) != 0) {
        return 2;
    }
    if (validate(number2) != 0) {
        return 2;
    }

    if (*(number1 + 0) == '0' || *(number2 + 0) == '0') {
        *result = (char*)calloc(2, 1);
        if (*result == NULL) {
            return 3;
        }
        strcpy(*result, "0");
        return 0;
    }

    if (*(number1 + 0) == 45 && *(number2 + 0) == 45) {
        int len1 = strlen(number1) - 1, len2 = strlen(number2) - 1, carry = 0;
        *result = (char*)calloc(len2 + len1 + 3, 1);

        if (*result == NULL) {
            return 3;
        }
        int *result_tab = (int*)calloc(len1 + len2 + 3, sizeof(int));
        if (result_tab == NULL) {
            free(*result);
            return 3;
        }
        int i_n1 = 0;
        int i_n2 = 0;
        for (int i = len1 - 1; i >= 0; i--) {
            carry = 0;
            int n1 = (*(number1 + i + 1) - '0');
            i_n2 = 0;
            for (int j = len2 - 1; j >= 0; j--) {
                int n2 = (*(number2 + j + 1) - '0');
                int sum = n1 * n2 + *(result_tab + i_n1 + i_n2) + carry;
                carry = sum / 10;
                *(result_tab + i_n1 + i_n2) = sum % 10;
                i_n2++;
            }
            if (carry > 0) {
                *(result_tab + i_n1 + i_n2) += carry;
            }
            i_n1++;
        }


        int i = i_n2 + i_n1 - 1;
        while (i >= 0 && *(result_tab + i) == '0') {
            i--;
        }
        if (i == -1) {
            strcpy(*result, "0");
        }
        for (int j = 0; j < i_n2 + i_n1; j++) {
            const char ch = (const char) (*(result_tab + j) + '0');
            strncat(*result, &ch, 1);
        }
        reverse(*result, 0, strlen(*result) - 1);
        free(result_tab);
    } else if (*(number1 + 0) == 45 && *(number2 + 0) != 45) {
        int len1 = strlen(number1) - 1, len2 = strlen(number2), carry = 0;
        *result = (char*)calloc(len2 + len1 + 3, 1);

        if (*result == NULL) {
            return 3;
        }
        const char ch_min = '-';
        strncat(*result, &ch_min, 1);
        int *result_tab = (int*)calloc(len1 + len2 + 3, sizeof(int));
        if (result_tab == NULL) {
            free(*result);
            return 3;
        }
        int i_n1 = 0;
        int i_n2 = 0;
        for (int i = len1 - 1; i >= 0; i--) {
            carry = 0;
            int n1 = (*(number1 + i + 1) - '0');
            i_n2 = 0;
            for (int j = len2 - 1; j >= 0; j--) {
                int n2 = (*(number2 + j) - '0');
                int sum = n1 * n2 + *(result_tab + i_n1 + i_n2) + carry;
                carry = sum / 10;
                *(result_tab + i_n1 + i_n2) = sum % 10;
                i_n2++;
            }
            if (carry > 0) {
                *(result_tab + i_n1 + i_n2) += carry;
            }
            i_n1++;
        }


        int i = i_n2 + i_n1 - 1;
        while (i >= 0 && *(result_tab + i) == '0') {
            i--;
        }
        if (i == -1) {
            strcpy(*result, "0");
        }
        for (int j = 0; j < i_n2 + i_n1; j++) {
            const char ch = (const char) (*(result_tab + j) + '0');
            strncat(*result, &ch, 1);
        }
        reverse(*result, 1, strlen(*result) - 1);
        free(result_tab);


    } else if (*(number1 + 0) != 45 && *(number2 + 0) == 45) {
        int len1 = strlen(number1), len2 = strlen(number2) - 1, carry = 0;
        *result = (char*)calloc(len2 + len1 + 3, 1);

        if (*result == NULL) {
            return 3;
        }
        const char ch_min = '-';
        strncat(*result, &ch_min, 1);
        int *result_tab = (int*)calloc(len1 + len2 + 3, sizeof(int));
        if (result_tab == NULL) {
            free(*result);
            return 3;
        }
        int i_n1 = 0;
        int i_n2 = 0;
        for (int i = len1 - 1; i >= 0; i--) {
            carry = 0;
            int n1 = (*(number1 + i) - '0');
            i_n2 = 0;
            for (int j = len2 - 1; j >= 0; j--) {
                int n2 = (*(number2 + j + 1) - '0');
                int sum = n1 * n2 + *(result_tab + i_n1 + i_n2) + carry;
                carry = sum / 10;
                *(result_tab + i_n1 + i_n2) = sum % 10;
                i_n2++;
            }
            if (carry > 0) {
                *(result_tab + i_n1 + i_n2) += carry;
            }
            i_n1++;
        }


        int i = i_n2 + i_n1 - 1;
        while (i >= 0 && *(result_tab + i) == '0') {
            i--;
        }
        if (i == -1) {
            strcpy(*result, "0");
        }
        for (int j = 0; j < i_n2 + i_n1; j++) {
            const char ch = (const char) (*(result_tab + j) + '0');
            strncat(*result, &ch, 1);
        }
        reverse(*result, 1, strlen(*result) - 1);
        free(result_tab);

    } else {
        int len1 = strlen(number1), len2 = strlen(number2), carry = 0;
        *result = (char*)calloc(len2 + len1 + 3, 1);

        if (*result == NULL) {
            return 3;
        }
        int *result_tab = (int*)calloc(len1 + len2 + 3, sizeof(int));
        if (result_tab == NULL) {
            free(*result);
            return 3;
        }
        int i_n1 = 0;
        int i_n2 = 0;
        for (int i = len1 - 1; i >= 0; i--) {
            carry = 0;
            int n1 = (*(number1 + i) - '0');
            i_n2 = 0;
            for (int j = len2 - 1; j >= 0; j--) {
                int n2 = (*(number2 + j) - '0');
                int sum = n1 * n2 + *(result_tab + i_n1 + i_n2) + carry;
                carry = sum / 10;
                *(result_tab + i_n1 + i_n2) = sum % 10;
                i_n2++;
            }
            if (carry > 0) {
                *(result_tab + i_n1 + i_n2) += carry;
            }
            i_n1++;
        }


        int i = i_n2 + i_n1 - 1;
        while (i >= 0 && *(result_tab + i) == '0') {
            i--;
        }
        if (i == -1) {
            strcpy(*result, "0");
        }
        for (int j = 0; j < i_n2 + i_n1; j++) {
            const char ch = (const char) (*(result_tab + j) + '0');
            strncat(*result, &ch, 1);
        }
        reverse(*result, 0, strlen(*result) - 1);
        free(result_tab);
    }
    int i;
    if (*(*result + 0) == 45) {
        i = 1;
    } else {
        i = 0;
    }
    while (*(*result + i) == 48 && *(*result + i + 1) != '\0') {
        memmove((*result + i), (*result + i + 1), strlen(*result) - i);
    }
    return 0;
}

void reverse(char *x, int begin, int end) {
    char c;

    if (begin >= end) {
        return;
    }

    c = *(x + begin);
    *(x + begin) = *(x + end);
    *(x + end) = c;

    reverse(x, ++begin, --end);
}