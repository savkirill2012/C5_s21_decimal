#include "../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal lower, bigger;
  int error_back = 0;
  int sign_change = 0;
  int normalization_overflow = 0;
  int scail_len_val1 = scail_len(value_1);
  int scail_len_val2 = scail_len(value_2);

  // изменение знака
  change_sign(&value_2);

  int diff = scail_len_val1 - scail_len_val2;

  if (scail_len_val1 < 29 && scail_len_val2 < 29) {
    // нормализация степени
    normalization_overflow = normalization_val(&value_1, &value_2, diff);

    // определение меньшего и большего числа
    search_low_and_big_val(value_1, value_2, &lower, &bigger);

    // rigth len
    if (diff < 0) {
      if (normalization_overflow) {
        result->bits[3] = value_1.bits[3];
      } else {
        result->bits[3] = value_2.bits[3];
      }
    } else {
      if (normalization_overflow) {
        result->bits[3] = value_2.bits[3];
      } else {
        result->bits[3] = value_1.bits[3];
      }
    }

    // minus or plus
    if ((value_1.bits[3] & (1 << 31)) != (value_2.bits[3] & (1 << 31))) {
      sign_change = 1;
    }

    // rigth sign
    if (sign_change) {
      if (bigger.bits[3] & (1 << 31)) {
        result->bits[3] = result->bits[3] | (1 << 31);
      } else {
        result->bits[3] = result->bits[3] & ~(1 << 31);
      }
    }

    // logic
    if (sign_change == 0) {
      error_back = sum_decimal(&bigger, lower);
    } else {
      minus_decimal(&bigger, lower);
    }

    if (error_back && (bigger.bits[3] & (1 << 31))) {
      error_back = 2;
    } else {
      // copy to res
      for (int i = 0; i < 3; i++) {
        result->bits[i] = bigger.bits[i];
      }
      error_back = check_if_min_or_max_val(*result, error_back);
    }
  } else {
    error_back = 2;
  }

  return error_back;
}