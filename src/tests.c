#include <check.h>
#include <stdlib.h>

#include "s21_decimal.h"

#define SUITE_NAME "Unit"
#define TCASE_NAME "Tests"

START_TEST(s21_add_test) {
  // add with overflow
  s21_decimal d, c, b;
  int ret_val;

  d.bits[3] = 65536;
  d.bits[2] = 0;
  d.bits[1] = 0;
  d.bits[0] = 6;

  c.bits[3] = -2147483648;
  c.bits[2] = -1;
  c.bits[1] = -1;
  c.bits[0] = -1;

  ret_val = s21_add(d, c, &b);

  ck_assert_int_eq(ret_val, 0);
  ck_assert_int_eq(b.bits[0], -2);
  ck_assert_int_eq(b.bits[1], -1);
  ck_assert_int_eq(b.bits[2], -1);
  ck_assert_int_eq(b.bits[3], -2147483648);

  // add with 1 minus val
  d.bits[3] = 65536;
  d.bits[2] = 0;
  d.bits[1] = 0;
  d.bits[0] = 15;

  c.bits[3] = 0;
  c.bits[2] = 0;
  c.bits[1] = 0;
  c.bits[0] = 11;

  ret_val = s21_add(d, c, &b);

  ck_assert_int_eq(ret_val, 0);
  ck_assert_int_eq(b.bits[0], 125);
  ck_assert_int_eq(b.bits[1], 0);
  ck_assert_int_eq(b.bits[2], 0);
  ck_assert_int_eq(b.bits[3], 65536);

  // 0 val
  d.bits[3] = -2147483648;
  d.bits[2] = 5;
  d.bits[1] = 0;
  d.bits[0] = 0;

  c.bits[3] = 0;
  c.bits[2] = 5;
  c.bits[1] = 0;
  c.bits[0] = 0;

  ret_val = s21_add(d, c, &b);

  ck_assert_int_eq(ret_val, 0);
  ck_assert_int_eq(b.bits[0], 0);
  ck_assert_int_eq(b.bits[1], 0);
  ck_assert_int_eq(b.bits[2], 0);
  ck_assert_int_eq(b.bits[3], -2147483648);

  // plus with +1 between bits
  d.bits[3] = 0;
  d.bits[2] = 0;
  d.bits[1] = 1;
  d.bits[0] = 1;

  c.bits[3] = 0;
  c.bits[2] = 0;
  c.bits[1] = -1;
  c.bits[0] = -1;

  ret_val = s21_add(d, c, &b);

  ck_assert_int_eq(ret_val, 0);
  ck_assert_int_eq(b.bits[0], 0);
  ck_assert_int_eq(b.bits[1], 1);
  ck_assert_int_eq(b.bits[2], 1);
  ck_assert_int_eq(b.bits[3], 0);

  // more, then max
  d.bits[3] = 0;
  d.bits[2] = 0;
  d.bits[1] = 0;
  d.bits[0] = 1;

  c.bits[3] = 0;
  c.bits[2] = -1;
  c.bits[1] = -1;
  c.bits[0] = -1;

  ret_val = s21_add(d, c, &b);

  ck_assert_int_eq(ret_val, 1);

  // max val
  d.bits[3] = 0;
  d.bits[2] = 0;
  d.bits[1] = 0;
  d.bits[0] = 1;

  c.bits[3] = 0;
  c.bits[2] = -1;
  c.bits[1] = -1;
  c.bits[0] = -2;

  ret_val = s21_add(d, c, &b);

  ck_assert_int_eq(ret_val, 1);

  // min val
  d.bits[3] = -2147483648;
  d.bits[2] = 0;
  d.bits[1] = 0;
  d.bits[0] = 1;

  c.bits[3] = -2147483648;
  c.bits[2] = -1;
  c.bits[1] = -1;
  c.bits[0] = -2;

  ret_val = s21_add(d, c, &b);

  ck_assert_int_eq(ret_val, 2);

  c.bits[3] = 65536;
  c.bits[2] = 0;
  c.bits[1] = 0;
  c.bits[0] = 6;

  d.bits[3] = -2147483648;
  d.bits[2] = -1;
  d.bits[1] = -1;
  d.bits[0] = -1;

  ret_val = s21_add(d, c, &b);

  ck_assert_int_eq(ret_val, 0);
  ck_assert_int_eq(b.bits[0], -2);
  ck_assert_int_eq(b.bits[1], -1);
  ck_assert_int_eq(b.bits[2], -1);
  ck_assert_int_eq(b.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_sub_test) {
  // simple add with different size
  s21_decimal d, c, b;
  int ret_val;

  d.bits[3] = 131072;
  d.bits[2] = 5;
  d.bits[1] = 0;
  d.bits[0] = 0;

  c.bits[3] = 0;
  c.bits[2] = 5;
  c.bits[1] = 0;
  c.bits[0] = 0;

  ret_val = s21_sub(d, c, &b);

  ck_assert_int_eq(ret_val, 0);
  ck_assert_int_eq(b.bits[0], 0);
  ck_assert_int_eq(b.bits[1], 0);
  ck_assert_int_eq(b.bits[2], 495);
  ck_assert_int_eq(b.bits[3], -2147352576);

  // add with 1 minus val
  d.bits[3] = -2147352576;
  d.bits[2] = 5;
  d.bits[1] = 0;
  d.bits[0] = 0;

  c.bits[3] = 0;
  c.bits[2] = 11;
  c.bits[1] = 0;
  c.bits[0] = 0;

  ret_val = s21_sub(d, c, &b);

  ck_assert_int_eq(ret_val, 0);
  ck_assert_int_eq(b.bits[0], 0);
  ck_assert_int_eq(b.bits[1], 0);
  ck_assert_int_eq(b.bits[2], 1105);
  ck_assert_int_eq(b.bits[3], -2147352576);

  // 0 val
  d.bits[3] = -2147483648;
  d.bits[2] = 5;
  d.bits[1] = 0;
  d.bits[0] = 0;

  c.bits[3] = -2147483648;
  c.bits[2] = 5;
  c.bits[1] = 0;
  c.bits[0] = 0;

  ret_val = s21_sub(d, c, &b);

  ck_assert_int_eq(ret_val, 0);
  ck_assert_int_eq(b.bits[0], 0);
  ck_assert_int_eq(b.bits[1], 0);
  ck_assert_int_eq(b.bits[2], 0);
  ck_assert_int_eq(b.bits[3], -2147483648);

  // plus with +1 between bits
  d.bits[3] = 0;
  d.bits[2] = 1;
  d.bits[1] = 1;
  d.bits[0] = 0;

  c.bits[3] = 0;
  c.bits[2] = -1;
  c.bits[1] = -1;
  c.bits[0] = 0;

  ret_val = s21_sub(d, c, &b);

  ck_assert_int_eq(ret_val, 0);
  ck_assert_int_eq(b.bits[0], 0);
  ck_assert_int_eq(b.bits[1], -2);
  ck_assert_int_eq(b.bits[2], -2);
  ck_assert_int_eq(b.bits[3], -2147483648);

  // more, then max
  d.bits[3] = 0;
  d.bits[2] = 1;
  d.bits[1] = 0;
  d.bits[0] = 0;

  c.bits[3] = -2147483648;
  c.bits[2] = -1;
  c.bits[1] = -1;
  c.bits[0] = -1;

  ret_val = s21_sub(d, c, &b);

  ck_assert_int_eq(ret_val, 1);

  // max val
  d.bits[3] = 0;
  d.bits[2] = 1;
  d.bits[1] = 0;
  d.bits[0] = 0;

  c.bits[3] = -2147483648;
  c.bits[2] = -2;
  c.bits[1] = -1;
  c.bits[0] = -1;

  ret_val = s21_sub(d, c, &b);

  ck_assert_int_eq(ret_val, 1);

  // min val
  d.bits[3] = -2147483648;
  d.bits[2] = 1;
  d.bits[1] = 0;
  d.bits[0] = 0;

  c.bits[3] = 0;
  c.bits[2] = -2;
  c.bits[1] = -1;
  c.bits[0] = -1;

  ret_val = s21_sub(d, c, &b);

  ck_assert_int_eq(ret_val, 2);

  // lower then min val
  d.bits[3] = -2147483648;
  d.bits[2] = 6;
  d.bits[1] = 0;
  d.bits[0] = 0;

  c.bits[3] = 0;
  c.bits[2] = -1;
  c.bits[1] = -1;
  c.bits[0] = -1;

  ret_val = s21_sub(d, c, &b);

  ck_assert_int_eq(ret_val, 2);

  d.bits[3] = 0;
  d.bits[2] = 5;
  d.bits[1] = 0;
  d.bits[0] = 0;

  c.bits[3] = -2147352576;
  c.bits[2] = 5;
  c.bits[1] = 0;
  c.bits[0] = 0;

  ret_val = s21_sub(d, c, &b);

  ck_assert_int_eq(ret_val, 0);
  ck_assert_int_eq(b.bits[0], 0);
  ck_assert_int_eq(b.bits[1], 0);
  ck_assert_int_eq(b.bits[2], 505);
  ck_assert_int_eq(b.bits[3], 131072);
}
END_TEST

START_TEST(s21_mul_test) {
  s21_decimal d, c, b;
  int ret_val;

  // simple mul
  d.bits[3] = 524288;
  d.bits[2] = 10000;
  d.bits[1] = 0;
  d.bits[0] = 0;

  c.bits[3] = 262144;
  c.bits[2] = 0;
  c.bits[1] = 4;
  c.bits[0] = 0;

  ret_val = s21_mul(d, c, &b);

  ck_assert_int_eq(ret_val, 0);
  ck_assert_int_eq(b.bits[3], 458752);
  ck_assert_int_eq(b.bits[2], 1717986918);
  ck_assert_int_eq(b.bits[1], 1717986918);
  ck_assert_int_eq(b.bits[0], 1717986918);

  // simple mul
  d.bits[3] = 0;
  d.bits[2] = 0;
  d.bits[1] = 0;
  d.bits[0] = 1;

  c.bits[3] = 0;
  c.bits[2] = 12;
  c.bits[1] = 3;
  c.bits[0] = 1;

  ret_val = s21_mul(d, c, &b);

  ck_assert_int_eq(ret_val, 0);
  ck_assert_int_eq(b.bits[3], 0);
  ck_assert_int_eq(b.bits[2], 12);
  ck_assert_int_eq(b.bits[1], 3);
  ck_assert_int_eq(b.bits[0], 1);

  // simple mul
  d.bits[3] = 0;
  d.bits[2] = 0;
  d.bits[1] = 0;
  d.bits[0] = 2;

  c.bits[3] = 0;
  c.bits[2] = 0;
  c.bits[1] = 3;
  c.bits[0] = 0;

  ret_val = s21_mul(d, c, &b);

  ck_assert_int_eq(ret_val, 0);
  ck_assert_int_eq(b.bits[3], 0);
  ck_assert_int_eq(b.bits[2], 0);
  ck_assert_int_eq(b.bits[1], 6);
  ck_assert_int_eq(b.bits[0], 0);

  // simple mul
  d.bits[3] = 0;
  d.bits[2] = 0;
  d.bits[1] = 0;
  d.bits[0] = 0;

  c.bits[3] = -2147483648;
  c.bits[2] = 0;
  c.bits[1] = 0;
  c.bits[0] = 0;

  ret_val = s21_mul(d, c, &b);

  ck_assert_int_eq(ret_val, 0);
  ck_assert_int_eq(b.bits[3], -2147483648);
  ck_assert_int_eq(b.bits[2], 0);
  ck_assert_int_eq(b.bits[1], 0);
  ck_assert_int_eq(b.bits[0], 0);

  // simple mul
  d.bits[3] = 0;
  d.bits[2] = 0;
  d.bits[1] = 0;
  d.bits[0] = 0;

  c.bits[3] = -2147483648;
  c.bits[2] = 0;
  c.bits[1] = 0;
  c.bits[0] = 10000;

  ret_val = s21_mul(d, c, &b);

  ck_assert_int_eq(ret_val, 0);
  ck_assert_int_eq(b.bits[3], -2147483648);
  ck_assert_int_eq(b.bits[2], 0);
  ck_assert_int_eq(b.bits[1], 0);
  ck_assert_int_eq(b.bits[0], 0);

  // simple mul
  d.bits[3] = -2147483648;
  d.bits[2] = 6;
  d.bits[1] = 5;
  d.bits[0] = 3;

  c.bits[3] = -2147483648;
  c.bits[2] = 0;
  c.bits[1] = 0;
  c.bits[0] = 10000;

  ret_val = s21_mul(d, c, &b);

  ck_assert_int_eq(ret_val, 0);
  ck_assert_int_eq(b.bits[3], 0);
  ck_assert_int_eq(b.bits[2], 60000);
  ck_assert_int_eq(b.bits[1], 50000);
  ck_assert_int_eq(b.bits[0], 30000);

  // check sign
  d.bits[3] = -2147483648;
  d.bits[2] = 6;
  d.bits[1] = 5;
  d.bits[0] = 3;

  c.bits[3] = 0;
  c.bits[2] = 0;
  c.bits[1] = 0;
  c.bits[0] = 10000;

  ret_val = s21_mul(d, c, &b);

  ck_assert_int_eq(ret_val, 0);
  ck_assert_int_eq(b.bits[3], -2147483648);
  ck_assert_int_eq(b.bits[2], 60000);
  ck_assert_int_eq(b.bits[1], 50000);
  ck_assert_int_eq(b.bits[0], 30000);

  // mul with round
  d.bits[3] = 524228;
  d.bits[2] = 5;
  d.bits[1] = 0;
  d.bits[0] = 0;

  c.bits[3] = 0;
  c.bits[2] = 0;
  c.bits[1] = 0;
  c.bits[0] = 200000000;

  ret_val = s21_mul(d, c, &b);

  ck_assert_int_eq(ret_val, 0);
  ck_assert_int_eq(b.bits[3], 458752);
  ck_assert_int_eq(b.bits[2], 1000000000);
  ck_assert_int_eq(b.bits[1], 0);
  ck_assert_int_eq(b.bits[0], 0);
}
END_TEST

START_TEST(s21_dev_test) {
  s21_decimal d, c, b;
  int ret_val;

  d.bits[3] = 0;
  d.bits[2] = 0;
  d.bits[1] = 10;
  d.bits[0] = 0;

  c.bits[3] = 0;
  c.bits[2] = 0;
  c.bits[1] = 0;
  c.bits[0] = 5;

  ret_val = s21_div(d, c, &b);

  ck_assert_int_eq(ret_val, 0);
  ck_assert_int_eq(b.bits[3], 0);
  ck_assert_int_eq(b.bits[2], 0);
  ck_assert_int_eq(b.bits[1], 2);
  ck_assert_int_eq(b.bits[0], 0);

  // dev 0
  d.bits[3] = 0;
  d.bits[2] = 0;
  d.bits[1] = 10;
  d.bits[0] = 0;

  c.bits[3] = 0;
  c.bits[2] = 0;
  c.bits[1] = 0;
  c.bits[0] = 0;

  ret_val = s21_div(d, c, &b);

  ck_assert_int_eq(ret_val, 3);

  // test sign
  d.bits[3] = 0;
  d.bits[2] = 0;
  d.bits[1] = 10;
  d.bits[0] = 0;

  c.bits[3] = -2147483648;
  c.bits[2] = 0;
  c.bits[1] = 0;
  c.bits[0] = 2;

  ret_val = s21_div(d, c, &b);

  ck_assert_int_eq(ret_val, 0);
  ck_assert_int_eq(b.bits[3], -2147483648);
  ck_assert_int_eq(b.bits[2], 0);
  ck_assert_int_eq(b.bits[1], 5);
  ck_assert_int_eq(b.bits[0], 0);

  // test scale
  d.bits[3] = 65536;
  d.bits[2] = 0;
  d.bits[1] = 10;
  d.bits[0] = 0;

  c.bits[3] = 0;
  c.bits[2] = 0;
  c.bits[1] = 0;
  c.bits[0] = 2;

  ret_val = s21_div(d, c, &b);

  ck_assert_int_eq(ret_val, 0);
  ck_assert_int_eq(b.bits[3], 65536);
  ck_assert_int_eq(b.bits[2], 0);
  ck_assert_int_eq(b.bits[1], 5);
  ck_assert_int_eq(b.bits[0], 0);

  d.bits[3] = 0;
  d.bits[2] = 0;
  d.bits[1] = 10;
  d.bits[0] = 0;

  c.bits[3] = 65536;
  c.bits[2] = 0;
  c.bits[1] = 0;
  c.bits[0] = 2;

  ret_val = s21_div(d, c, &b);

  ck_assert_int_eq(ret_val, 0);
  ck_assert_int_eq(b.bits[3], 0);
  ck_assert_int_eq(b.bits[2], 0);
  ck_assert_int_eq(b.bits[1], 50);
  ck_assert_int_eq(b.bits[0], 0);

  // owerflow
  d.bits[3] = 0;
  d.bits[2] = 100;
  d.bits[1] = 0;
  d.bits[0] = 0;

  c.bits[3] = 524288;
  c.bits[2] = 0;
  c.bits[1] = 0;
  c.bits[0] = 4;

  ret_val = s21_div(d, c, &b);

  ck_assert_int_eq(ret_val, 0);
  ck_assert_int_eq(b.bits[3], 0);
  ck_assert_int_eq(b.bits[2], -1794967296);
  ck_assert_int_eq(b.bits[1], 0);
  ck_assert_int_eq(b.bits[0], 0);

  //
  d.bits[3] = 131072;
  d.bits[2] = 21111111;
  d.bits[1] = -1;
  d.bits[0] = -1;

  c.bits[3] = 0;
  c.bits[2] = 3;
  c.bits[1] = 0;
  c.bits[0] = 300;

  ret_val = s21_div(d, c, &b);

  ck_assert_int_eq(ret_val, 0);
  ck_assert_int_eq(b.bits[3], 131072);
  ck_assert_int_eq(b.bits[2], 0);
  ck_assert_int_eq(b.bits[1], 0);
  ck_assert_int_eq(b.bits[0], 7037037);

  //
  d.bits[3] = 0;
  d.bits[2] = -1;
  d.bits[1] = -1;
  d.bits[0] = -1;

  c.bits[3] = 131072;
  c.bits[2] = 0;
  c.bits[1] = 0;
  c.bits[0] = 3;

  ret_val = s21_div(d, c, &b);

  ck_assert_int_eq(ret_val, 1);
}
END_TEST

START_TEST(test_s21_is_greater) {
  s21_decimal a1, a2;
  // 1337 > 1338 == 0 no
  a1.bits[3] = 0;
  a1.bits[2] = 0;
  a1.bits[1] = 0;
  a1.bits[0] = 0x539;

  a2.bits[3] = 0;
  a2.bits[2] = 0;
  a2.bits[1] = 0;
  a2.bits[0] = 0x53A;
  ck_assert_int_eq(s21_is_greater(a1, a2), 0);

  // -1337 > 1338 == 0 no
  a1.bits[3] = 0x80000000;
  a1.bits[2] = 0;
  a1.bits[1] = 0;
  a1.bits[0] = 0x539;

  a2.bits[3] = 0;
  a2.bits[2] = 0;
  a2.bits[1] = 0;
  a2.bits[0] = 0x53A;
  ck_assert_int_eq(s21_is_greater(a1, a2), 0);

  // 1337 > -1338 == 1 yes
  a1.bits[3] = 0;
  a1.bits[2] = 0;
  a1.bits[1] = 0;
  a1.bits[0] = 0x539;

  a2.bits[3] = 0x80000000;
  a2.bits[2] = 0;
  a2.bits[1] = 0;
  a2.bits[0] = 0x53A;
  ck_assert_int_eq(s21_is_greater(a1, a2), 1);

  // -1337 > -1338 == 1 yes
  a1.bits[3] = 0x80000000;
  a1.bits[2] = 0;
  a1.bits[1] = 0;
  a1.bits[0] = 0x539;

  a2.bits[3] = 0x80000000;
  a2.bits[2] = 0;
  a2.bits[1] = 0;
  a2.bits[0] = 0x53A;
  ck_assert_int_eq(s21_is_greater(a1, a2), 1);

  // -13.37 > -1338 == 1 yes
  a1.bits[3] = 0x80020000;
  a1.bits[2] = 0;
  a1.bits[1] = 0;
  a1.bits[0] = 0x539;

  a2.bits[3] = 0x80000000;
  a2.bits[2] = 0;
  a2.bits[1] = 0;
  a2.bits[0] = 0x53A;
  ck_assert_int_eq(s21_is_greater(a1, a2), 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal) {
  s21_decimal a1, a2;
  // 1337 >= 1338 == 0 no
  a1.bits[3] = 0;
  a1.bits[2] = 0;
  a1.bits[1] = 0;
  a1.bits[0] = 0x539;

  a2.bits[3] = 0;
  a2.bits[2] = 0;
  a2.bits[1] = 0;
  a2.bits[0] = 0x53A;
  ck_assert_int_eq(s21_is_greater_or_equal(a1, a2), 0);

  // 1338 >= 1337 == 1 yes
  a1.bits[3] = 0;
  a1.bits[2] = 0;
  a1.bits[1] = 0;
  a1.bits[0] = 0x53A;

  a2.bits[3] = 0;
  a2.bits[2] = 0;
  a2.bits[1] = 0;
  a2.bits[0] = 0x539;

  ck_assert_int_eq(s21_is_greater_or_equal(a1, a2), 1);

  // 1337 >= 1337 == 1 yes
  a1.bits[3] = 0;
  a1.bits[2] = 0;
  a1.bits[1] = 0;
  a1.bits[0] = 0x539;

  a2.bits[3] = 0;
  a2.bits[2] = 0;
  a2.bits[1] = 0;
  a2.bits[0] = 0x539;
  ck_assert_int_eq(s21_is_greater_or_equal(a1, a2), 1);
}
END_TEST

START_TEST(test_s21_is_equal) {
  s21_decimal a1, a2;
  // 1337 = 1337 == 1 yes
  a1.bits[3] = 0;
  a1.bits[2] = 0;
  a1.bits[1] = 0;
  a1.bits[0] = 0x539;

  a2.bits[3] = 0;
  a2.bits[2] = 0;
  a2.bits[1] = 0;
  a2.bits[0] = 0x539;
  ck_assert_int_eq(s21_is_equal(a1, a2), 1);

  // 1337 = 1338 == 0 no
  a1.bits[3] = 0;
  a1.bits[2] = 0;
  a1.bits[1] = 0;
  a1.bits[0] = 0x539;

  a2.bits[3] = 0;
  a2.bits[2] = 0;
  a2.bits[1] = 0;
  a2.bits[0] = 0x53A;
  ck_assert_int_eq(s21_is_equal(a1, a2), 0);

  // 1337 = 1338 == 0 no
  a1.bits[3] = 0;
  a1.bits[2] = 0;
  a1.bits[1] = 0;
  a1.bits[0] = 0x539;

  a2.bits[3] = 0;
  a2.bits[2] = 0;
  a2.bits[1] = 0;
  a2.bits[0] = 0x53A;
  ck_assert_int_eq(s21_is_equal(a1, a2), 0);

  // 1337 = - 1338 == 0 no
  a1.bits[3] = 0;
  a1.bits[2] = 0;
  a1.bits[1] = 0;
  a1.bits[0] = 0x539;

  a2.bits[3] = 0x80000000;
  a2.bits[2] = 0;
  a2.bits[1] = 0;
  a2.bits[0] = 0x53A;
  ck_assert_int_eq(s21_is_equal(a1, a2), 0);

  // - 1337 = - 1338 == 0 no
  a1.bits[3] = 0x80000000;
  a1.bits[2] = 0;
  a1.bits[1] = 0;
  a1.bits[0] = 0x539;

  a2.bits[3] = 0x80000000;
  a2.bits[2] = 0;
  a2.bits[1] = 0;
  a2.bits[0] = 0x53A;
  ck_assert_int_eq(s21_is_equal(a1, a2), 0);
}
END_TEST

START_TEST(test_s21_is_not_equal) {
  s21_decimal a1, a2;
  // 1337 != 1338 == 1 yes
  a1.bits[3] = 0;
  a1.bits[2] = 0;
  a1.bits[1] = 0;
  a1.bits[0] = 0x539;

  a2.bits[3] = 0;
  a2.bits[2] = 0;
  a2.bits[1] = 0;
  a2.bits[0] = 0x53A;
  ck_assert_int_eq(s21_is_not_equal(a1, a2), 1);

  // 1337 != 1337 == 0 no
  a1.bits[3] = 0;
  a1.bits[2] = 0;
  a1.bits[1] = 0;
  a1.bits[0] = 0x539;

  a2.bits[3] = 0;
  a2.bits[2] = 0;
  a2.bits[1] = 0;
  a2.bits[0] = 0x539;
  ck_assert_int_eq(s21_is_not_equal(a1, a2), 0);
}
END_TEST

START_TEST(test_s21_is_less) {
  s21_decimal a1, a2;
  // 1337 < 1338 == 1 yes
  a1.bits[3] = 0;
  a1.bits[2] = 0;
  a1.bits[1] = 0;
  a1.bits[0] = 0x539;

  a2.bits[3] = 0;
  a2.bits[2] = 0;
  a2.bits[1] = 0;
  a2.bits[0] = 0x53A;
  ck_assert_int_eq(s21_is_less(a1, a2), 1);

  // 1338 < 1337 == 1 no
  a1.bits[3] = 0;
  a1.bits[2] = 0;
  a1.bits[1] = 0;
  a1.bits[0] = 0x53A;

  a2.bits[3] = 0;
  a2.bits[2] = 0;
  a2.bits[1] = 0;
  a2.bits[0] = 0x539;
  ck_assert_int_eq(s21_is_less(a1, a2), 0);

  // -1337 < 1338 == 1 yes
  a1.bits[3] = 0x80000000;
  a1.bits[2] = 0;
  a1.bits[1] = 0;
  a1.bits[0] = 0x539;

  a2.bits[3] = 0;
  a2.bits[2] = 0;
  a2.bits[1] = 0;
  a2.bits[0] = 0x53A;
  ck_assert_int_eq(s21_is_less(a1, a2), 1);

  // 1337 < -1338 == 0 no
  a1.bits[3] = 0;
  a1.bits[2] = 0;
  a1.bits[1] = 0;
  a1.bits[0] = 0x539;

  a2.bits[3] = 0x80000000;
  a2.bits[2] = 0;
  a2.bits[1] = 0;
  a2.bits[0] = 0x53A;

  ck_assert_int_eq(s21_is_less(a1, a2), 0);

  // -1337 < -1338 == 0 no
  a1.bits[3] = 0x80000000;
  a1.bits[2] = 0;
  a1.bits[1] = 0;
  a1.bits[0] = 0x539;

  a2.bits[3] = 0x80000000;
  a2.bits[2] = 0;
  a2.bits[1] = 0;
  a2.bits[0] = 0x53A;
  ck_assert_int_eq(s21_is_less(a1, a2), 0);

  // 8307676162671600317.2929608408368441 < 1338 == 0 no
  a1.bits[3] = 0x00100000;  // 0000 0000 0001 0000 0000 0000 0000 0000
  a1.bits[2] = 0x266B4F0E;  // 0010 0110 0110 1011 0100 1111 0000 1110
  a1.bits[1] = 0;
  a1.bits[0] = 0x539;  // 0000 0000 0000 0000 0000 0010 0001 1011

  a2.bits[3] = 0;      // 0000 0000 0000 0000 0000 0000 0000 0000
  a2.bits[2] = 0;      //
  a2.bits[1] = 0;      //
  a2.bits[0] = 0x53A;  // 0000 0000 0000 0000 0000 0101 0011 1010
  ck_assert_int_eq(s21_is_less(a1, a2), 0);
}
END_TEST

START_TEST(test_s21_is_less_or_equal) {
  s21_decimal a1, a2;
  // 1337 <= 1338 == 1 yes
  a1.bits[3] = 0;
  a1.bits[2] = 0;
  a1.bits[1] = 0;
  a1.bits[0] = 0x539;

  a2.bits[3] = 0;
  a2.bits[2] = 0;
  a2.bits[1] = 0;
  a2.bits[0] = 0x53A;
  ck_assert_int_eq(s21_is_less_or_equal(a1, a2), 1);

  // 1338 <= 1337 == 0 no
  a1.bits[3] = 0;
  a1.bits[2] = 0;
  a1.bits[1] = 0;
  a1.bits[0] = 0x53A;

  a2.bits[3] = 0;
  a2.bits[2] = 0;
  a2.bits[1] = 0;
  a2.bits[0] = 0x539;
  ck_assert_int_eq(s21_is_less_or_equal(a1, a2), 0);

  // 1337 <= 1337 == 1 yes
  a1.bits[3] = 0;
  a1.bits[2] = 0;
  a1.bits[1] = 0;
  a1.bits[0] = 0x539;

  a2.bits[3] = 0;
  a2.bits[2] = 0;
  a2.bits[1] = 0;
  a2.bits[0] = 0x539;
  ck_assert_int_eq(s21_is_less_or_equal(a1, a2), 1);
}
END_TEST

START_TEST(test_int_to_decimal) {
  // test case 1
  int src = -2147483648;  // минимальный int
  s21_decimal dst[4];
  dst->bits[0] = 0x80000000;
  dst->bits[1] = 0x00000000;
  dst->bits[2] = 0x00000000;
  dst->bits[3] = 0x80000000;
  s21_decimal temp;
  init_decimal_zero(&temp);
  int res = s21_from_int_to_decimal(src, &temp);
  ck_assert_int_eq(temp.bits[0], dst->bits[0]);
  ck_assert_int_eq(temp.bits[1], dst->bits[1]);
  ck_assert_int_eq(temp.bits[2], dst->bits[2]);
  ck_assert_int_eq(temp.bits[3], dst->bits[3]);
  ck_assert_int_eq(res, 0);

  // test case 2
  src = 2147483647;  // максимальный int
  dst->bits[0] = 0x7FFFFFFF;
  dst->bits[1] = 0x00000000;
  dst->bits[2] = 0x00000000;
  dst->bits[3] = 0x00000000;
  init_decimal_zero(&temp);
  res = s21_from_int_to_decimal(src, &temp);
  ck_assert_int_eq(temp.bits[0], dst->bits[0]);
  ck_assert_int_eq(temp.bits[1], dst->bits[1]);
  ck_assert_int_eq(temp.bits[2], dst->bits[2]);
  ck_assert_int_eq(temp.bits[3], dst->bits[3]);
  ck_assert_int_eq(res, 0);

  // test case 3
  src = 0;
  dst->bits[0] = 0x00000000;
  dst->bits[1] = 0x00000000;
  dst->bits[2] = 0x00000000;
  dst->bits[3] = 0x00000000;
  init_decimal_zero(&temp);
  res = s21_from_int_to_decimal(src, &temp);
  ck_assert_int_eq(temp.bits[0], dst->bits[0]);
  ck_assert_int_eq(temp.bits[1], dst->bits[1]);
  ck_assert_int_eq(temp.bits[2], dst->bits[2]);
  ck_assert_int_eq(temp.bits[3], dst->bits[3]);
  ck_assert_int_eq(res, 0);

  // test case 4
  src = 5;
  dst->bits[0] = 0x00000005;
  dst->bits[1] = 0x00000000;
  dst->bits[2] = 0x00000000;
  dst->bits[3] = 0x00000000;
  init_decimal_zero(&temp);
  res = s21_from_int_to_decimal(src, &temp);
  ck_assert_int_eq(temp.bits[0], dst->bits[0]);
  ck_assert_int_eq(temp.bits[1], dst->bits[1]);
  ck_assert_int_eq(temp.bits[2], dst->bits[2]);
  ck_assert_int_eq(temp.bits[3], dst->bits[3]);
  ck_assert_int_eq(res, 0);

  // test case 5
  src = -5;
  dst->bits[0] = 0x00000005;
  dst->bits[1] = 0x00000000;
  dst->bits[2] = 0x00000000;
  dst->bits[3] = 0x80000000;
  init_decimal_zero(&temp);
  res = s21_from_int_to_decimal(src, &temp);
  ck_assert_int_eq(temp.bits[0], dst->bits[0]);
  ck_assert_int_eq(temp.bits[1], dst->bits[1]);
  ck_assert_int_eq(temp.bits[2], dst->bits[2]);
  ck_assert_int_eq(temp.bits[3], dst->bits[3]);
  ck_assert_int_eq(res, 0);

  // test case 6
  src = 123;
  s21_decimal *dst_1 = NULL;
  res = s21_from_int_to_decimal(src, dst_1);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_float_to_decimal) {
  // test case 1
  float src = 0.0;
  s21_decimal dst[4];
  dst->bits[0] = 0x00000000;
  dst->bits[1] = 0x00000000;
  dst->bits[2] = 0x00000000;
  dst->bits[3] = 0x00000000;
  s21_decimal temp;
  init_decimal_zero(&temp);
  int res = s21_from_float_to_decimal(src, &temp);
  ck_assert_int_eq(temp.bits[0], dst->bits[0]);
  ck_assert_int_eq(temp.bits[1], dst->bits[1]);
  ck_assert_int_eq(temp.bits[2], dst->bits[2]);
  ck_assert_int_eq(temp.bits[3], dst->bits[3]);
  ck_assert_int_eq(res, 0);

  // test case 2
  src = 1E-28f;
  dst->bits[0] = 0x00000001;
  dst->bits[1] = 0x00000000;
  dst->bits[2] = 0x00000000;
  dst->bits[3] = 0x001C0000;
  init_decimal_zero(&temp);
  res = s21_from_float_to_decimal(src, &temp);
  ck_assert_int_eq(temp.bits[0], dst->bits[0]);
  ck_assert_int_eq(temp.bits[1], dst->bits[1]);
  ck_assert_int_eq(temp.bits[2], dst->bits[2]);
  ck_assert_int_eq(temp.bits[3], dst->bits[3]);
  ck_assert_int_eq(res, 0);

  // //test case 3
  // src = 70172132300000000000000000000.f;
  // dst->bits[0] = 0xA9400000;
  // dst->bits[1] = 0xB25EFECA;
  // dst->bits[2] = 0xE2BD0685;
  // dst->bits[3] = 0x00000000;
  // init_decimal_zero(&temp);
  // res = s21_from_float_to_decimal(src, &temp);
  // ck_assert_int_eq(temp.bits[0], dst->bits[0]);
  // ck_assert_int_eq(temp.bits[1], dst->bits[1]);
  // ck_assert_int_eq(temp.bits[2], dst->bits[2]);
  // ck_assert_int_eq(temp.bits[3], dst->bits[3]);
  // ck_assert_int_eq(res, 0);

  // test case 4
  src = -17453.f;
  dst->bits[0] = 0x0000442D;
  dst->bits[1] = 0x00000000;
  dst->bits[2] = 0x00000000;
  dst->bits[3] = 0x80000000;
  init_decimal_zero(&temp);
  res = s21_from_float_to_decimal(src, &temp);
  ck_assert_int_eq(temp.bits[0], dst->bits[0]);
  ck_assert_int_eq(temp.bits[1], dst->bits[1]);
  ck_assert_int_eq(temp.bits[2], dst->bits[2]);
  ck_assert_int_eq(temp.bits[3], dst->bits[3]);
  ck_assert_int_eq(res, 0);

  // test case 5
  src = 0.0000733;
  dst->bits[0] = 0x000002DD;
  dst->bits[1] = 0x00000000;
  dst->bits[2] = 0x00000000;
  dst->bits[3] = 0x00070000;
  init_decimal_zero(&temp);
  res = s21_from_float_to_decimal(src, &temp);
  ck_assert_int_eq(temp.bits[0], dst->bits[0]);
  ck_assert_int_eq(temp.bits[1], dst->bits[1]);
  ck_assert_int_eq(temp.bits[2], dst->bits[2]);
  ck_assert_int_eq(temp.bits[3], dst->bits[3]);
  ck_assert_int_eq(res, 0);

  // test case 6
  src = nan("");
  init_decimal_zero(&temp);
  res = s21_from_float_to_decimal(src, &temp);
  ck_assert_int_eq(res, 1);

  // test case 7
  src = INFINITY;
  init_decimal_zero(&temp);
  res = s21_from_float_to_decimal(src, &temp);
  ck_assert_int_eq(res, 1);

  // test case 8
  src = -INFINITY;
  init_decimal_zero(&temp);
  res = s21_from_float_to_decimal(src, &temp);
  ck_assert_int_eq(res, 1);

  // test case 9
  src = 1.999E-27f;
  dst->bits[0] = 0x00000013;
  dst->bits[1] = 0x00000000;
  dst->bits[2] = 0x00000000;
  dst->bits[3] = 0x001C0000;
  init_decimal_zero(&temp);
  res = s21_from_float_to_decimal(src, &temp);
  ck_assert_int_eq(temp.bits[0], dst->bits[0]);
  ck_assert_int_eq(temp.bits[1], dst->bits[1]);
  ck_assert_int_eq(temp.bits[2], dst->bits[2]);
  ck_assert_int_eq(temp.bits[3], dst->bits[3]);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_decimal_to_float) {
  // test case 1
  s21_decimal src[4];
  src->bits[0] = 0xFFFFFFFF;
  src->bits[1] = 0xFFFFFFFF;
  src->bits[2] = 0xFFFFFFFF;
  src->bits[3] = 0x00000000;
  float dst = 79228162500000000000000000000.f;
  float tmp;
  int res = s21_from_decimal_to_float(*src, &tmp);
  ck_assert_float_eq(tmp, dst);
  ck_assert_int_eq(res, 0);

  // test case 2
  src->bits[0] = 0xFFFFFFFF;
  src->bits[1] = 0xFFFFFFFF;
  src->bits[2] = 0xFFFFFFFF;
  src->bits[3] = 0x80000000;
  dst = -79228162500000000000000000000.f;
  res = s21_from_decimal_to_float(*src, &tmp);
  ck_assert_float_eq(tmp, dst);
  ck_assert_int_eq(res, 0);

  // test case 3
  src->bits[0] = 0x00000000;
  src->bits[1] = 0x00000000;
  src->bits[2] = 0x00000000;
  src->bits[3] = 0x00000000;
  dst = 0.f;
  res = s21_from_decimal_to_float(*src, &tmp);
  ck_assert_float_eq(tmp, dst);
  ck_assert_int_eq(res, 0);

  // test case 4
  src->bits[0] = 0xFFFFFFFF;
  src->bits[1] = 0xFFFFFFFF;
  src->bits[2] = 0xFFFFFFFF;
  src->bits[3] = 0xFFFFFFFF;
  res = s21_from_decimal_to_float(*src, &tmp);
  ck_assert_int_eq(res, 1);

  // test case 5
  src->bits[0] = 0xFFFFFFFF;
  src->bits[1] = 0xFFFFFFFF;
  src->bits[2] = 0xFFFFFFFF;
  src->bits[3] = 0x7FFFFFFF;
  res = s21_from_decimal_to_float(*src, &tmp);
  ck_assert_int_eq(res, 1);

  // test case 6
  src->bits[0] = 0x00000002;
  src->bits[1] = 0x00000000;
  src->bits[2] = 0x00000000;
  src->bits[3] = 0x80000000;
  dst = -2.f;
  res = s21_from_decimal_to_float(*src, &tmp);
  ck_assert_float_eq(tmp, dst);
  ck_assert_int_eq(res, 0);

  // test case 7
  src->bits[0] = 0x00000000;
  src->bits[1] = 0x00000000;
  src->bits[2] = 0x00000000;
  src->bits[3] = 0x80000000;
  dst = -0.f;
  res = s21_from_decimal_to_float(*src, &tmp);
  ck_assert_float_eq(tmp, dst);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_decimal_to_int) {
  // test case 1
  int dst = -2147483647;
  s21_decimal src[4];
  src->bits[0] = 0x7FFFFFFF;
  src->bits[1] = 0x00000000;
  src->bits[2] = 0x00000000;
  src->bits[3] = 0x80000000;
  int tmp;
  int res = s21_from_decimal_to_int(*src, &tmp);
  ck_assert_int_eq(tmp, dst);
  ck_assert_int_eq(res, 0);

  // test case 2
  dst = 2147483647;
  src->bits[0] = 0x7FFFFFFF;
  src->bits[1] = 0x00000000;
  src->bits[2] = 0x00000000;
  src->bits[3] = 0x00000000;
  res = s21_from_decimal_to_int(*src, &tmp);
  ck_assert_int_eq(tmp, dst);
  ck_assert_int_eq(res, 0);

  // test case 3
  dst = 0;
  src->bits[0] = 0x00000000;
  src->bits[1] = 0x00000000;
  src->bits[2] = 0x00000000;
  src->bits[3] = 0x00000000;
  res = s21_from_decimal_to_int(*src, &tmp);
  ck_assert_int_eq(tmp, dst);
  ck_assert_int_eq(res, 0);

  // test case 4
  dst = 5;
  src->bits[0] = 0x00000005;
  src->bits[1] = 0x00000000;
  src->bits[2] = 0x00000000;
  src->bits[3] = 0x00000000;
  res = s21_from_decimal_to_int(*src, &tmp);
  ck_assert_int_eq(tmp, dst);
  ck_assert_int_eq(res, 0);

  // test case 5
  dst = -5;
  src->bits[0] = 0x00000005;
  src->bits[1] = 0x00000000;
  src->bits[2] = 0x00000000;
  src->bits[3] = 0x80000000;
  res = s21_from_decimal_to_int(*src, &tmp);
  ck_assert_int_eq(tmp, dst);
  ck_assert_int_eq(res, 0);

  // test case 6
  src->bits[0] = 0x000005C4;
  src->bits[1] = 0x01518D64;
  src->bits[2] = 0x00000000;
  src->bits[3] = 0x80000000;
  int temp;
  res = s21_from_decimal_to_int(*src, &temp);
  ck_assert_int_eq(res, 1);

  // test case 7
  src->bits[0] = 0x000005C4;
  src->bits[1] = 0x01518D64;
  src->bits[2] = 0x00000000;
  src->bits[3] = 0x00000000;
  res = s21_from_decimal_to_int(*src, &temp);
  ck_assert_int_eq(res, 1);

  // test case 8
  dst = 1;
  src->bits[0] = 0x00000457;
  src->bits[1] = 0x00000000;
  src->bits[2] = 0x00000000;
  src->bits[3] = 0x00030000;
  res = s21_from_decimal_to_int(*src, &tmp);
  ck_assert_int_eq(tmp, dst);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_negate_test) {
  // test case 1
  s21_decimal src1, origin, result;
  // src1 = 2.1234;
  src1.bits[0] = 0b00000000000000000101001011110010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000001000000000000000000;
  // origin = -2.1234;
  origin.bits[0] = 0b00000000000000000101001011110010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000001000000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);

  // test case 2
  // src1 = 457.000001;
  src1.bits[0] = 0b00011011001111010100010001000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000001100000000000000000;
  // origin = -457.000001;
  origin.bits[0] = 0b00011011001111010100010001000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000001100000000000000000;
  check_origin = 0;
  check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);

  // test case 3
  // src1 = 2.000;
  src1.bits[0] = 0b00000000000000000000011111010000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000110000000000000000;
  // origin = -2.000;
  origin.bits[0] = 0b00000000000000000000011111010000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000110000000000000000;
  check_origin = 0;
  check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);

  // test case 4
  //  src1 = 0.000000000000000000000000000;
  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000110110000000000000000;
  // origin = 0.000000000000000000000000000;
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000110110000000000000000;
  check_origin = 0;
  check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);

  // test case 5
  //  src1 = -3;
  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  // origin = 3;
  origin.bits[0] = 0b00000000000000000000000000000011;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  check_origin = 0;
  check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);

  // test case 6
  //  src1 = 2.222212;
  src1.bits[0] = 0b00000000001000011110100010000100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000001100000000000000000;
  // origin = -2.222212;
  origin.bits[0] = 0b00000000001000011110100010000100;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000001100000000000000000;
  check_origin = 0;
  check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);

  // test case 7
  //  src1 = 2.22221200000001000;
  src1.bits[0] = 0b00000111100011111010001111101000;
  src1.bits[1] = 0b00000011000101010111110100000001;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000100010000000000000000;
  // origin = -2.22221200000001000;
  origin.bits[0] = 0b00000111100011111010001111101000;
  origin.bits[1] = 0b00000011000101010111110100000001;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000100010000000000000000;
  check_origin = 0;
  check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);

  // test case 8
  // src1 = 3.745754741;
  src1.bits[0] = 0b11011111010000111010111001110101;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000010010000000000000000;
  // origin = -3.745754741;
  origin.bits[0] = 0b11011111010000111010111001110101;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000010010000000000000000;
  check_origin = 0;
  check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);

  // test case 9
  //  src1 = 2.222212;
  src1.bits[0] = 0b00000000001000011110100010000100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000001100000000000000000;
  // origin = -2.222212;
  origin.bits[0] = 0b00000000001000011110100010000100;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000001100000000000000000;
  check_origin = 0;
  check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);

  // test case 10
  //  src1 = -364748;
  src1.bits[0] = 0b00000000000001011001000011001100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  // origin = 364748;
  origin.bits[0] = 0b00000000000001011001000011001100;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  check_origin = 0;
  check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_truncate_test) {
  // test case 1
  s21_decimal src1, origin, result;
  // src1 = 2.1234;
  src1.bits[0] = 0b00000000000000000101001011110010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000001000000000000000000;
  // origin = 2;
  origin.bits[0] = 0b00000000000000000000000000000010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  int check = s21_truncate(src1, &result);
  int check_origin = 0;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);

  // test case 2
  //  src1 = 457.000001;
  src1.bits[0] = 0b00011011001111010100010001000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000001100000000000000000;
  // origin = 457;
  origin.bits[0] = 0b00000000000000000000000111001001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  check = s21_truncate(src1, &result);
  check_origin = 0;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);

  // test case 3
  //  src1 = 2.000;
  src1.bits[0] = 0b00000000000000000000011111010000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000110000000000000000;
  // origin = 2;
  origin.bits[0] = 0b00000000000000000000000000000010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  check = s21_truncate(src1, &result);
  check_origin = 0;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);

  // test case 4
  //  src1 = -3;
  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  // origin = -3;
  origin.bits[0] = 0b00000000000000000000000000000011;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  check = s21_truncate(src1, &result);
  check_origin = 0;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);

  // test case 5
  //  src1 = 2.222212;
  src1.bits[0] = 0b00000000001000011110100010000100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000001100000000000000000;
  // origin = 2;
  origin.bits[0] = 0b00000000000000000000000000000010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  check = s21_truncate(src1, &result);
  check_origin = 0;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);

  // test case 6
  //  src1 = 2.22221200000001000;
  src1.bits[0] = 0b00000111100011111010001111101000;
  src1.bits[1] = 0b00000011000101010111110100000001;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000100010000000000000000;
  // origin = 2;
  origin.bits[0] = 0b00000000000000000000000000000010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  check = s21_truncate(src1, &result);
  check_origin = 0;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);

  // test case 7
  //  src1 = 3.745754741;
  src1.bits[0] = 0b11011111010000111010111001110101;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000010010000000000000000;
  // origin = 3;
  origin.bits[0] = 0b00000000000000000000000000000011;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  check = s21_truncate(src1, &result);
  check_origin = 0;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);

  // test case 8
  //  src1 = 2.222212;
  src1.bits[0] = 0b00000000001000011110100010000100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000001100000000000000000;
  // origin = 2;
  origin.bits[0] = 0b00000000000000000000000000000010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  check = s21_truncate(src1, &result);
  check_origin = 0;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);

  // test case 9
  //  src1 = -364748;
  src1.bits[0] = 0b00000000000001011001000011001100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  // origin = -364748;
  origin.bits[0] = 0b00000000000001011001000011001100;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  check = s21_truncate(src1, &result);
  check_origin = 0;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_round_test) {
  // test case 1
  s21_decimal src, origin, result;
  // src = 5.0;
  src.bits[0] = 0b00000000000000000000000000110010;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000000010000000000000000;
  int check = s21_round(src, &result);
  int check_origin = 0;
  // origin = 5;
  origin.bits[0] = 0b00000000000000000000000000000101;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);

  // test case 2
  //  src = 3.4;
  src.bits[0] = 0b00000000000000000000000000100010;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000000010000000000000000;
  check = s21_round(src, &result);
  check_origin = 0;
  // origin = 3;
  origin.bits[0] = 0b00000000000000000000000000000011;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);

  // test case 4
  //  src = 0.0;
  src.bits[0] = 0b00000000000000000000000000000000;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000000010000000000000000;
  check = s21_round(src, &result);
  check_origin = 0;
  // origin = 0;
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);

  // test case 5
  //  src = -2.4363463;
  src.bits[0] = 0b00000001011100111100000111000111;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b10000000000001110000000000000000;
  check = s21_round(src, &result);
  check_origin = 0;
  // origin = -2;
  origin.bits[0] = 0b00000000000000000000000000000010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);

  // test case 6
  //  src = 652.34631;
  src.bits[0] = 0b00000011111000110110011011000111;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000001010000000000000000;
  check = s21_round(src, &result);
  check_origin = 0;
  // origin = 652;
  origin.bits[0] = 0b00000000000000000000001010001100;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);

  // test case 7
  //  src = 4.97623323;
  src.bits[0] = 0b00011101101010010010000100011011;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000010000000000000000000;
  check = s21_round(src, &result);
  check_origin = 0;
  // origin = 5;
  origin.bits[0] = 0b00000000000000000000000000000101;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);

  // test case 8
  //  src = 65658654.59;
  src.bits[0] = 0b10000111010110110010011111110011;
  src.bits[1] = 0b00000000000000000000000000000001;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000000100000000000000000;
  check = s21_round(src, &result);
  check_origin = 0;
  // origin = 65658655;
  origin.bits[0] = 0b00000011111010011101111100011111;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);

  // test case 9
  //  src = -364748.110;
  src.bits[0] = 0b00010101101111011001110101001110;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b10000000000000110000000000000000;
  check = s21_round(src, &result);
  check_origin = 0;
  // origin = -364748;
  origin.bits[0] = 0b00000000000001011001000011001100;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);

  // test case 10
  //  src = 1.9874565432111;
  src.bits[0] = 0b01101000011010011010001100101111;
  src.bits[1] = 0b00000000000000000001001000010011;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000011010000000000000000;
  check = s21_round(src, &result);
  check_origin = 0;
  // origin = 2;
  origin.bits[0] = 0b00000000000000000000000000000010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_floor_test) {
  // test case 1
  s21_decimal src, origin, result;
  // src = 5.0;
  src.bits[0] = 0b00000000000000000000000000110010;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000000010000000000000000;
  int check = s21_floor(src, &result);
  int check_origin = 0;
  // origin = 5;
  origin.bits[0] = 0b00000000000000000000000000000101;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);

  // test case 2
  //  src = 3.4;
  src.bits[0] = 0b00000000000000000000000000100010;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000000010000000000000000;
  check = s21_floor(src, &result);
  check_origin = 0;
  // origin = 3;
  origin.bits[0] = 0b00000000000000000000000000000011;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);

  // test case 3
  //  src = 0.0;
  src.bits[0] = 0b00000000000000000000000000000000;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000000010000000000000000;
  check = s21_floor(src, &result);
  check_origin = 0;
  // origin = 0;
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);

  // test case 4
  //  src = -0.45;
  src.bits[0] = 0b00000000000000000000000000101101;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b10000000000000100000000000000000;
  check = s21_floor(src, &result);
  check_origin = 0;
  // origin = -1;
  origin.bits[0] = 0b00000000000000000000000000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);

  // test case 5
  //  src = 652.34631;
  src.bits[0] = 0b00000011111000110110011011000111;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000001010000000000000000;
  check = s21_floor(src, &result);
  check_origin = 0;
  // origin = 652;
  origin.bits[0] = 0b00000000000000000000001010001100;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);

  // test case 6
  //  src = 4.97623323;
  src.bits[0] = 0b00011101101010010010000100011011;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000010000000000000000000;
  check = s21_floor(src, &result);
  check_origin = 0;
  // origin = 4;
  origin.bits[0] = 0b00000000000000000000000000000100;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);

  // test case 7
  //  src = 65658654.59;
  src.bits[0] = 0b10000111010110110010011111110011;
  src.bits[1] = 0b00000000000000000000000000000001;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000000100000000000000000;
  check = s21_floor(src, &result);
  check_origin = 0;
  // origin = 65658654;
  origin.bits[0] = 0b00000011111010011101111100011110;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);

  // test case 8
  //  src = 1.9874565432111;
  src.bits[0] = 0b01101000011010011010001100101111;
  src.bits[1] = 0b00000000000000000001001000010011;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000011010000000000000000;
  check = s21_floor(src, &result);
  check_origin = 0;
  // origin = 1;
  origin.bits[0] = 0b00000000000000000000000000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);

  // test case 9
  //  src = 545454512454545.35265454545645;
  src.bits[0] = 0b10000010111000100101101011101101;
  src.bits[1] = 0b11111001111010000010010110101101;
  src.bits[2] = 0b10110000001111101111000010010100;
  src.bits[3] = 0b00000000000011100000000000000000;
  check = s21_floor(src, &result);
  check_origin = 0;
  // origin = 545454512454545;
  origin.bits[0] = 0b10000110011101001011101110010001;
  origin.bits[1] = 0b00000000000000011111000000010110;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

