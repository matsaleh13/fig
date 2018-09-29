#include "gtest/gtest.h"

#include "macros.h"



TEST(macros, format_string_with_va_args) {
  auto msg = FORMAT_STRING("Formatting string: [%s]", "hello world");

  ASSERT_EQ(msg, std::string("Formatting string: [hello world]"));
}

TEST(macros, format_string_with_no_va_args) {
  auto msg = FORMAT_STRING("Formatting string with no args: [hello world]");

  ASSERT_EQ(msg, std::string("Formatting string with no args: [hello world]"));
}

TEST(macros, error_with_va_args_and_file_line) {
  auto e = FIG_ERROR("Formatting string: [%s]", "hello world"); auto line = __LINE__;

  ASSERT_EQ(e.what(), std::string("Formatting string: [hello world]"));
  ASSERT_EQ(e.file(), __FILE__);
  ASSERT_EQ(e.line(), line);
}

TEST(macros, error_with_no_va_args_and_file_line) {
  auto e = FIG_ERROR("Formatting string with no args: [hello world]"); auto line = __LINE__;

  ASSERT_EQ(e.what(), std::string("Formatting string with no args: [hello world]"));
  ASSERT_EQ(e.file(), __FILE__);
  ASSERT_EQ(e.line(), line);
}
