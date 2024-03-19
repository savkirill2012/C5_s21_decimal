#include "../s21_decimal.h"

int s21_is_greater(s21_decimal left, s21_decimal right) {  // <
  int result = 0;
  int sign_1 = s21_get_sign(left), sign_2 = s21_get_sign(right);
  if (!(s21_is_zero(left) && s21_is_zero(right))) {
    if (sign_1 != sign_2) {
      if (sign_1 == 0) {
        result = 1;
      } else {
        result = 0;
      }
    } else {
      s21_scale_equalize(&left, &right);
      // normalization_val(&left, &right,
      //                   s21_get_scale(left) - s21_get_scale(right));
      for (int i = 95; i >= 0; i--) {
        int bit_val_1 = s21_get_bit(left, i), bit_val_2 = s21_get_bit(right, i);
        if (bit_val_1 != bit_val_2) {
          if (bit_val_1 != 0) {
            result = (sign_1 == 0) ? 1 : 0;
            break;
          } else {
            result = (sign_1 == 0) ? 0 : 1;
            break;
          }
        }
      }
    }
  }
  return result;
}