#include "../s21_decimal.h"

int s21_is_less(s21_decimal left, s21_decimal right) {  // <
  return s21_is_greater(right, left);
}