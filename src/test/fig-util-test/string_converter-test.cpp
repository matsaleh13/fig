#include "gtest/gtest.h"

#include "result.h"
#include "error.h"
#include "string_converter.h"


template <typename TChar>
class StringValueTypedFixture : public ::testing::Test {
public:
  const TChar* input_value_int_type();
  const TChar* input_value_unsigned_type();
  const TChar* input_value_float_type();
  const TChar* input_value_string_type();

  int test_value_int = 42;
  long test_value_long = 42L;
  long long test_value_long_long = 42LL;

  unsigned int test_value_unsigned_int = 42U;
  unsigned long test_value_unsigned_long = 42UL;
  unsigned long long test_value_unsigned_long_long = 42ULL;

  float test_value_float = 42.42f;
  double test_value_double = 42.42;
  long double test_value_long_double = 42.42;

  const char* test_value_char_string = "The rain in Spain falls ma\u00F1ana.";
  const wchar_t* test_value_wchar_string =
      L"The rain in Spain falls ma\u00F1ana.";

  using StringType = std::basic_string<TChar>;
};

template <>
const char* StringValueTypedFixture<char>::input_value_int_type() {
  return "42";
}

template <>
const wchar_t* StringValueTypedFixture<wchar_t>::input_value_int_type() {
  return L"42";
}

template <>
const char* StringValueTypedFixture<char>::input_value_unsigned_type() {
  return "42";
}

template <>
const wchar_t* StringValueTypedFixture<wchar_t>::input_value_unsigned_type() {
  return L"42";
}

template <>
const char* StringValueTypedFixture<char>::input_value_float_type() {
  return "42.42";
}

template <>
const wchar_t* StringValueTypedFixture<wchar_t>::input_value_float_type() {
  return L"42.42";
}

template <>
const char* StringValueTypedFixture<char>::input_value_string_type() {
  return "The rain in Spain falls ma\u00F1ana.";
}

template <>
const wchar_t* StringValueTypedFixture<wchar_t>::input_value_string_type() {
  return L"The rain in Spain falls ma\u00F1ana.";
}

using MyTypes = ::testing::Types<char, wchar_t>;
TYPED_TEST_CASE(StringValueTypedFixture, MyTypes);

//
// StringConverter tests.
//

static void foo() {
    int converted =
      fig::util::StringConverter<std::string, int>::convert(std::string("1"));
}

TYPED_TEST(StringValueTypedFixture, convert_to_int_types) {
  using StringType = StringValueTypedFixture::StringType;

  int converted =
      fig::util::StringConverter<typename StringType, int>::convert(this->input_value_int_type());
  EXPECT_EQ(converted, this->test_value_int);

  fig::util::Result<int, fig::util::Error> result = fig::util::StringConverter<StringType, int>::convert_safe(
      this->input_value_int_type());
  if (result) {
    EXPECT_EQ(result.value(), this->test_value_int);
  }
  else {
    ADD_FAILURE();
  }
}



