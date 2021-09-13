//
// Created by Marcin on 24.05.2021.
//

#ifndef DANTE_INT_OPERATIONS_H
#define DANTE_INT_OPERATIONS_H
enum operations_t{
    op_add, op_sub, op_div, op_mul
};
typedef int(*fun)(int, int);
fun get_function (enum operations_t x);
int add_int(int a, int b);
int sub_int(int a, int b);
int div_int(int a, int b);
int mul_int(int a, int b);
#endif //DANTE_INT_OPERATIONS_H