#include "gtest/gtest.h"

#include "result.h"
#include "result_error.h"

TEST(result_class, create_result_with_int_value) {
  fig::util::Result<int, bool> r(1);
  r.operator bool(); // must check
  EXPECT_EQ(r.value(), 1);
}

TEST(result_class, create_result_with_bool_error) {
  fig::util::Result<int, bool> r(false);
  r.operator bool(); // must check
  EXPECT_EQ(r.error(), false);
}

TEST(result_class, result_with_int_value_tests_true) {
  fig::util::Result<int, bool> r(100);
  EXPECT_TRUE(r);
}

TEST(result_class, result_with_bool_error_tests_false) {
  fig::util::Result<int, bool> r(false);
  EXPECT_FALSE(r);
}

TEST(result_class, throw_when_result_with_int_value_not_checked) {
  fig::util::Result<int, bool> r(100);
  EXPECT_THROW(r.value(), fig::util::ResultNotCheckedError);
}

TEST(result_class, throw_when_result_with_bool_error_not_checked) {
  fig::util::Result<int, bool> r(100);
  EXPECT_THROW(r.error(), fig::util::ResultNotCheckedError);
}

TEST(result_class, result_with_int_value_returned_by_value) {
  auto f = []() -> fig::util::Result<int, bool> {
    return fig::util::Result<int, bool>(100);
  };

  auto r = f();
  r.operator bool(); // must check
  EXPECT_EQ(r.value(), 100);
}

TEST(result_class, result_with_bool_error_returned_by_value) {
  auto f = []() -> fig::util::Result<int, bool> {
    return fig::util::Result<int, bool>(false);
  };

  auto r = f();
  r.operator bool(); // must check
  EXPECT_EQ(r.error(), false);
}

TEST(result_class,
     throw_when_result_with_int_value_returned_by_value_not_checked) {
  auto f = []() -> fig::util::Result<int, bool> {
    return fig::util::Result<int, bool>(100);
  };

  auto r = f();
  EXPECT_THROW(r.value(), fig::util::ResultNotCheckedError);
}

TEST(result_class,
     throw_when_result_with_bool_error_returned_by_value_not_checked) {
  auto f = []() -> fig::util::Result<int, bool> {
    return fig::util::Result<int, bool>(false);
  };

  auto r = f();
  EXPECT_THROW(r.value(), fig::util::ResultNotCheckedError);
}
