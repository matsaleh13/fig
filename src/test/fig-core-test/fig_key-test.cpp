#include "gtest/gtest.h"

#include "fig_key.h"

template <typename TChar>
class FigKeyTypedFixture : public ::testing::Test {
public:
  const TChar* input_key_name();
  const TChar* test_key_name();

  typedef std::basic_string<TChar> StringType;
};

template <>
const char* FigKeyTypedFixture<char>::input_key_name() {
  return "Forty-Two";
}

template <>
const wchar_t* FigKeyTypedFixture<wchar_t>::input_key_name() {
  return L"Forty-Two";
}

template <>
const char* FigKeyTypedFixture<char>::test_key_name() {
  return "forty-two";
}

template <>
const wchar_t* FigKeyTypedFixture<wchar_t>::test_key_name() {
  return L"forty-two";
}

using MyTypes = ::testing::Types<char, wchar_t>;
TYPED_TEST_CASE(FigKeyTypedFixture, MyTypes);

TYPED_TEST(FigKeyTypedFixture, create_key_from_const_char) {
  fig::core::FigKey<typename FigKeyTypedFixture::StringType> k(
      this->input_key_name());

  ASSERT_EQ(k.name(),
            typename FigKeyTypedFixture::StringType(this->test_key_name()));
}

TYPED_TEST(FigKeyTypedFixture, create_key_from_basic_string) {
  fig::core::FigKey<typename FigKeyTypedFixture::StringType> k(
      typename FigKeyTypedFixture::StringType(this->input_key_name()));

  ASSERT_EQ(k.name(),
            typename FigKeyTypedFixture::StringType(this->test_key_name()));
}
