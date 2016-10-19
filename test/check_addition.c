#include <check.h>
#include <addition.h>

START_TEST (test_addition) {
  ck_assert_int_eq(add(1, 2), 3);
  ck_assert_int_eq(add(0, 0), 0);
} END_TEST

Suite * money_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Addition");

  /* Core test case */
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_addition);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  size_t number_failed;
  Suite *s;
  SRunner *sr;

  s = money_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}
