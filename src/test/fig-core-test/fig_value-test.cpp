#include "gtest/gtest.h"

#include "fig_value.h"

template <typename TChar>
class FigValueTypedFixture : public ::testing::Test {
public:
  const TChar* input_value_int_type();
  const TChar* input_value_unsigned_type();
  const TChar* input_value_float_type();

  int test_value_int = 42;
  long test_value_long = 42L;
  long long test_value_ll = 42LL;

  unsigned int test_value_unsigned_int = 42U;
  unsigned long test_value_unsigned_int = 42UL;
  unsigned long long test_value_unsigned_int = 42ULL;

  float test_value_float = 42.42;
  double test_value_double = 42.42;
  long double test_value_ld = 42.42;

  typedef std::basic_string<TChar> StringType;
};

template <>
const char* FigValueTypedFixture<char>::input_value_int_type() {
  return "42";
}

template <>
const wchar_t* FigValueTypedFixture<wchar_t>::input_value_int_type() {
  return L"42";
}

template <>
const char* FigValueTypedFixture<char>::input_value_unsigned_type() {
  return "42";
}

template <>
const wchar_t* FigValueTypedFixture<wchar_t>::input_value_unsigned_type() {
  return L"42";
}

template <>
const char* FigValueTypedFixture<char>::input_value_float_type() {
  return "42.42";
}

template <>
const wchar_t* FigValueTypedFixture<wchar_t>::input_value_float_type() {
  return L"42.42";
}

using MyTypes = ::testing::Types<char, wchar_t>;
TYPED_TEST_CASE(FigValueTypedFixture, MyTypes);

TYPED_TEST(FigValueTypedFixture, create_value_from_const_char) {
  using StringType = typename FigKeyTypedFixture::StringType;
  using ValueType = fig::core::FigValue<StringType>;

  ValueType v(this->input_value_int_type());

  ASSERT_EQ(v.get<int>(), this->test_value_int);
}
