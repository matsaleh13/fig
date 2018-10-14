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
  long long test_value_long_long = 42LL;

  unsigned int test_value_unsigned_int = 42U;
  unsigned long test_value_unsigned_long = 42UL;
  unsigned long long test_value_unsigned_long_long = 42ULL;

  float test_value_float = 42.42f;
  double test_value_double = 42.42;
  long double test_value_long_double = 42.42;

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
  using StringType = FigValueTypedFixture::StringType;
  using ValueType = fig::core::FigValue<StringType>;

  ValueType v(this->input_value_int_type());
  ASSERT_EQ(v.get(), this->input_value_int_type());
}

TYPED_TEST(FigValueTypedFixture, create_value_from_basic_string) {
  using StringType = FigValueTypedFixture::StringType;
  using ValueType = fig::core::FigValue<StringType>;

  ValueType v(StringType(this->input_value_int_type()));
  ASSERT_EQ(v.get(), this->input_value_int_type());
}

TYPED_TEST(FigValueTypedFixture, create_value_with_init) {
  using StringType = FigValueTypedFixture::StringType;
  using ValueType = fig::core::FigValue<StringType>;

  ValueType v = StringType(this->input_value_int_type());

  ASSERT_EQ(v.get(), this->input_value_int_type());
}

TYPED_TEST(FigValueTypedFixture, create_value_default_then_assign) {
  using StringType = FigValueTypedFixture::StringType;
  using ValueType = fig::core::FigValue<StringType>;

  ValueType v;
  v = StringType(this->input_value_int_type());

  ASSERT_EQ(v.get(), this->input_value_int_type());
}

TYPED_TEST(FigValueTypedFixture, get_as_int_types) {
  using StringType = FigValueTypedFixture::StringType;
  using ValueType = fig::core::FigValue<StringType>;

  ValueType v(this->input_value_int_type());

  ASSERT_EQ(v.get<int>(), this->test_value_int);
  ASSERT_EQ(v.get<long>(), this->test_value_long);
  ASSERT_EQ(v.get<long long>(), this->test_value_long_long);
}

TYPED_TEST(FigValueTypedFixture, get_as_unsigned_types) {
  using StringType = FigValueTypedFixture::StringType;
  using ValueType = fig::core::FigValue<StringType>;

  ValueType v(this->input_value_unsigned_type());

  ASSERT_EQ(v.get<unsigned int>(), this->test_value_unsigned_int);
  ASSERT_EQ(v.get<unsigned long>(), this->test_value_unsigned_long);
  ASSERT_EQ(v.get<unsigned long long>(), this->test_value_unsigned_long);
}

TYPED_TEST(FigValueTypedFixture, get_as_float_types) {
  using StringType = FigValueTypedFixture::StringType;
  using ValueType = fig::core::FigValue<StringType>;

  ValueType v(this->input_value_float_type());

  ASSERT_EQ(v.get<float>(), this->test_value_float);
  ASSERT_EQ(v.get<double>(), this->test_value_double);
  ASSERT_EQ(v.get<long double>(), this->test_value_long_double);
}