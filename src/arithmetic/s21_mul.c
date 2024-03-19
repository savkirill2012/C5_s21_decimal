#include "../s21_decimal.h"

/*int main() {
    s21_decimal d, c, b;
    int ret_val;

  d.bits[3] = 1048576;
  d.bits[2] = 1005;
  d.bits[1] = 0;
  d.bits[0] = 0;

  c.bits[3] = 0;
  c.bits[2] = 0;
  c.bits[1] = 0;
  c.bits[0] = 200000000;

  ret_val = s21_mul(d, c, &b);

    printf("%d\n", b.bits[3]);
    printf("%d\n", b.bits[2]);
    printf("%d\n", b.bits[1]);
    printf("%d\n", b.bits[0]);

    return 0;
} */

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int scail_len_val1 = scail_len(value_1);
  int scail_len_val2 = scail_len(value_2);
  int sign = 0;

  // unsigned char lower_pow;
  int error_back = 0;

  // add bigger_pow in res
  result->bits[3] = 0;

  if (scail_len_val1 < 29 && scail_len_val2 < 29) {
    if ((value_1.bits[3] & (1 << 31)) != (value_2.bits[3] & (1 << 31))) {
      sign = -1;
    } else {
      sign = 1;
    }

    error_back =
        mul_decimal(&value_1, value_2, scail_len_val1 + scail_len_val2, sign);

    for (int i = 0; i < 4; i++) {
      result->bits[i] = value_1.bits[i];
    }
  } else {
    error_back = 2;
  }

  return error_back;
}