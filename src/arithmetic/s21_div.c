#include "../s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int scail_len_val1 = scail_len(value_1);
  int scail_len_val2 = scail_len(value_2);
  int sign = 0;

  // unsigned char lower_pow;
  int error_back = 0;

  result->bits[3] = 0;

  if (value_2.bits[0] == 0 && value_2.bits[1] == 0 && value_2.bits[2] == 0) {
    error_back = 3;
  }

  if (scail_len_val1 < 29 && scail_len_val2 < 29 && error_back != 3) {
    if ((value_1.bits[3] & (1 << 31)) != (value_2.bits[3] & (1 << 31))) {
      sign = -1;
    } else {
      sign = 1;
    }

    error_back = del_decimal(&value_1, value_2, sign);

    for (int i = 0; i < 4; i++) {
      result->bits[i] = value_1.bits[i];
    }
  }

  return error_back;
}