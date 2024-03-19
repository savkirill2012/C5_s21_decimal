#include "../s21_decimal.h"

// Округляет указанное Decimal число до ближайшего целого числа в
// отрицательной бесконечности.
// dec структура которую хотим изменить

int s21_floor(s21_decimal value, s21_decimal *result) {
  s21_zero_decimal(result);
  s21_zero_decimal(result);
  s21_truncate(value, result);
  if (s21_get_sign(value) && !s21_is_equal(*result, value)) {
    s21_sub(*result, ((s21_decimal){{1, 0, 0, 0}}), result);
  }
  return 0;
}
