#include "../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int exit_status = 0;
  if (!dst || src != src || fabs(src) > S21_MAX_DECIMAL ||
      (fabs(src) > 0 && fabs(src) < S21_MIN_DECIMAL)) {
    exit_status = 1;
  } else {
    unsigned int value = 0;
    int scale = find_scale(src, &value);
    s21_decimal temp;
    s21_decimal helper;
    s21_from_int_to_decimal(value, &temp);
    if (src < 0) {
      s21_set_sign(&temp, 1);
    }
    if (scale > S21_MAX_POW) {
      s21_set_scale(&temp, scale);
      s21_set_scale(&helper, S21_MAX_POW);
      div_simple(&temp, &helper);
    } else if (scale < S21_MIN_POW) {
      s21_set_scale(&helper, abs(scale));
      s21_common_scale(&helper, &temp);
      s21_set_scale(&temp, S21_MIN_POW);
    } else {
      s21_set_scale(&temp, abs(scale));
    }
    *dst = temp;
  }
  return exit_status;
}