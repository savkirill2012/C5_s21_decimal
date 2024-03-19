#include <math.h>
#include <stdlib.h>

#include "../s21_decimal.h"

int s21_is_zero(s21_decimal val) {
  int error = 0;
  s21_decimal zero_value = {0};
  for (int i = 2; i > -1; i--) {
    if (val.bits[i] != zero_value.bits[i]) error++;
  }
  return error == 0 ? 1 : 0;
}

void s21_scale_equalize(s21_decimal *value1, s21_decimal *value2) {
  s21_decimal *min = NULL;
  int flag = 0;
  int scale1 = get_scale(*value1), scale2 = get_scale(*value2);
  if (scale1 > scale2) {
    min = value2;
  } else {
    int tmp = scale1;
    scale1 = scale2;
    scale2 = tmp;
    min = value1;
  }
  for (int i = scale1 - scale2; (i > 0 && flag == 0); i--) {
    flag = scale_increase(min);
  }
}

int scale_increase(s21_decimal *value) {
  int res = 0;
  int scale = s21_get_scale(*value);
  if (first_bit(*value) < 93 && scale < 28) {
    s21_decimal tmp8 = {0}, tmp2 = {0};
    dec_copy(*value, &tmp2);
    dec_copy(*value, &tmp8);
    for (int i = 0; i < 3; i++) left(&tmp8);
    left(&tmp2);
    bit_addition(tmp8, tmp2, value);
    s21_set_scale(&*value, scale + 1);
  } else {
    res = 1;
  }
  return res;
}

int first_bit(s21_decimal value) {
  int bit = 95;
  for (; bit >= 0 && s21_get_bit(value, bit) == 0; bit--) {
  }
  return bit;
}

void dec_copy(s21_decimal og, s21_decimal *res) {
  for (int i = 0; i < 128; i++) {
    s21_set_bit(res, i, s21_get_bit(og, i));
  }
}

void left(s21_decimal *value) {
  int bit31 = s21_get_bit(*value, 31);
  int bit63 = s21_get_bit(*value, 63);
  value->bits[0] <<= 1;
  value->bits[1] <<= 1;
  value->bits[2] <<= 1;
  if (bit31) s21_set_bit(value, 32, 1);
  if (bit63) s21_set_bit(value, 64, 1);
}

void bit_addition(s21_decimal value1, s21_decimal value2, s21_decimal *res) {
  int tmp = 0, sum = 0;
  for (int i = 0; i < 96; i++) {
    sum = s21_get_bit(value1, i) + s21_get_bit(value2, i);
    if (sum == 2) {
      if (tmp == 1) {
        s21_set_bit(res, i, 1);
      } else {
        s21_set_bit(res, i, 0);
        tmp = 1;
      }
    } else if (sum == 1) {
      if (tmp == 1) {
        s21_set_bit(res, i, 0);
      } else {
        s21_set_bit(res, i, 1);
      }
    } else if (sum == 0) {
      if (tmp == 1) {
        s21_set_bit(res, i, 1);
        tmp = 0;
      } else {
        s21_set_bit(res, i, 0);
      }
    }
  }
}

int get_scale(s21_decimal src) {
  int scale = 0;
  for (int i = S21_FIRST_BIT_SCALE; i < S21_LAST_BIT_SCALE; i++) {
    if (s21_get_bit(src, i + 96)) scale += (1 << (i - S21_FIRST_BIT_SCALE));
  }
  if (scale > 29) scale = 28;
  return scale;
}
