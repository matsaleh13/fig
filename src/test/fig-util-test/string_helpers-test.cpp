#include "gtest/gtest.h"

#include "string_helpers.h"

TEST(string_helpers, format_string_using_const_char_buf) {
  auto msg = fig::util::string_format("Formatting string: [%s]", "hello world");

  ASSERT_EQ(msg, std::string("Formatting string: [hello world]"));
}

TEST(string_helpers, format_numbers_using_const_char_buf) {
  auto msg = fig::util::string_format("Formatting numbers: [%d] [%0.3f] [%08x]",
                                      42, 42.42, 0x42);

  ASSERT_EQ(msg, std::string("Formatting numbers: [42] [42.420] [00000042]"));
}

TEST(string_helpers, format_string_using_std_string) {
  auto msg = fig::util::string_format(std::string("Formatting string: [%s]"),
                                      "hello world");

  ASSERT_EQ(msg, std::string("Formatting string: [hello world]"));
}

TEST(string_helpers, format_numbers_using_std_string) {
  auto msg = fig::util::string_format(
      std::string("Formatting numbers: [%d] [%0.3f] [%08x]"), 42, 42.42, 0x42);

  ASSERT_EQ(msg, std::string("Formatting numbers: [42] [42.420] [00000042]"));
}

TEST(string_helpers, format_string_using_std_string_cstr) {
  auto msg = fig::util::string_format(
      std::string("Formatting string: [%s]").c_str(), "hello world");

  ASSERT_EQ(msg, std::string("Formatting string: [hello world]"));
}

TEST(string_helpers, format_numbers_using_std_string_cstr) {
  auto msg = fig::util::string_format(
      std::string("Formatting numbers: [%d] [%0.3f] [%08x]").c_str(), 42, 42.42,
      0x42);

  ASSERT_EQ(msg, std::string("Formatting numbers: [42] [42.420] [00000042]"));
}

//
// Testing with format string sizes > fig::util::MIN_BUF_SIZE
//
class StringHelpersLargeBufferFixture : public ::testing::Test {
protected:
  StringHelpersLargeBufferFixture() {
    // Fill with some characters to pad the buffer.
    memset(m_large_format_string, 'X', BUF_SIZE-1);   // all but last
    m_large_format_string[BUF_SIZE-1] = '\0'; // term null
    memset(m_large_result_string, 'X', BUF_SIZE-1);   // all but last
    m_large_result_string[BUF_SIZE-1] = '\0'; // term null
  }

  template <size_t N>
  void init_format(const char (&format)[N], size_t delta) {
    memcpy(m_large_format_string, format, N - 1);  // Omit terminating null.
    m_large_format_string[BUF_SIZE-delta] = '\0';  // account for the number of chars that will be added to the string.
  }

  template <size_t N>
  void init_result(const char (&result)[N]) { 
    memcpy(m_large_result_string, result, N - 1);  // Omit terminating null.
  }

  const static size_t BUF_SIZE = fig::util::MIN_BUF_SIZE * 2;
  char m_large_format_string[BUF_SIZE];
  char m_large_result_string[BUF_SIZE];
};

// Differences in lengths of format strings vs. formatted strings.
// NOTE: totally depends on test data values.
size_t HELLO_WORLD_DELTA = 10;
size_t FORTY_TWO_DELTA = 6;

TEST_F(StringHelpersLargeBufferFixture, format_string_using_const_char_buf) {
  init_format("Formatting string: [%s]", HELLO_WORLD_DELTA);
  init_result("Formatting string: [hello world]");

  auto msg = fig::util::string_format(m_large_format_string, "hello world");

  ASSERT_EQ(msg, std::string(m_large_result_string));  // std::string to avoid pointer compare.
}

TEST_F(StringHelpersLargeBufferFixture, format_numbers_using_const_char_buf) {
  init_format("Formatting numbers: [%d] [%0.3f] [%08x]", FORTY_TWO_DELTA);
  init_result("Formatting numbers: [42] [42.420] [00000042]");

  auto msg = fig::util::string_format(m_large_format_string, 42, 42.42, 0x42); 

  ASSERT_EQ(msg, std::string(m_large_result_string)); // std::string to avoid pointer compare.
}

TEST_F(StringHelpersLargeBufferFixture, format_string_using_std_string) {
  init_format("Formatting string: [%s]", HELLO_WORLD_DELTA);
  init_result("Formatting string: [hello world]");

  auto msg = fig::util::string_format(std::string(m_large_format_string),
                                      "hello world");

  ASSERT_EQ(msg, std::string(m_large_result_string)); // std::string to avoid pointer compare.
}

TEST_F(StringHelpersLargeBufferFixture, format_numbers_using_std_string) {
  init_format("Formatting numbers: [%d] [%0.3f] [%08x]", FORTY_TWO_DELTA);
  init_result("Formatting numbers: [42] [42.420] [00000042]");

  auto msg = fig::util::string_format(
      std::string(m_large_format_string), 42, 42.42, 0x42);

  ASSERT_EQ(msg, std::string(m_large_result_string)); // std::string to avoid pointer compare.
}

TEST_F(StringHelpersLargeBufferFixture, format_string_using_std_string_cstr) {
  init_format("Formatting string: [%s]", HELLO_WORLD_DELTA);
  init_result("Formatting string: [hello world]");

  auto msg = fig::util::string_format(
      std::string(m_large_format_string).c_str(), "hello world");

  ASSERT_EQ(msg, std::string(m_large_result_string)); // std::string to avoid pointer compare.
}

