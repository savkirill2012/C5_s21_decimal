#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int exit_status = 0;
  if (!dst)
    exit_status = 1;
  else {
    init_decimal_zero(dst);
    if (src < 0) {
      s21_change_sign(dst);
      src = -src;
    }
    dst->bits[0] = src;
  }
  return exit_status;
}
