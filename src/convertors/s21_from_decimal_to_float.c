#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int exit_status = 0;
  if (!dst || !s21_check_bit(src)) {
    exit_status = 1;
  } else {
    s21_decimal temp_src = src;
    int sign = s21_get_sign(src);
    if (sign == 1) {
      s21_change_sign(&temp_src);
    }
    double temp_dst = 0.0;
    int scale = s21_get_scale(src);
    for (int i = 0; i < S21_BIT_TOTAL_NUMBER; i++) {
      if (s21_get_bit(src, i)) {
        temp_dst += pow(2.0, i);
      }
    }
    temp_dst /= pow(10.0, scale);
    if (sign) {
      temp_dst *= -1;
    }
    *dst = (float)temp_dst;
  }
  return exit_status;
}