int main(void) {
  Suite *suite = suite_create(SUITE_NAME);
  TCase *tcase = tcase_create(TCASE_NAME);
  SRunner *srunner = srunner_create(suite);
  int counted_errors = 0;

  suite_add_tcase(suite, tcase);
  // arithmetic
  tcase_add_test(tcase, s21_add_test);
  tcase_add_test(tcase, s21_sub_test);
  tcase_add_test(tcase, s21_mul_test);
  tcase_add_test(tcase, s21_dev_test);
  // compare
  tcase_add_test(tcase, test_s21_is_greater);
  tcase_add_test(tcase, test_s21_is_greater_or_equal);
  tcase_add_test(tcase, test_s21_is_equal);
  tcase_add_test(tcase, test_s21_is_not_equal);
  tcase_add_test(tcase, test_s21_is_less);
  tcase_add_test(tcase, test_s21_is_less_or_equal);
  // convertors
  tcase_add_test(tcase, test_int_to_decimal);
  tcase_add_test(tcase, test_float_to_decimal);
  tcase_add_test(tcase, test_decimal_to_float);
  tcase_add_test(tcase, test_decimal_to_int);
  // other
  tcase_add_test(tcase, s21_negate_test);
  tcase_add_test(tcase, s21_truncate_test);
  tcase_add_test(tcase, s21_round_test);
  tcase_add_test(tcase, s21_floor_test);

  srunner_set_fork_status(srunner, CK_NOFORK);
  srunner_run_all(srunner, CK_VERBOSE);
  counted_errors = srunner_ntests_failed(srunner);
  srunner_free(srunner);

  return counted_errors == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
