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