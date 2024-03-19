#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int exit_status = 0;
  s21_decimal temp;
  s21_truncate(src, &temp);
  if ((temp.bits[2] || temp.bits[1] || temp.bits[0] > S21_MAX_INT) || !dst) {
    exit_status = 1;
  } else {
    *dst = temp.bits[0];
    if (s21_get_sign(src)) {
      *dst = *dst * (-1);
    }
  }
  return exit_status;
}