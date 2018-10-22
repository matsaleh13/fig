#include "gtest/gtest.h"

#include "fig_value.h"

template <typename TChar>
class FigValueTypedFixture : public ::testing::Test {
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

template <>
const char* FigValueTypedFixture<char>::input_value_string_type() {
  return "The rain in Spain falls ma\u00F1ana.";
}

template <>
const wchar_t* FigValueTypedFixture<wchar_t>::input_value_string_type() {
  return L"The rain in Spain falls ma\u00F1ana.";
}

using MyTypes = ::testing::Types<char, wchar_t>;
TYPED_TEST_CASE(FigValueTypedFixture, MyTypes);


//
// Create FigValue Tests
//

template <typename TString>
static void CheckGetNativeValue(const fig::core::FigValue<TString>& v,
                                const TString& test) {
  EXPECT_EQ(v.get(), test);
}

TYPED_TEST(FigValueTypedFixture, create_value_from_const_char) {
  using StringType = FigValueTypedFixture::StringType;
  using ValueType = fig::core::FigValue<StringType>;

  ValueType v(this->input_value_int_type());
  CheckGetNativeValue<StringType>(v, this->input_value_int_type());
}

TYPED_TEST(FigValueTypedFixture, create_value_from_basic_string) {
  using StringType = FigValueTypedFixture::StringType;
  using ValueType = fig::core::FigValue<StringType>;

  ValueType v(StringType(this->input_value_int_type()));
  CheckGetNativeValue<StringType>(v, this->input_value_int_type());
}

TYPED_TEST(FigValueTypedFixture, create_value_with_init) {
  using StringType = FigValueTypedFixture::StringType;
  using ValueType = fig::core::FigValue<StringType>;

  ValueType v = StringType(this->input_value_int_type());
  CheckGetNativeValue<StringType>(v, this->input_value_int_type());
}

TYPED_TEST(FigValueTypedFixture, create_value_default_then_assign) {
  using StringType = FigValueTypedFixture::StringType;
  using ValueType = fig::core::FigValue<StringType>;

  ValueType v;
  v = StringType(this->input_value_int_type());
  CheckGetNativeValue<StringType>(v, this->input_value_int_type());
}

//
// get<TValue> and get_safe<TValue> tests.
//

template <typename TString, typename TValue>
static void CheckGetConvertedValue(const fig::core::FigValue<TString>& v,
                                   const TValue& test) {

  EXPECT_EQ(v.get<TValue>(), test);

  auto r = v.get_safe<TValue>();
  if (r) {
    EXPECT_EQ(r.value(), test);
  } else {
    GTEST_FAIL();
  }
}

TYPED_TEST(FigValueTypedFixture, get_as_int_types) {
  using StringType = FigValueTypedFixture::StringType;
  using ValueType = fig::core::FigValue<StringType>;

  ValueType v(this->input_value_int_type());

  CheckGetConvertedValue<StringType, int>(v, this->test_value_int);
  CheckGetConvertedValue<StringType, long>(v, this->test_value_long);
  CheckGetConvertedValue<StringType, long long>(v, this->test_value_long_long);
}

TYPED_TEST(FigValueTypedFixture, get_as_unsigned_types) {
  using StringType = FigValueTypedFixture::StringType;
  using ValueType = fig::core::FigValue<StringType>;

  ValueType v(this->input_value_unsigned_type());

  EXPECT_EQ(v.get<unsigned int>(), this->test_value_unsigned_int);
  EXPECT_EQ(v.get<unsigned long>(), this->test_value_unsigned_long);
  EXPECT_EQ(v.get<unsigned long long>(), this->test_value_unsigned_long);
}

TYPED_TEST(FigValueTypedFixture, get_as_float_types) {
  using StringType = FigValueTypedFixture::StringType;
  using ValueType = fig::core::FigValue<StringType>;

  ValueType v(this->input_value_float_type());

  EXPECT_EQ(v.get<float>(), this->test_value_float);
  EXPECT_EQ(v.get<double>(), this->test_value_double);
  EXPECT_EQ(v.get<long double>(), this->test_value_long_double);
}

TYPED_TEST(FigValueTypedFixture, get_as_string_types) {
  using StringType = FigValueTypedFixture::StringType;
  using ValueType = fig::core::FigValue<StringType>;

  ValueType v(this->input_value_string_type());

  EXPECT_EQ(v.get<std::wstring>(), this->test_value_wchar_string);
  EXPECT_EQ(v.get<std::string>(), this->test_value_char_string);
}
