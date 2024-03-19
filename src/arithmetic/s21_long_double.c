#include "../s21_decimal.h"

int sum_ldecimal(s21_ldecimal *res, s21_ldecimal add_val) {
  int error_val = 0;
  int bit_to_add_next = 0;

  for (int i = 0; i < 6; i++) {
    int loc_bits = 0;
    for (int j = 0; j < 32; j++) {
      loc_bits = (res->bits[i] >> j & (1)) + (add_val.bits[i] >> j & (1)) +
                 bit_to_add_next;
      bit_to_add_next = 0;
      if (loc_bits == 2) {
        bit_to_add_next = 1;
        loc_bits = 0;
      } else if (loc_bits == 3) {
        bit_to_add_next = 1;
      }

      if (loc_bits == 0) {
        res->bits[i] = res->bits[i] & ~(1 << j);  // set 0 on exact pos
      } else {
        res->bits[i] = res->bits[i] | (1 << j);  // set 1 on exact pos
      }
    }
  }

  if (bit_to_add_next != 0) {
    error_val = 1;
  }

  return error_val;
}

void minus_ldecimal(s21_ldecimal *bigger, s21_ldecimal lower) {
  s21_ldecimal one_last_bit;
  init_ldecimal_zeros(&one_last_bit);
  one_last_bit.bits[0] = one_last_bit.bits[0] | (1);

  for (int i = 0; i < 6; i++) {
    bigger->bits[i] = ~(bigger->bits[i]);
  }

  sum_ldecimal(bigger, one_last_bit);
  sum_ldecimal(&lower, *bigger);

  // отнять 1 бит
  lower = minus_one_bitl(lower);

  // инвертировать
  for (int i = 0; i < 6; i++) {
    lower.bits[i] = ~(lower.bits[i]);
  }

  for (int i = 0; i < 6; i++) {
    bigger->bits[i] = lower.bits[i];
  }
}

s21_ldecimal minus_one_bitl(s21_ldecimal res) {
  int counter = 0;
  int num_bit = 0;

  while ((res.bits[num_bit] >> counter & (1)) == 0 && num_bit < 6) {
    if (counter == 31) {
      num_bit++;
      counter = 0;
    } else {
      counter++;
    }
  }

  if (num_bit < 6) {
    res.bits[num_bit] = res.bits[num_bit] & ~(1 << counter);  // set 0 on exact
                                                              // pos

    while (num_bit != -1) {
      if (counter == 0) {
        num_bit--;
        counter = 32;
      } else {
        counter--;
        res.bits[num_bit] =
            res.bits[num_bit] | (1 << counter);  // set 1 on exact pos
      }
    }
  } else {
    for (int i = 0; i < 6; i++) {
      res.bits[i] = -1;
    }
  }

  return res;
}

int move_bits_leftl(s21_ldecimal *res, int num_move) {
  int error_back = 0;
  int counter = 0;
  int bit_for_next_int = 0;
  int bit_for_next_int_1 = 0;

  while (counter != num_move) {
    counter++;

    for (int i = 0; i < 5; i += 2) {
      bit_for_next_int = (res->bits[i] >> 31) & (1);
      res->bits[i] = res->bits[i] << 1;

      if (bit_for_next_int_1) {
        res->bits[i] = res->bits[i] | (1);
      }

      bit_for_next_int_1 = (res->bits[i + 1] >> 31) & (1);
      res->bits[i + 1] = res->bits[i + 1] << 1;

      if (bit_for_next_int) {
        res->bits[i + 1] = res->bits[i + 1] | (1);
      }
    }

    if (bit_for_next_int_1) {
      error_back = 1;
      break;
    }
  }

  return error_back;
}

int long_devide_by_ten(s21_ldecimal val, s21_ldecimal *res) {
  int local_counter = 0;
  s21_ldecimal ten_devider, ten_devider_l, prev_val, ret_val;

  init_ldecimal_zeros(&ret_val);
  init_ldecimal_zeros(&prev_val);
  init_ldecimal_zeros(&ten_devider_l);
  ten_devider_l.bits[0] = 10;

  while (is_lbigger(val, ten_devider_l) != -1) {
    init_ldecimal_zeros(&ten_devider);
    ten_devider.bits[0] = 10;

    move_bits_leftl(&ten_devider, local_counter);

    if (is_lbigger(ten_devider, val) == 1 || local_counter == 192) {
      minus_ldecimal(&val, prev_val);
      init_ldecimal_zeros(&prev_val);
      prev_val.bits[(local_counter - 1) / 32] =
          prev_val.bits[(local_counter - 1) / 32] |
          (1 << ((local_counter - 1) % 32));
      sum_ldecimal(&ret_val, prev_val);
      local_counter = 0;
    }

    local_counter++;
    prev_val = ten_devider;
  }

  for (int i = 0; i < 6; i++) {
    res->bits[i] = ret_val.bits[i];
  }

  return val.bits[0];
}

int is_lbigger(s21_ldecimal gess_bigger, s21_ldecimal compare_val) {
  int is_bigger = 0;

  for (int i = 5; i >= 0; i--) {
    if ((unsigned int)gess_bigger.bits[i] > (unsigned int)compare_val.bits[i]) {
      is_bigger = 1;
      break;
    } else if ((unsigned int)gess_bigger.bits[i] <
               (unsigned int)compare_val.bits[i]) {
      is_bigger = -1;
      break;
    }
  }

  return is_bigger;
}

void init_ldecimal_zeros(s21_ldecimal *val) {
  for (int i = 0; i < 7; i++) {
    val->bits[i] = 0;
  }
}

int del_normalization(s21_decimal val1, s21_decimal val2,
                      s21_ldecimal *ret_val1, s21_ldecimal *ret_val2) {
  int error_back = 0;
  int diff = scail_len(val1) - scail_len(val2);

  for (int i = 0; i < 3; i++) {
    ret_val1->bits[i] = val1.bits[i];
    ret_val2->bits[i] = val2.bits[i];
  }

  if (diff < 0) {
    while (diff != 0) {
      error_back = multy_long_ten(*ret_val1, ret_val1);
      if (error_back == 1) {
        break;
      }
      diff++;
    }
    ret_val1->bits[6] = 0;
    ret_val2->bits[6] = 0;
  } else {
    ret_val1->bits[6] = diff << 16;
    ret_val2->bits[6] = diff << 16;
  }

  return error_back;
}

int multy_long_ten(s21_ldecimal value, s21_ldecimal *result) {
  int error_back = 0;
  s21_ldecimal loc_val = value;

  error_back = move_bits_leftl(&loc_val, 3);

  if (error_back == 0) {
    for (int i = 0; i < 6; i++) {
      result->bits[i] = loc_val.bits[i];
    }

    loc_val = value;
    error_back = move_bits_leftl(&loc_val, 1);

    if (error_back == 0) {
      error_back = sum_ldecimal(result, loc_val);
    }
  }

  return error_back;
}