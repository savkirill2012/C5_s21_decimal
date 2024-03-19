#include "../s21_decimal.h"

int normalization_val(s21_decimal *val1, s21_decimal *val2, int dif) {
  int error_norm = 0;
  s21_decimal bigger_val, lower_val, one_last_bit;
  int flag_val;

  if (dif < 0) {
    bigger_val = *val1;
    lower_val = *val2;
    flag_val = 1;
    dif = abs(dif);
  } else {
    bigger_val = *val2;
    lower_val = *val1;
    flag_val = 2;
  }

  while (dif) {
    error_norm = multy_ten_logic(bigger_val, &bigger_val);
    if (error_norm == 1) {
      break;
    }
    dif--;
  }

  if (error_norm) {
    int remainder = 0;
    int loc_counter = 0;
    while (dif) {
      if (loc_counter > 5) {
        if (remainder != 0) {
          remainder = 0;
        } else {
          remainder = 1;
        }
        loc_counter = 1;
      }
      int loc_val = devide_ten_logic(lower_val, &lower_val);
      remainder += pow(10, loc_counter) * loc_val;
      loc_counter++;
      dif--;
    }

    if ((unsigned int)(bigger_val.bits[0]) % 2 == 1) {
      if (remainder / (pow(10, loc_counter - 1)) > 4) {
        if (5 * pow(10, loc_counter) != remainder) {
          one_last_bit.bits[0] = 1;
          one_last_bit.bits[1] = 0;
          one_last_bit.bits[2] = 0;
          one_last_bit.bits[3] = 0;
          sum_decimal(&lower_val, one_last_bit);
        }
      }
    }
  }

  if (flag_val == 1) {
    for (int i = 0; i < 3; i++) {
      val1->bits[i] = bigger_val.bits[i];
      val2->bits[i] = lower_val.bits[i];
    }
  } else {
    for (int i = 0; i < 3; i++) {
      val2->bits[i] = bigger_val.bits[i];
      val1->bits[i] = lower_val.bits[i];
    }
  }

  return error_norm;
}

int multy_ten_logic(s21_decimal value, s21_decimal *result) {
  int error_back = 0;
  s21_decimal loc_val = value;

  error_back = move_bits_left(&loc_val, 3);

  if (error_back == 0) {
    for (int i = 0; i < 3; i++) {
      result->bits[i] = loc_val.bits[i];
    }

    loc_val = value;
    error_back = move_bits_left(&loc_val, 1);

    if (error_back == 0) {
      error_back = sum_decimal(result, loc_val);
    }
  }

  return error_back;
}

int devide_ten_logic(s21_decimal val, s21_decimal *res) {
  int local_counter = 0;
  s21_decimal ten_devider, ten_devider_l, prev_val, ret_val;

  init_decimal_zero(&ret_val);
  init_decimal_zero(&prev_val);
  init_decimal_zero(&ten_devider_l);
  ten_devider_l.bits[0] = 10;

  while (is_bigger(val, ten_devider_l) != -1) {
    init_decimal_zero(&ten_devider);
    ten_devider.bits[0] = 10;

    move_bits_left(&ten_devider, local_counter);
    local_counter++;

    if (is_bigger(ten_devider, val) == 1 || local_counter == 96) {
      minus_decimal(&val, prev_val);
      sum_decimal(&ret_val, prev_val);
      local_counter = 0;
    }

    prev_val = ten_devider;
  }

  res->bits[0] = ret_val.bits[0];
  res->bits[1] = ret_val.bits[1];
  res->bits[2] = ret_val.bits[2];

  return val.bits[0];
}

int sum_decimal(s21_decimal *result, s21_decimal loc_val) {
  int error_val = 0;
  int bit_to_add_next = 0;

  for (int i = 0; i < 3; i++) {
    int loc_bits = 0;
    for (int j = 0; j < 32; j++) {
      loc_bits = (result->bits[i] >> j & (1)) + (loc_val.bits[i] >> j & (1)) +
                 bit_to_add_next;
      bit_to_add_next = 0;
      if (loc_bits == 2) {
        bit_to_add_next = 1;
        loc_bits = 0;
      } else if (loc_bits == 3) {
        bit_to_add_next = 1;
      }

      if (loc_bits == 0) {
        result->bits[i] = result->bits[i] & ~(1 << j);  // set 0 on exact pos
      } else {
        result->bits[i] = result->bits[i] | (1 << j);  // set 1 on exact pos
      }
    }
  }

  if (bit_to_add_next != 0) {
    error_val = 1;
  }

  return error_val;
}

