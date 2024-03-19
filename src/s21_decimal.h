#ifndef S21_DECIMAL_H_
#define S21_DECIMAL_H_

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define S21_BIT_BOX 32
#define S21_SIGN_BIT 127
#define S21_MAX_DECIMAL 7.9228162514264337593543950335e28f
#define S21_MIN_DECIMAL 1e-28f
#define S21_FIRST_BIT_SCALE 16
#define S21_LAST_BIT_SCALE 23
#define S21_MAX_POW 28
#define S21_MIN_POW 0
#define S21_MAX_UINT 4294967296U
#define S21_MAX_INT 2147483647
#define S21_BIT_TOTAL_NUMBER 96
#define MAX_DEC powf(2.0f, 96.0f) - 1.0
#define MIN_DEC -powf(2.0f, 96.0f) + 1.0
#define BADINT (unsigned int)0x80000000
#define START_INFO 96

typedef struct {
  int bits[4];
} s21_decimal;

typedef struct {
  int bits[7];
} s21_ldecimal;

// арифметические операции
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// функции сравнения
int s21_is_less(s21_decimal left, s21_decimal right);              // <
int s21_is_less_or_equal(s21_decimal left, s21_decimal right);     // <=
int s21_is_greater(s21_decimal left, s21_decimal right);           // >
int s21_is_greater_or_equal(s21_decimal left, s21_decimal right);  // >=
int s21_is_equal(s21_decimal left, s21_decimal right);             // ==
int s21_is_not_equal(s21_decimal left, s21_decimal right);         // !=

// преобразователи
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// другие функции
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// общие функции
int sum_decimal(s21_decimal *result, s21_decimal loc_val);
int devide_ten_logic(s21_decimal val, s21_decimal *res);
int multy_ten_logic(s21_decimal value, s21_decimal *result);
int normalization_val(s21_decimal *val1, s21_decimal *val2, int dif);
int move_bits_left(s21_decimal *val, int times_move);
int is_bigger(s21_decimal gess_bigger, s21_decimal compare_val);
void init_decimal_zero(s21_decimal *val);
void minus_decimal(s21_decimal *bigger, s21_decimal lower);
s21_decimal minus_one_bit(s21_decimal res);
int s21_get_sign(s21_decimal src);
int s21_get_scale(s21_decimal src);
int s21_get_bit(s21_decimal src, int bit_position);
void s21_set_sign(s21_decimal *dst, int sign);
void s21_set_scale(s21_decimal *dst, int scale);
void s21_set_bit(s21_decimal *dst, int bit_position, int check);
void s21_zero_decimal(s21_decimal *dst);

// вспомогательные функции compare
int s21_is_zero(s21_decimal val);
void s21_scale_equalize(s21_decimal *value1, s21_decimal *value2);
int scale_increase(s21_decimal *value);
void scale_decrease(s21_decimal *value);
int first_bit(s21_decimal value);
void dec_copy(s21_decimal og, s21_decimal *res);
void left(s21_decimal *value);
void bit_addition(s21_decimal value1, s21_decimal value2, s21_decimal *res);
void div_by_ten(s21_decimal *value);
int get_scale(s21_decimal src);

// вспомогательные функции arithmetic
// long double
void init_ldecimal_zeros(s21_ldecimal *val);
int del_normalization(s21_decimal val1, s21_decimal val2,
                      s21_ldecimal *ret_val1, s21_ldecimal *ret_val2);
int multy_long_ten(s21_ldecimal value, s21_ldecimal *result);
int sum_ldecimal(s21_ldecimal *res, s21_ldecimal add_val);
void minus_ldecimal(s21_ldecimal *bigger, s21_ldecimal lower);
s21_ldecimal minus_one_bitl(s21_ldecimal res);
int move_bits_leftl(s21_ldecimal *res, int num_move);
int is_lbigger(s21_ldecimal gess_bigger, s21_ldecimal compare_val);
int long_devide_by_ten(s21_ldecimal val, s21_ldecimal *res);

// double
void change_sign(s21_decimal *val);
int scail_len(s21_decimal val);
int check_if_min_or_max_val(s21_decimal result, int error);
int search_low_and_big_val(s21_decimal val1, s21_decimal val2,
                           s21_decimal *low_val, s21_decimal *big_val);
int mul_decimal(s21_decimal *result, s21_decimal loc_va, int scale, int sign);
int del_decimal(s21_decimal *result, s21_decimal val, int sign);

// вспомогательные функции для преобразователей
void s21_change_sign(s21_decimal *dst);
int find_scale(float src, unsigned int *value);
void s21_common_scale(s21_decimal *first, s21_decimal *second);
void div_simple(s21_decimal *first, s21_decimal *second);
int s21_check_bit(s21_decimal src);
int s21_from_decimal_to_double(s21_decimal src, long double *dst);

#endif  // S21_DECIMAL_H_
