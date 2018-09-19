#include "gtest/gtest.h"

#include "result.h"

   
TEST(result_class, create_result_with_int_value)
{
  fig::util::Result<int, bool> r(1);
  EXPECT_EQ(r.value(), 1);
}

TEST(result_class, create_result_with_bool_error)
{
  fig::util::Result<int, bool> r(false);
  EXPECT_EQ(r.error(), false);
}

TEST(result_class, create_result_with_int_value_tests_true)
{
  fig::util::Result<int, bool> r(100);
  EXPECT_TRUE(r);
}

TEST(result_class, create_result_with_bool_error_tests_false)
{
  fig::util::Result<int, bool> r(false);
  EXPECT_FALSE(r);
}

TEST(result_class, create_result_with_int_value_get_error)
{
  fig::util::Result<int, bool> r(100);
  EXPECT_ANY_THROW(r.error());
}
