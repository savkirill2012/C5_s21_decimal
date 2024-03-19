#include "../s21_decimal.h"

int s21_is_equal(s21_decimal left, s21_decimal right) {
  // возвращает 0 - не равны
  // 1 - равны
  int result = 0;
  int sign_1 = s21_get_sign(left), sign_2 = s21_get_sign(right);
  if (!(s21_is_zero(left) && s21_is_zero(right))) {
    if (sign_1 == sign_2) {
      s21_scale_equalize(&left, &right);
      if (left.bits[0] == right.bits[0] && left.bits[1] == right.bits[1] &&
          left.bits[2] == right.bits[2] && left.bits[3] == right.bits[3]) {
        result = 1;
      }
    } else {
      result = 0;
    }
  } else {
    result = 1;
  }
  return result;
}