TEST_F(StringHelpersLargeBufferFixture, format_numbers_using_std_string_cstr) {
  init_format("Formatting numbers: [%d] [%0.3f] [%08x]", FORTY_TWO_DELTA);
  init_result("Formatting numbers: [42] [42.420] [00000042]");

  auto msg = fig::util::string_format(
      std::string(m_large_format_string).c_str(), 42, 42.42,
      0x42);

  ASSERT_EQ(msg, std::string(m_large_result_string)); // std::string to avoid pointer compare.
}

// Negative path tests
TEST_F(StringHelpersLargeBufferFixture, format_string_using_const_char_buf_neg) {
  init_format("Formatting string: [%s]", HELLO_WORLD_DELTA);
  init_result("Formatting string: [hello world]");

  auto msg = fig::util::string_format(m_large_format_string, "hello world");

  // ASSERT_TRUE(msg != std::string("Formatting string: [hello world]"));
  ASSERT_NE(msg, std::string("Formatting string: [hello world]")); // std::string to avoid pointer compare.
}

TEST_F(StringHelpersLargeBufferFixture, format_numbers_using_const_char_buf_neg) {
  init_format("Formatting numbers: [%d] [%0.3f] [%08x]", FORTY_TWO_DELTA);
  init_result("Formatting numbers: [42] [42.420] [00000042]"); 

  auto msg = fig::util::string_format(m_large_format_string, 42, 42.42, 0x42);

  ASSERT_NE(msg, std::string("Formatting numbers: [42] [42.420] [00000042]")); // std::string to avoid pointer compare.
}

TEST_F(StringHelpersLargeBufferFixture, format_string_using_std_string_neg) {
  init_format("Formatting string: [%s]", HELLO_WORLD_DELTA);
  init_result("Formatting string: [hello world]");

  auto msg = fig::util::string_format(std::string(m_large_format_string),
                                      "hello world");

  ASSERT_NE(msg, std::string("Formatting string: [hello world]")); // std::string to avoid pointer compare.;
}

TEST_F(StringHelpersLargeBufferFixture, format_numbers_using_std_string_neg) {
  init_format("Formatting numbers: [%d] [%0.3f] [%08x]", FORTY_TWO_DELTA);
  init_result("Formatting numbers: [42] [42.420] [00000042]");

  auto msg = fig::util::string_format(
      std::string(m_large_format_string), 42, 42.42, 0x42);

  ASSERT_NE(msg, std::string("Formatting numbers: [42] [42.420] [00000042]")); // std::string to avoid pointer compare.
}

TEST_F(StringHelpersLargeBufferFixture, format_string_using_std_string_cstr_neg) {
  init_format("Formatting string: [%s]", HELLO_WORLD_DELTA);
  init_result("Formatting string: [hello world]");

  auto msg = fig::util::string_format(
      std::string(m_large_format_string).c_str(), "hello world");

  ASSERT_NE(msg, std::string("Formatting string: [hello world]")); // std::string to avoid pointer compare.
}

TEST_F(StringHelpersLargeBufferFixture, format_numbers_using_std_string_cstr_neg) {
  init_format("Formatting numbers: [%d] [%0.3f] [%08x]", FORTY_TWO_DELTA);
  init_result("Formatting numbers: [42] [42.420] [00000042]");

  auto msg = fig::util::string_format(
      std::string(m_large_format_string).c_str(), 42, 42.42,
      0x42);

  ASSERT_NE(msg, std::string("Formatting numbers: [42] [42.420] [00000042]")); // std::string to avoid pointer compare.
}

//
// fig::util::tolower
//
TEST(string_helpers, tolower_using_std_string) {
  auto input = "HELLO WORLD";
  auto expected = "hello world";

  auto convert = std::string(input);
  fig::util::tolower(convert);

  ASSERT_EQ(convert, std::string(expected));
}

TEST(string_helpers, tolower_return_using_std_string) {
  auto input = "HELLO WORLD";
  auto expected = "hello world";

  auto convert = fig::util::tolower(std::string(input));;

  ASSERT_EQ(convert, std::string(expected));
}

TEST(string_helpers, tolower_using_std_wstring) {
  auto input = L"HELLO WORLD";
  auto expected = L"hello world";

  auto convert = std::wstring(input);
  fig::util::tolower(convert);

  ASSERT_EQ(convert, std::wstring(expected));
}

TEST(string_helpers, tolower_return_using_std_wstring) {
  auto input = L"HELLO WORLD";
  auto expected = L"hello world";

  auto convert = fig::util::tolower(std::wstring(input));;

  ASSERT_EQ(convert, std::wstring(expected));
}

//
// fig::util::[w]string_to[w]string
//

TEST(string_helpers, string_to_wstring) {
  const char* input = "But I'm not dead.";
  const wchar_t* expected = L"But I'm not dead.";

  auto convert = fig::util::string_to_wstring(input);

  ASSERT_EQ(convert, std::wstring(expected));
}

TEST(string_helpers, wstring_to_string) {
  const wchar_t* input = L"I didn't vote for you.";
  const char* expected = "I didn't vote for you.";

  auto convert = fig::util::wstring_to_string(input);

  ASSERT_EQ(convert, std::string(expected));
}