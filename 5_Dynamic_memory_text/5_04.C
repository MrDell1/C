#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int subtract(const char *number1, const char *number2, char **result);

int add(const char *number1, const char *number2, char **result);

int validate(const char *number);

int compare(const char *number1, const char *number2);

void reverse(char *x, int begin, int end);

int main() {
    char *num1, *num2, *res;
    num1 = (char *)malloc(201);
    if (num1 == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }
    num2 = (char *)malloc(201);
    if (num2 == NULL) {
        printf("Failed to allocate memory");
        free(num1);
        return 8;
    }

    printf("Podaj pierwsza liczbe:");
    scanf("%200[^\n]s", num1);
    setbuf(stdin, NULL);

    printf("Podaj druga liczbe:");
    scanf("%200[^\n]s", num2);

    int add_err = 0;
    add_err = add(num1, num2, &res);
    if (add_err != 0) {
        if(add_err == 3) {
            printf("Failed to allocate memory");
            free(num1);
            free(num2);
            return 8;
        }
        else{
            printf("Incorrect input");
            free(num1);
            free(num2);
            return 1;
        }
       
    }
    printf("%s\n", res);
    free(res);
    int sub_err = 0;
    sub_err = subtract(num1, num2, &res);
    if (sub_err != 0) {
        if(sub_err == 3) {
            printf("Failed to allocate memory");
            free(num1);
            free(num2);
            return 8;
        }
        else{
            printf("Incorrect input");
            free(num1);
            free(num2);
            return 1;
        }

    }
    printf("%s", res);
    free(res);
    free(num1);
    free(num2);
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

int compare(const char *number1, const char *number2) {
    if (number1 == NULL || number2 == NULL) {
        return 2;
    }
    if (validate(number1) != 0) {
        return 3;
    }
    if (validate(number2) != 0) {
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
                for (int i = shorter - 1; i > 0; i--) {
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
                for (int i = diff; i >= 0; i--) {
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
                        if (sub > 0) {
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
            if(strlen(number1) > strlen(number2) - 1){
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
            }
            else {
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
            for (int i = diff - 1; i > 0; i--) {
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
            if(strlen(number1) - 1 > strlen(number2)) {
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
            }
            else{
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