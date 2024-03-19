#include "../s21_decimal.h"

// Перевод числа в его fabs состояние
// dec структура которую хотим изменить
//  result  стркутра для записи нового числа

int s21_negate(s21_decimal dec, s21_decimal *result) {
  s21_zero_decimal(result);
  int sign = s21_get_sign(dec);
  *result = dec;
  if (sign == 1) {
    s21_set_bit(result, 127, 0);
  } else {
    s21_set_bit(result, 127, 1);
  }
  return 0;
}