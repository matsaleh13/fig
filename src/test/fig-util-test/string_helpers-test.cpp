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
    // Pad with some character to fill the buffer.
    memset(m_large_format_string, 'X', BUF_SIZE);
    memset(m_large_result_string, 'X', BUF_SIZE);
  }

  template <size_t N>
  void init_format(const char (&format)[N]) {
    memcpy(m_large_format_string, format, N);
  }

  template <size_t N>
  void init_result(const char (&result)[N]) {
    memcpy(m_large_result_string, result, N);
  }

  const static size_t BUF_SIZE = fig::util::MIN_BUF_SIZE * 2;
  char m_large_format_string[BUF_SIZE];
  char m_large_result_string[BUF_SIZE];
};

TEST_F(StringHelpersLargeBufferFixture, format_string_using_const_char_buf) {
  init_format("Formatting string: [%s]");
  init_result("Formatting string: [hello world]");

  auto msg = fig::util::string_format(m_large_format_string, "hello world");

  std::cerr << m_large_result_string << std::endl;

  ASSERT_EQ(msg, std::string(m_large_result_string));
}

TEST_F(StringHelpersLargeBufferFixture, format_numbers_using_const_char_buf) {
  init_format("Formatting numbers: [%d] [%0.3f] [%08x]");
  init_result("Formatting numbers: [42] [42.420] [00000042]");

  auto msg = fig::util::string_format(m_large_format_string, 42, 42.42, 0x42);

  ASSERT_EQ(msg, std::string(m_large_result_string));
}

TEST_F(StringHelpersLargeBufferFixture, format_string_using_std_string) {
  init_format("Formatting string: [%s]");
  init_result("Formatting string: [hello world]");

  auto msg = fig::util::string_format(std::string(m_large_format_string),
                                      "hello world");

  ASSERT_EQ(msg, std::string(m_large_result_string));
}

TEST_F(StringHelpersLargeBufferFixture, format_numbers_using_std_string) {
  init_format("Formatting numbers: [%d] [%0.3f] [%08x]");
  init_result("Formatting numbers: [42] [42.420] [00000042]");

  auto msg = fig::util::string_format(
      std::string(m_large_format_string), 42, 42.42, 0x42);

  ASSERT_EQ(msg, std::string(m_large_result_string));
}

TEST_F(StringHelpersLargeBufferFixture, format_string_using_std_string_cstr) {
  init_format("Formatting string: [%s]");
  init_result("Formatting string: [hello world]");

  auto msg = fig::util::string_format(
      std::string(m_large_format_string).c_str(), "hello world");

  ASSERT_EQ(msg, std::string(m_large_result_string));
}

TEST_F(StringHelpersLargeBufferFixture, format_numbers_using_std_string_cstr) {
  init_format("Formatting numbers: [%d] [%0.3f] [%08x]");
  init_result("Formatting numbers: [42] [42.420] [00000042]");

  auto msg = fig::util::string_format(
      std::string(m_large_format_string).c_str(), 42, 42.42,
      0x42);

  ASSERT_EQ(msg, std::string(m_large_result_string));
}

// Negative path tests
TEST_F(StringHelpersLargeBufferFixture, format_string_using_const_char_buf_neg) {
  init_format("Formatting string: [%s]");
  init_result("Formatting string: [hello world]");

  auto msg = fig::util::string_format(m_large_format_string, "hello world");

  ASSERT_TRUE(msg != std::string("Formatting string: [hello world]"));
  // ASSERT_NE(msg, std::string("Formatting string: [hello world]"));
}

TEST_F(StringHelpersLargeBufferFixture, format_numbers_using_const_char_buf_neg) {
  init_format("Formatting numbers: [%d] [%0.3f] [%08x]");
  init_result("Formatting numbers: [42] [42.420] [00000042]");

  auto msg = fig::util::string_format(m_large_format_string, 42, 42.42, 0x42);

  ASSERT_NE(msg, std::string("Formatting numbers: [42] [42.420] [00000042]"));
}

TEST_F(StringHelpersLargeBufferFixture, format_string_using_std_string_neg) {
  init_format("Formatting string: [%s]");
  init_result("Formatting string: [hello world]");

  auto msg = fig::util::string_format(std::string(m_large_format_string),
                                      "hello world");

  ASSERT_NE(msg, std::string("Formatting string: [hello world]"));
}

TEST_F(StringHelpersLargeBufferFixture, format_numbers_using_std_string_neg) {
  init_format("Formatting numbers: [%d] [%0.3f] [%08x]");
  init_result("Formatting numbers: [42] [42.420] [00000042]");

  auto msg = fig::util::string_format(
      std::string(m_large_format_string), 42, 42.42, 0x42);

  ASSERT_NE(msg, std::string("Formatting numbers: [42] [42.420] [00000042]"));
}

TEST_F(StringHelpersLargeBufferFixture, format_string_using_std_string_cstr_neg) {
  init_format("Formatting string: [%s]");
  init_result("Formatting string: [hello world]");

  auto msg = fig::util::string_format(
      std::string(m_large_format_string).c_str(), "hello world");

  ASSERT_NE(msg, std::string("Formatting string: [hello world]"));
}

TEST_F(StringHelpersLargeBufferFixture, format_numbers_using_std_string_cstr_neg) {
  init_format("Formatting numbers: [%d] [%0.3f] [%08x]");
  init_result("Formatting numbers: [42] [42.420] [00000042]");

  auto msg = fig::util::string_format(
      std::string(m_large_format_string).c_str(), 42, 42.42,
      0x42);

  ASSERT_NE(msg, std::string("Formatting numbers: [42] [42.420] [00000042]"));
}