#include "../s21_decimal.h"

#define START_INFO 96

void s21_change_bit(s21_decimal *dst, int bit_position) {
  if (dst->bits[bit_position / S21_BIT_BOX] &
      (1 << (bit_position % S21_BIT_BOX))) {
    dst->bits[bit_position / S21_BIT_BOX] =
        dst->bits[bit_position / S21_BIT_BOX] &
        ~(1 << (bit_position % S21_BIT_BOX));
  } else {
    dst->bits[bit_position / S21_BIT_BOX] =
        dst->bits[bit_position / S21_BIT_BOX] |
        (1 << (bit_position % S21_BIT_BOX));
  }
}

void s21_change_sign(s21_decimal *dst) { s21_change_bit(dst, S21_SIGN_BIT); }

void s21_common_scale(s21_decimal *temp, s21_decimal *helper) {
  if (s21_get_scale(*temp) > s21_get_scale(*helper)) {
    while (s21_get_scale(*temp) - s21_get_scale(*helper)) {
      unsigned int first_overflow = 0;
      unsigned int second_overflow = 0;
      unsigned int third_overflow = 0;
      unsigned long long int first_bits =
          (unsigned long long int)helper->bits[0] * 10;
      if (S21_MAX_UINT <= first_bits) {
        first_overflow = first_bits / S21_MAX_UINT;
      }
      unsigned long long int second_bits =
          (unsigned long long int)helper->bits[1] * 10 + first_overflow;
      if (S21_MAX_UINT <= second_bits) {
        second_overflow = second_bits / S21_MAX_UINT;
      }
      unsigned long long int third_bits =
          (unsigned long long int)helper->bits[2] * 10 + second_overflow;
      if (S21_MAX_UINT <= third_bits) {
        third_overflow = 1;
      }
      if (third_overflow) {
        div_simple(temp, helper);
        break;
      }
      helper->bits[0] = first_bits % S21_MAX_UINT;
      helper->bits[1] = second_bits % S21_MAX_UINT;
      helper->bits[2] = third_bits % S21_MAX_UINT;
      helper->bits[3] += 1U << S21_FIRST_BIT_SCALE;
    }
  } else if (s21_get_scale(*temp) < s21_get_scale(*helper)) {
    s21_common_scale(helper, temp);
  }
}

int find_scale(float src, unsigned int *value) {
  char temp[100];
  sprintf(temp, "%E", fabs(src));
  int scale = (temp[10] - '0') * 10 + (temp[11] - '0');
  if (temp[9] == '+') {
    scale = -scale;
  }
  int j = 0;
  int zeros = 1;
  int count_number = -1;
  for (int i = 7; i >= 0; i--) {
    if (temp[i] == '.')
      continue;
    else if (zeros && temp[i] == '0')
      continue;
    else {
      zeros = 0;
      count_number++;
      *value += (temp[i] - '0') * pow(10, j++);
    }
  }
  scale += count_number;
  return scale;
}

void div_simple(s21_decimal *temp, s21_decimal *helper) {
  unsigned long int div_first = 0;
  unsigned long int div_second = 0;
  while (s21_get_scale(*temp) - s21_get_scale(*helper)) {
    int exp = 0;
    div_second = (temp->bits[2] % 10) * (S21_MAX_UINT);
    div_first = ((temp->bits[1] + div_second) % 10) * (S21_MAX_UINT);
    temp->bits[2] = temp->bits[2] / 10;
    temp->bits[1] = (temp->bits[1] + div_second) / 10;
    temp->bits[0] = (temp->bits[0] + div_first) / 10;
    exp = s21_get_scale(*temp) - 1;
    s21_set_scale(temp, exp);
  }
}

int s21_check_bit(s21_decimal src) {
  int res = 1;
  for (int i = 96; i < 112; i++) {
    if (s21_get_bit(src, i)) {
      res = 0;
    }
  }
  for (int i = 120; i < 127; i++) {
    if (s21_get_bit(src, i)) {
      res = 0;
    }
  }
  if (s21_get_scale(src) < 0 || s21_get_scale(src) > 28) {
    res = 0;
  }
  return res;
}

int s21_from_decimal_to_double(s21_decimal src, long double *dst) {
  long double temp = (double)*dst;
  for (int i = 0; i < 96; i++) {
    temp += s21_get_bit(src, i) * pow(2, i);
  }
  temp = temp * pow(10, -s21_get_scale(src));
  if (s21_get_bit(src, 127)) temp = temp * (-1);
  *dst = temp;
  return 0;
}

// int s21_truncate(s21_decimal value, s21_decimal *result) {
//   s21_zero_decimal(result);
//   float difference = 0;
//   if (s21_get_scale(value)) {
//     long double fl_to_int = 0.0;
//     s21_from_decimal_to_double(value, &fl_to_int);
//     fl_to_int = trunc(fl_to_int);
//     if (fl_to_int < 0.0) {
//       s21_set_bit(result, 127, 1);

//       fl_to_int *= -1;
//     }
//     for (int i = 0; fl_to_int >= 1 && i < START_INFO; i++) {
//       fl_to_int = floor(fl_to_int) / 2;
//       difference = fl_to_int - floor(fl_to_int);
//       if (difference > 0.0) {
//         s21_set_bit(result, i, 1);
//       } else {
//         s21_set_bit(result, i, 0);
//       }
//     }
//     s21_set_scale(result, 0);
//   } else {
//     for (int i = 0; i < 4; ++i) {
//       result->bits[i] = value.bits[i];
//     }
//   }
//   return 0;
// }