int move_bits_left(s21_decimal *val, int times_move) {
  int error_back = 0;
  int counter = 0;
  int bit_for_next_int = 0;
  int bit_for_next_int_1 = 0;

  while (counter != times_move) {
    counter++;
    bit_for_next_int = (val->bits[0] >> 31) & (1);
    val->bits[0] = val->bits[0] << 1;
    bit_for_next_int_1 = (val->bits[1] >> 31) & (1);
    val->bits[1] = val->bits[1] << 1;

    if (bit_for_next_int) {
      val->bits[1] = val->bits[1] | (1);
    }

    bit_for_next_int = (val->bits[2] >> 31) & (1);
    val->bits[2] = val->bits[2] << 1;

    if (bit_for_next_int_1) {
      val->bits[2] = val->bits[2] | (1);
    }

    if (bit_for_next_int) {
      error_back = 1;
      break;
    }
  }

  return error_back;
}

int is_bigger(s21_decimal gess_bigger, s21_decimal compare_val) {
  int is_bigger = 0;

  for (int i = 2; i >= 0; i--) {
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

void init_decimal_zero(s21_decimal *val) {
  for (int i = 0; i < 4; i++) {
    val->bits[i] = 0;
  }
}

void minus_decimal(s21_decimal *bigger, s21_decimal lower) {
  s21_decimal one_last_bit;
  init_decimal_zero(&one_last_bit);
  one_last_bit.bits[0] = one_last_bit.bits[0] | (1);

  for (int i = 0; i < 3; i++) {
    bigger->bits[i] = ~(bigger->bits[i]);
  }

  sum_decimal(bigger, one_last_bit);
  sum_decimal(&lower, *bigger);

  // отнять 1 бит
  lower = minus_one_bit(lower);

  // инвертировать
  for (int i = 0; i < 3; i++) {
    lower.bits[i] = ~(lower.bits[i]);
  }

  bigger->bits[0] = lower.bits[0];
  bigger->bits[1] = lower.bits[1];
  bigger->bits[2] = lower.bits[2];
}

s21_decimal minus_one_bit(s21_decimal res) {
  int counter = 0;
  int num_bit = 0;

  while ((res.bits[num_bit] >> counter & (1)) == 0 && num_bit < 3) {
    if (counter == 31) {
      num_bit++;
      counter = 0;
    } else {
      counter++;
    }
  }

  if (num_bit < 4) {
    res.bits[num_bit] = res.bits[num_bit] & ~(1 << counter);  // set 0 on exact
                                                              // pos

    while (num_bit > -1) {
      if (counter == 0) {
        num_bit--;
        counter = 32;
      } else {
        counter--;
        res.bits[num_bit] =
            res.bits[num_bit] | (1 << counter);  // set 1 on exact pos
      }
    }
  }

  return res;
}

int s21_get_sign(s21_decimal src) { return s21_get_bit(src, S21_SIGN_BIT); }

void s21_zero_decimal(s21_decimal *dst) {
  dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;
}

int s21_get_scale(s21_decimal src) {
  int scale = 0;
  for (int i = S21_FIRST_BIT_SCALE; i < S21_LAST_BIT_SCALE; i++) {
    if (s21_get_bit(src, i + 96)) scale += (1 << (i - S21_FIRST_BIT_SCALE));
  }
  return scale;
}

void s21_set_scale(s21_decimal *dst, int scale) {
  int sign = s21_get_sign(*dst);
  dst->bits[3] = scale << S21_FIRST_BIT_SCALE;
  if (s21_get_sign(*dst) != sign) {
    s21_change_sign(dst);
  }
}

void s21_set_sign(s21_decimal *dst, int sign) {
  s21_set_bit(dst, S21_SIGN_BIT, sign);
}

int s21_get_bit(s21_decimal src, int bit_position) {
  return (src.bits[bit_position / S21_BIT_BOX] &
          (1 << (bit_position % S21_BIT_BOX)))
             ? 1
             : 0;
}

void s21_set_bit(s21_decimal *dst, int bit_position, int check) {
  if (check) {
    dst->bits[bit_position / S21_BIT_BOX] =
        dst->bits[bit_position / S21_BIT_BOX] |
        (1 << (bit_position % S21_BIT_BOX));
  } else {
    dst->bits[bit_position / S21_BIT_BOX] =
        dst->bits[bit_position / S21_BIT_BOX] &
        ~(1 << (bit_position % S21_BIT_BOX));
  }
}