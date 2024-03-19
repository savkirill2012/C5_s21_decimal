#include "../s21_decimal.h"

int mul_decimal(s21_decimal *result, s21_decimal val, int scale, int sign) {
  int error_val = 0;
  int loc_scale = scale;

  s21_decimal lower, bigger;
  s21_ldecimal lloc_val, back_val, one_last_bit;

  init_ldecimal_zeros(&back_val);
  init_ldecimal_zeros(&one_last_bit);
  one_last_bit.bits[0] = one_last_bit.bits[0] | 1;

  search_low_and_big_val(*result, val, &lower, &bigger);

  for (int i = 0; i < 3; i++) {
    int counter = 0;
    while (counter < 32) {
      if (lower.bits[i] >> counter & (1)) {
        init_ldecimal_zeros(&lloc_val);
        for (int i = 0; i < 3; i++) {
          lloc_val.bits[i] = bigger.bits[i];
        }
        error_val = move_bits_leftl(&lloc_val, counter + i * 32);
        if (error_val) {
          break;
        }
        error_val = sum_ldecimal(&back_val, lloc_val);
        if (error_val) {
          break;
        }
      }
      counter++;
    }
  }

  if (error_val == 0) {
    int remainder = 0;
    int loc_counter = 0;
    if (!(back_val.bits[3] == 0 && back_val.bits[4] == 0 &&
          back_val.bits[5] == 0)) {
      while (loc_scale != 0 &&
             !(back_val.bits[3] == 0 && back_val.bits[4] == 0 &&
               back_val.bits[5] == 0)) {
        if (loc_counter > 5) {
          if (remainder != 0) {
            remainder = 0;
          } else {
            remainder = 1;
          }
          loc_counter = 1;
        }
        int loc_val = long_devide_by_ten(back_val, &back_val);
        remainder += pow(10, loc_counter) * loc_val;
        loc_scale--;
      }

      if ((unsigned int)(back_val.bits[0]) % 2 == 1) {
        if (remainder / (pow(10, loc_counter - 1)) > 4) {
          if (5 * pow(10, loc_counter) != remainder) {
            sum_ldecimal(&back_val, one_last_bit);
          }
        }
      }

      if (!(back_val.bits[3] == 0 && back_val.bits[4] == 0 &&
            back_val.bits[5] == 0)) {
        error_val = 1;
      } else {
        for (int i = 0; i < 3; i++) {
          result->bits[i] = back_val.bits[i];
        }
      }
    } else {
      for (int i = 0; i < 3; i++) {
        result->bits[i] = back_val.bits[i];
      }
    }
  }

  result->bits[3] = loc_scale << 16;
  if (sign == -1) {
    result->bits[3] = result->bits[3] | (1 << 31);
  }

  return error_val;
}

int search_low_and_big_val(s21_decimal val1, s21_decimal val2,
                           s21_decimal *low_val, s21_decimal *big_val) {
  int is_they_same = 0;

  for (int i = 2; i >= 0; i--) {
    if ((unsigned int)val1.bits[i] > (unsigned int)val2.bits[i]) {
      *big_val = val1;
      *low_val = val2;
      break;
    } else if ((unsigned int)val1.bits[i] < (unsigned int)val2.bits[i]) {
      *big_val = val2;
      *low_val = val1;
      break;
    }
    if (i == 0) {
      *big_val = val1;
      *low_val = val2;
      is_they_same = 1;
    }
  }

  return is_they_same;
}

int scail_len(s21_decimal val) {
  int ret_len = 0;

  for (int i = 0; i < 8; i++) {
    ret_len = ret_len | (((val.bits[3] >> (16 + i)) & (1))
                         << i);  // set exact bit on pos in dec
  }

  return ret_len;
}

int check_if_min_or_max_val(s21_decimal result, int error) {
  int error_back = error;

  if (result.bits[0] == -1 && result.bits[1] == -1 && result.bits[2] == -1 &&
      result.bits[3] == 0) {
    error_back = 1;
  } else if (result.bits[0] == -1 && result.bits[1] == -1 &&
             result.bits[2] == -1 && result.bits[3] == -2147483648) {
    error_back = 2;
  }

  return error_back;
}

void change_sign(s21_decimal *val) {
  if (val->bits[3] & (1 << 31)) {
    val->bits[3] = val->bits[3] & ~(1 << 31);
  } else {
    val->bits[3] = val->bits[3] | (1 << 31);
  }
}

int del_decimal(s21_decimal *result, s21_decimal val, int sign) {
  s21_ldecimal val1, val2, prev_val, ret_val, one_last_bit;
  int local_counter = 0;
  int error_back = 0;

  init_ldecimal_zeros(&ret_val);
  init_ldecimal_zeros(&val1);
  init_ldecimal_zeros(&val2);
  init_ldecimal_zeros(&prev_val);
  init_ldecimal_zeros(&one_last_bit);
  one_last_bit.bits[0] = one_last_bit.bits[0] | 1;

  del_normalization(*result, val, &val1, &val2);

  ret_val.bits[6] = val1.bits[6];

  while (is_lbigger(val1, val2) != -1) {
    s21_ldecimal loc_val = val2;

    move_bits_leftl(&loc_val, local_counter);

    if (is_lbigger(loc_val, val1) == 1 || local_counter == 192) {
      minus_ldecimal(&val1, prev_val);
      init_ldecimal_zeros(&prev_val);
      prev_val.bits[(local_counter - 1) / 32] =
          prev_val.bits[(local_counter - 1) / 32] |
          (1 << ((local_counter - 1) % 32));
      sum_ldecimal(&ret_val, prev_val);
      local_counter = -1;
    }

    local_counter++;
    prev_val = loc_val;
  }

  // Банковское округление
  if (ret_val.bits[0] & (1)) {
    minus_ldecimal(&val2, val1);
    if (is_lbigger(val1, val2) == 1) {
      sum_ldecimal(&ret_val, one_last_bit);
    }
  }

  if (ret_val.bits[3] == 0 && ret_val.bits[4] == 0 && ret_val.bits[5] == 0) {
    for (int i = 0; i < 3; i++) {
      result->bits[i] = ret_val.bits[i];
    }
    result->bits[3] = ret_val.bits[6];
  } else {
    if (!(ret_val.bits[3] == 0 && ret_val.bits[4] == 0 &&
          ret_val.bits[5] == 0)) {
      error_back = 1;
    } else {
      for (int i = 0; i < 3; i++) {
        result->bits[i] = ret_val.bits[i];
      }
      result->bits[3] = ret_val.bits[6];
    }
  }

  if (sign == -1) {
    result->bits[3] = result->bits[3] | (1 << 31);
  } else {
    result->bits[3] = result->bits[3] & ~(1 << 31);
  }

  return error_back;
}